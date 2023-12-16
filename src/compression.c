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

}

unsigned long long obtenirTailleFichier(FILE *f) {
    return 0;
}

void ecrireTailleFichier(FILE *f, unsigned long long taille) {
    
}

void ecrireStatistiques(FILE *f, Statistiques s) {
    
}


void concatenerCodeBinaireDansFichier(FILE *f, CodeBinaire *cbTemp, CodeBinaire cb) {

}

void encoder(FILE *f, char *filename, TableDeCodage tdc, Statistiques s) {
    unsigned short i;

    rewind(f);
    FILE *fbCompresse = fopen(strcat(filename,".huff"), "wb");

    // Ecriture des données importantes avant d'encoder
    ecrireIdentifiant(fbCompresse);
    ecrireTailleFichier(fbCompresse, obtenirTailleFichier(fbCompresse));
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
        fprintf(fbCompresse, "%c", O_octetVersNaturel(codeBinaireEnOctet(cbTemp)));
    }

    fclose(fbCompresse);
}

void compresser(FILE *f, char *filename) {

}