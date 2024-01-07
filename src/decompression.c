#include "decompression.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "arbreDeHuffman.h"
#include "construireArbreDeHuffman.h"
#include "fileDePrioriteDArbreDeHuffman.h"
#include "octet.h"
#include "statistiques.h"
#include "compression.h" // On inclut compression.h pour avoir la constante de l'identifiant

void D_seDeplacerDansLArbre(O_Bit b, ADH_ArbreDeHuffman *a) {
    if (b == bitA0) {
        *a = ADH_obtenirFilsGauche(*a);
    } else {
        *a = ADH_obtenirFilsDroit(*a);
    }
}

void D_lireStatistiques(FILE *fb, S_Statistiques *s) {
    unsigned char octet;
    unsigned long occurence;

    S_statistiques(s);
    do {
        // Note : la valeur de type size_t retournée par la fonction fread est le nombre de blocs lus. Si elle est inférieure au nombre de blocs
        // à lire indiqué en paramètre, c'est que nous sommes arrivés à la fin du fichier ou qu'une erreur est survenue.
        size_t nbBlocsLus = fread(&occurence, sizeof(unsigned long int), 1, fb);
        if (nbBlocsLus < 1) {
            printf("Erreur : problème de lecture. Cela peut être causé par un fichier corrumpu.\n");
            exit(EXIT_FAILURE);
        }
        if (occurence != 0) {
            size_t nbBlocsLus = fread(&octet, sizeof(unsigned char), 1, fb);
            if (nbBlocsLus < 1) {
                printf("Erreur : problème de lecture. Cela peut être causé par un fichier corrumpu.\n");
                exit(EXIT_FAILURE);
            }
            S_fixerOccurence(s, O_naturelVersOctet(octet), occurence);
        }

    } while (occurence != 0);
}

void D_decoder(ADH_ArbreDeHuffman aHuff, unsigned long long int longueur, FILE *fbCompresse, FILE *fbDecompresse) {
    rewind(fbDecompresse);
    ADH_ArbreDeHuffman aTemp = aHuff;
    unsigned long long int compteurOctetsDecodes = 0;
    bool finDecodage = false;
    while (!finDecodage) {
        unsigned char o;
        size_t nbBlocsLus = fread(&o, sizeof(unsigned char), 1, fbCompresse);
        if (nbBlocsLus < 1) {
            printf("Erreur060 decompression.c : fin du fichier atteinte de manière innatendue ou erreur de la fonction fread \n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < MAX_BITS; i++) {
            if (!finDecodage) {  // if qui permet de régler les bugs sur le dernier octets
                O_Bit b = O_obtenirIemeBit(O_naturelVersOctet(o), i);
                D_seDeplacerDansLArbre(b, &aTemp);
                if (ADH_estUneFeuille(aTemp)) {
                    O_Octet oDecode = ADH_obtenirOctet(aTemp);
                    fwrite(&oDecode, sizeof(unsigned char), 1, fbDecompresse);
                    aTemp = aHuff;
                    compteurOctetsDecodes = compteurOctetsDecodes + 1;
                    finDecodage = (compteurOctetsDecodes == longueur);
                }
            }
        }
    }
}

void D_decompresser(FILE *fbCompresse, char *filename) {
    rewind(fbCompresse);
    // Petit bout de code pour supprimer le .huff en fin de la variable filename
    size_t nouvelleLongueurDuNom = strlen(filename) - strlen(".huff");
    filename[nouvelleLongueurDuNom] = '\0';
    FILE *fbDecompresse = fopen(filename, "wb");
    unsigned short int identifiant;
    size_t nbBlocsLus = fread(&identifiant, sizeof(unsigned short int), 1, fbCompresse);
    if (nbBlocsLus < 1) {
        printf("Erreur : problème de lecture. Cela peut être causé par un fichier corrumpu.\n");
        exit(EXIT_FAILURE);
    }
    if (identifiant == IDENTIFIANT) {
        unsigned long long int longueur;
        size_t nbBlocsLus = fread(&longueur, sizeof(unsigned long long int), 1, fbCompresse);
        if (nbBlocsLus < 1) {
            printf("Erreur : problème de lecture. Cela peut être causé par un fichier corrumpu.\n");
            exit(EXIT_FAILURE);
        }
        if (longueur > 0) {  // Cas particulier d'un fichier vide
            S_Statistiques s;
            D_lireStatistiques(fbCompresse, &s);
            ADH_ArbreDeHuffman a = CADH_construireArbreDeHuffman(s);
            if (ADH_estUneFeuille(a)) {  // Cas particulier d'un fichier contenant un seul octet (présent plusieurs fois ou non)
                unsigned char octet = O_octetVersNaturel(ADH_obtenirOctet(a));
                for (unsigned long long i = 1; i <= longueur; i++)
                    fwrite(&octet, sizeof(unsigned char), 1, fbDecompresse);
            } else {
                D_decoder(a, longueur, fbCompresse, fbDecompresse);
            }
            ADH_liberer(a);
        }
    } else {
        printf("Erreur : identifiant de compression incorrect. Il semble que le fichier ait été compressé à l'origine avec un compresseur différent.");
        exit(EXIT_FAILURE);
    }

    fclose(fbDecompresse);
    chmod(filename, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}