#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include "decompression.h"
#include "fileDePrioriteDArbreDeHuffman.h"
#include "construireArbreDeHuffman.h"
#include "statistiques.h"
#include "arbreDeHuffman.h"
#include "octet.h"
#include <string.h>
// On inclut compression.h pour avoir la constante de l'identifiant
#include "compression.h"

void D_seDeplacerDansLArbre(Bit b, ArbreDeHuffman *a) {
    if (b == bitA0) {
        *a = ADH_obtenirFilsGauche(*a);
    } else {
        *a = ADH_obtenirFilsDroit(*a);
    }
}

void D_lireStatistiques(FILE *fb, Statistiques *s) {
    
    Octet octet;
    unsigned long int occurence;

    S_statistiques(s);
    do {
        fread(&occurence, sizeof(unsigned long int), 1, fb);
        if(occurence!=0){
            fread(&octet, sizeof(unsigned char), 1, fb);
            S_fixerOccurence(s,octet,occurence);
        }

    } while (occurence!=0);

}

void D_decoder(ArbreDeHuffman aHuff, unsigned long long int longueur, FILE *fbCompresse, FILE *fbDecompresse) {
    rewind(fbDecompresse);
    ArbreDeHuffman aTemp = aHuff;
    unsigned long long int compteurOctetsDecodes = 0;
    while (compteurOctetsDecodes < longueur) {
        Octet o;
        fread(&o, sizeof(unsigned char), 1, fbCompresse);
        for (int i = 0; i <= 7; i++) {
            Bit b = O_obtenirIemeBit(o, i);
            D_seDeplacerDansLArbre(b, &aTemp);
            if (ADH_estUneFeuille(aTemp)) {
                Octet oDecode = ADH_obtenirOctet(aTemp);
                fwrite(&oDecode, sizeof(unsigned char), 1, fbDecompresse);
                compteurOctetsDecodes = compteurOctetsDecodes + 1;
                aTemp = aHuff;
            }
        }
    }
}

void D_decompresser(FILE *fbCompresse, char *filename) {
    rewind(fbCompresse);
    // Dans l'instruction en dessous, il faudrait que le nom du fichier decompresse soit "personnalisé"
    FILE *fbDecompresse = fopen(filename, "wb");
    unsigned short int identifiant;
    fread(&identifiant, sizeof(unsigned short int), 1, fbCompresse);
    if (identifiant == IDENTIFIANT) {
        unsigned long long int longueur;
        fread(&longueur, sizeof(unsigned long long int), 1, fbCompresse);
        Statistiques s;
        D_lireStatistiques(fbCompresse, &s);
        ArbreDeHuffman a = CADH_construireArbreDeHuffman(s);
        D_decoder(a, longueur, fbCompresse, fbDecompresse);
        ADH_liberer(a);
    }
}