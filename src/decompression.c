#include <stdio.h>
#include "decompression.h"
#include "fileDePrioriteDArbreDeHuffman.h"
#include "statistiques.h"
#include "arbreDeHuffman.h"

void decompresser(FILE *f) {

}

void seDeplacerDansLArbre(int bit, ArbreDeHuffman *a) {

}

void libererArbreDeHuffman(ArbreDeHuffman a) {
    if (!(ADH_estUneFeuille(a))) {
        libererArbreDeHuffman(ADH_obtenirFilsDroit(a));
        libererArbreDeHuffman(ADH_obtenirFilsGauche(a));
    }
    free(a)
}
