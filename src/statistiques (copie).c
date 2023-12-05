#include <stdlib.h>

#include "statistiques.h"

void statistiques(Statistiques s) {
    unsigned short o;
    for (o=0; o<=255; o++)
        s[o] = 0;
}

void incrementerOccurence(Statistiques *s, Octet o) {
    (*s)[octetVersNaturel(o)]++;
}

unsigned long obtenirOccurence(Statistiques s, Octet o) {
    return s[octetVersNaturel(o)];
}