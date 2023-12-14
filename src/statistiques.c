#include "statistiques.h"

void S_statistiques(Statistiques s) {
    for (unsigned short o = 0; o < MAX_OCTET; o++)
        s[o] = 0;
}

void S_incrementerOccurence(Statistiques *s, Octet o) {
    (*s)[O_octetVersNaturel(o)]++;
}

unsigned long S_obtenirOccurence(Statistiques s, Octet o) {
    return s[O_octetVersNaturel(o)];
}