#include <stdlib.h>

#include "statistiques.h"

Statistiques statistiques() {
    unsigned int octet;
    unsigned int *stats = (Statistiques)malloc(256*sizeof(int));
    for (octet=0; octet<=255; octet++)
        stats[octet] = 0;
    return stats;
}

void incrementerOccurence(Statistiques *stats, Octet octet) {
    (*stats)[octetVersNaturel(octet)]++;
}

unsigned int obtenirOccurence(Statistiques stats, Octet octet) {
    return stats[octetVersNaturel(octet)];
}