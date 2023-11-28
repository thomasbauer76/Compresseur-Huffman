#include <stdlib.h>

#include "statistiques.h"

void statistiques(Statistiques stats) {
    unsigned int octet;
    for (octet=0; octet<=255; octet++)
        stats[octet] = 0;
}

void incrementerOccurence(Statistiques *stats, Octet octet) {
    (*stats)[octetVersNaturel(octet)]++;
}

unsigned int obtenirOccurence(Statistiques stats, Octet octet) {
    return stats[octetVersNaturel(octet)];
}