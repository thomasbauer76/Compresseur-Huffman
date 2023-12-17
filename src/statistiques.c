#include "statistiques.h"

void S_statistiques(Statistiques *p_s) {
    for (unsigned short o = 0; o < MAX_OCTET; o++)
        (*p_s)[o] = 0;
}

void S_incrementerOccurence(Statistiques *p_s, Octet o) {
    (*p_s)[O_octetVersNaturel(o)]++;
}

void S_fixerOccurence(Statistiques *p_s, Octet o, unsigned long n) {
    (*p_s)[O_octetVersNaturel(o)] = n;
}

unsigned long S_obtenirOccurence(Statistiques s, Octet o) {
    return s[O_octetVersNaturel(o)];
}