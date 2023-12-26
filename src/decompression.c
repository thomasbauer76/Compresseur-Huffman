#include <stdio.h>
#include <stdlib.h> 
#include "decompression.h"
#include "fileDePrioriteDArbreDeHuffman.h"
#include "statistiques.h"
#include "arbreDeHuffman.h"
#include "octet.h"

void D_decompresser(FILE *f) {

}

void D_seDeplacerDansLArbre(Bit b, ArbreDeHuffman *a) {
    if (b == bitA0) {
        *a = ADH_obtenirFilsGauche(*a);
    } else {
        *a = ADH_obtenirFilsDroit(*a);
    }
}

FILE* D_decoder(ArbreDeHuffman aHuff, FILE *fb1) {
    FILE *fb2 = fopen("fichierDecompresser", "w");
    ArbreDeHuffman aTemp = aHuff;
    while (!(feof(fb1))) {
        Octet o;
        fread(&o, sizeof(Octet), 1, fb1);
        for (int i = 0; i <= 7; i++) {
            Bit b = O_obtenirIemeBit(o, i);
            D_seDeplacerDansLArbre(b, &aTemp);
            if (ADH_estUneFeuille(aTemp)) {
                Octet oDecode = ADH_obtenirOctet(aTemp);
                fwrite(&oDecode, sizeof(Octet), 1, fb1);
                aTemp = aHuff;
            }
        }
    }
    return fb2;
}

void D_lireStatistiques(FILE *fb, Statistiques s) {

}