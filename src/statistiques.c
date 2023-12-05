#include "statistiques.h"

void statistiques(Statistiques s) {
    for (unsigned short o = 0; o <= 255; o++)
        s[o] = 0;
}

void incrementerOccurence(Statistiques *s, Octet o) {
    (*s)[O_octetVersNaturel(o)]++;
}

unsigned long obtenirOccurence(Statistiques s, Octet o) {
    return s[O_octetVersNaturel(o)];
}