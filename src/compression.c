#include <stdio.h>
#include <string.h>
#include "octet.h"
#include "tableDeCodage.h"
#include "statistiques.h"
#include "codeBinaire.h"
#include "compression.h"

Octet codeBinaireEnOctet(CodeBinaire cb) {

}

void ecrireIdentifiant(FILE *f) {
    unsigned short identifiant = IDENTIFIANT;
    fwrite(&identifiant, sizeof(unsigned short), 1, f);
}

void ecrireTailleFichier(FILE *f, unsigned long long taille) {
    fwrite(&taille, sizeof(unsigned long long), 1, f);
}

void ecrireStatistiques(FILE *f, Statistiques s) {
    unsigned short o;
    for (o = 0; o < MAX_OCTET; o++) {
        unsigned long occurence = S_obtenirOccurence(s, O_naturelVersOctet(o));
        fwrite(&occurence, sizeof(unsigned long), 1, f);
    }
}

void concatenerCodeBinaireDansFichier(FILE *f, CodeBinaire *p_cbTemp, CodeBinaire cb) {
    unsigned short i, j;

    if (CB_obtenirLongueur(*p_cbTemp) == 8)
        *p_cbTemp = cb;
    
    unsigned short tailleCbTemp = CB_obtenirLongueur(*p_cbTemp);
    unsigned short tailleCb = CB_obtenirLongueur(cb);
    unsigned short tailleTotale = tailleCbTemp + tailleCb;

    if (tailleTotale > 8) {
        for (i = 0; i < MAX_CB - tailleCbTemp; i++)
            CB_ajouterBit(p_cbTemp, CB_obtenirIemeBit(cb, i));
        unsigned char octet = O_octetVersNaturel(codeBinaireEnOctet(*p_cbTemp));
        fwrite(&octet, sizeof(unsigned char), 1, f);

        *p_cbTemp = CB_creerCodeBinaire(CB_obtenirIemeBit(cb, i+1));
        for (j = i + 2; j < tailleCb; j++)
            CB_ajouterBit(p_cbTemp, CB_obtenirIemeBit(cb, j));
    }
    else {
        for (i = tailleCbTemp; i < tailleTotale; i++)
            CB_ajouterBit(p_cbTemp, CB_obtenirIemeBit(cb, i));

        if (CB_obtenirLongueur(*p_cbTemp) == 8) {
            unsigned char octet = O_octetVersNaturel(codeBinaireEnOctet(*p_cbTemp));
            fwrite(&octet, sizeof(unsigned char), 1, f);
        }
    }
}

void encoder(FILE *f, char *filename, TableDeCodage tdc, Statistiques s, unsigned long long taille) {
    unsigned short i;

    rewind(f);
    FILE *fbCompresse = fopen(strcat(filename,".huff"), "wb");

    // Ecriture des données importantes avant d'encoder
    ecrireIdentifiant(fbCompresse);
    ecrireTailleFichier(fbCompresse, taille);
    ecrireStatistiques(fbCompresse, s);

    // Création d'un code binaire temporaire initalisé à 8 bits pour rentrer dans la première condition de la fonction concatenerCodeBinaireEnOctet
    CodeBinaire cbTemp = CB_creerCodeBinaire(bitA0);
    for (i = 1; i < MAX_CB; i++)
        CB_ajouterBit(&cbTemp, bitA0);
    
    // Boucle d'encodage
    CodeBinaire cb;
    short o;
    while ((o = fgetc(f)) != EOF) {
        cb = TDC_octetVersCodeBinaire(tdc, O_naturelVersOctet(o));
        concatenerCodeBinaireDansFichier(fbCompresse, &cbTemp, cb);
    }

    // Ecriture du dernier octet si le dernier code binaire n'est pas de taille 8 et n'a donc pas été écrit dans le fichier compressé
    if (CB_obtenirLongueur(cbTemp) < 8) {
        for (i = CB_obtenirLongueur(cbTemp); i < MAX_CB; i++)
            CB_ajouterBit(&cbTemp, bitA0);
        unsigned char octet = O_octetVersNaturel(codeBinaireEnOctet(cbTemp));
        fwrite(&octet, sizeof(unsigned char), 1, fbCompresse);
    }

    fclose(fbCompresse);
}

void compresser(FILE *f, char *filename) {

}