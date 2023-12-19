#include <stdio.h>
#include <stdlib.h> 
#include "decompression.h"
#include "fileDePrioriteDArbreDeHuffman.h"
#include "statistiques.h"
#include "arbreDeHuffman.h"

void D_decompresser(FILE *f) {

}

void D_seDeplacerDansLArbre(int bit, ArbreDeHuffman *a) {
    if (bit == 0) {
        *a = ADH_obtenirFilsGauche(*a);
    } else {
        *a = ADH_obtenirFilsDroit(*a);
    }
}

void D_libererArbreDeHuffman(ArbreDeHuffman a) {
    if (!(ADH_estUneFeuille(a))) {
        D_libererArbreDeHuffman(ADH_obtenirFilsDroit(a));
        D_libererArbreDeHuffman(ADH_obtenirFilsGauche(a));
    }
    free(a);
}
