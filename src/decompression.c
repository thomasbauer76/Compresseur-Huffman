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
    if (b == 0) {
        *a = ADH_obtenirFilsGauche(*a);
    } else {
        *a = ADH_obtenirFilsDroit(*a);
    }
}

void D_libererArbreDeHuffman(ArbreDeHuffman a) {
    if (!(ADH_estUneFeuille(a))) {
        libererArbreDeHuffman(ADH_obtenirFilsDroit(a));
        libererArbreDeHuffman(ADH_obtenirFilsGauche(a));
    }
    free(a);
}
