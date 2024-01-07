#include "compression.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "arbreDeHuffman.h"
#include "codeBinaire.h"
#include "construireArbreDeHuffman.h"
#include "fileDePrioriteDArbreDeHuffman.h"
#include "octet.h"
#include "statistiques.h"
#include "tableDeCodage.h"

unsigned short min(unsigned short a, unsigned short b) {
    if (a > b)
        return b;
    else
        return a;
}

void C_obtenirStatistiquesEtTailleFichier(FILE *f, S_Statistiques *s, unsigned long long *taille) {
    rewind(f);

    S_statistiques(s);
    *taille = 0;

    short o;
    while ((o = fgetc(f)) != EOF) {
        S_incrementerOccurence(s, O_naturelVersOctet(o));
        (*taille)++;
    }
}

void C_obtenirTableDeCodageRecursif(TableDeCodage *tdc, ADH_ArbreDeHuffman a, CB_CodeBinaire cb) {
    CB_CodeBinaire cbCopie;

    if (ADH_estUneFeuille(a)) {
        TDC_ajouterCodage(tdc, ADH_obtenirOctet(a), cb);
    } else {
        memcpy(&cbCopie, &cb, sizeof(CB_CodeBinaire));

        CB_ajouterBit(&cbCopie, bitA0);
        C_obtenirTableDeCodageRecursif(tdc, ADH_obtenirFilsGauche(a), cbCopie);
        CB_ajouterBit(&cb, bitA1);
        C_obtenirTableDeCodageRecursif(tdc, ADH_obtenirFilsDroit(a), cb);
    }
}

TableDeCodage C_obtenirTableDeCodage(ADH_ArbreDeHuffman a) {
    assert(!ADH_estUneFeuille(a));

    TableDeCodage tdc = TDC_creerTableCodage();

    CB_CodeBinaire cbGauche = CB_creerCodeBinaire(bitA0);
    CB_CodeBinaire cbDroit = CB_creerCodeBinaire(bitA1);
    C_obtenirTableDeCodageRecursif(&tdc, ADH_obtenirFilsGauche(a), cbGauche);
    C_obtenirTableDeCodageRecursif(&tdc, ADH_obtenirFilsDroit(a), cbDroit);

    return tdc;
}

void C_ecrireIdentifiant(FILE *f) {
    unsigned short identifiant = IDENTIFIANT;
    fwrite(&identifiant, sizeof(unsigned short), 1, f);
}

void C_ecrireTailleFichier(FILE *f, unsigned long long taille) {
    fwrite(&taille, sizeof(unsigned long long), 1, f);
}

void C_ecrireStatistiques(FILE *f, S_Statistiques s) {
    O_Octet octet;
    unsigned long occurence;

    unsigned short o;
    for (o = 0; o < MAX_OCTET; o++) {
        octet = O_naturelVersOctet(o);
        occurence = S_obtenirOccurence(s, octet);
        if (occurence > 0) {
            fwrite(&occurence, sizeof(unsigned long), 1, f);
            fwrite(&o, sizeof(unsigned char), 1, f);
        }
    }
    occurence = 0;
    fwrite(&occurence, sizeof(unsigned long), 1, f);
}

O_Octet C_codeBinaireEnOctet(CB_CodeBinaire cb) {
    assert(CB_obtenirLongueur(cb) == MAX_BITS);
    return O_creerOctet(CB_obtenirIemeBit(cb, 7),
                        CB_obtenirIemeBit(cb, 6),
                        CB_obtenirIemeBit(cb, 5),
                        CB_obtenirIemeBit(cb, 4),
                        CB_obtenirIemeBit(cb, 3),
                        CB_obtenirIemeBit(cb, 2),
                        CB_obtenirIemeBit(cb, 1),
                        CB_obtenirIemeBit(cb, 0));
}

void C_concatenerCodeBinaireDansFichier(FILE *f, CB_CodeBinaire *p_cbTemp, CB_CodeBinaire cb) {
    unsigned short i = 0;
    unsigned short tailleCb = CB_obtenirLongueur(cb);

    while (i != tailleCb) {
        if (CB_obtenirLongueur(*p_cbTemp) == MAX_BITS) {
            *p_cbTemp = CB_creerCodeBinaire(CB_obtenirIemeBit(cb, i));
            i++;
        }

        while (i < tailleCb && CB_obtenirLongueur(*p_cbTemp) < MAX_BITS) {
            CB_ajouterBit(p_cbTemp, CB_obtenirIemeBit(cb, i));
            i++;
        }

        if (CB_obtenirLongueur(*p_cbTemp) == MAX_BITS) {
            unsigned char octet = O_octetVersNaturel(C_codeBinaireEnOctet(*p_cbTemp));
            fwrite(&octet, sizeof(unsigned char), 1, f);
        }
    }
}

void C_encoder(FILE *f, FILE *fbCompresse, TableDeCodage tdc) {
    unsigned short i;
    rewind(f);

    // Création d'un code binaire temporaire initalisé à 8 bits pour rentrer dans la première condition de la fonction concatenerCodeBinaireEnOctet
    CB_CodeBinaire cbTemp = CB_creerCodeBinaire(bitA0);
    for (i = 1; i < MAX_BITS; i++)
        CB_ajouterBit(&cbTemp, bitA0);

    // Boucle d'encodage
    CB_CodeBinaire cb;
    short o;
    while ((o = fgetc(f)) != EOF) {
        cb = TDC_octetVersCodeBinaire(tdc, O_naturelVersOctet(o));
        C_concatenerCodeBinaireDansFichier(fbCompresse, &cbTemp, cb);
    }

    // Ecriture du dernier octet si le dernier code binaire n'est pas de taille 8 et n'a donc pas été écrit dans le fichier compressé
    if (CB_obtenirLongueur(cbTemp) < MAX_BITS) {
        for (i = CB_obtenirLongueur(cbTemp); i < MAX_BITS; i++)
            CB_ajouterBit(&cbTemp, bitA0);
        unsigned char octet = O_octetVersNaturel(C_codeBinaireEnOctet(cbTemp));
        fwrite(&octet, sizeof(unsigned char), 1, fbCompresse);
    }
}

void C_compresser(FILE *f, char *filename) {
    S_Statistiques s;
    unsigned long long taille;

    rewind(f);
    FILE *fbCompresse = fopen(strcat(filename, ".huff"), "wb");

    C_obtenirStatistiquesEtTailleFichier(f, &s, &taille);

    // Ecriture des données importantes avant d'encoder
    C_ecrireIdentifiant(fbCompresse);
    C_ecrireTailleFichier(fbCompresse, taille);
    if (taille > 0) {  // Cas particulier d'un fichier vide
        C_ecrireStatistiques(fbCompresse, s);
        ADH_ArbreDeHuffman a = CADH_construireArbreDeHuffman(s);
        if (!ADH_estUneFeuille(a))  // Cas particulier d'un fichier contenant un seul octet (présent plusieurs fois ou non)
            C_encoder(f, fbCompresse, C_obtenirTableDeCodage(a));
        ADH_liberer(a);
    }

    fclose(fbCompresse);
}