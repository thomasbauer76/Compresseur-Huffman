#include <stdio.h>
#include <stdlib.h> 
#include "decompression.h"
#include "fileDePrioriteDArbreDeHuffman.h"
#include "statistiques.h"
#include "arbreDeHuffman.h"

void decompresser(FILE *f) {

}

void seDeplacerDansLArbre(int bit, ArbreDeHuffman *a) {
    if (bit == 0) {
        *a = ADH_obtenirFilsGauche(*a);
    } else {
        *a = ADH_obtenirFilsDroit(*a);
    }
}

void libererArbreDeHuffman(ArbreDeHuffman a) {
    if (!(ADH_estUneFeuille(a))) {
        libererArbreDeHuffman(ADH_obtenirFilsDroit(a));
        libererArbreDeHuffman(ADH_obtenirFilsGauche(a));
    }
    free(a);
}
