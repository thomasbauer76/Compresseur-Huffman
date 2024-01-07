#include "statistiques.h"

void S_statistiques(S_Statistiques *p_s) {
    for (unsigned short o = 0; o < MAX_OCTET; o++)
        (*p_s)[o] = 0;
}

void S_incrementerOccurence(S_Statistiques *p_s, O_Octet o) {
    (*p_s)[O_octetVersNaturel(o)]++;
}

void S_fixerOccurence(S_Statistiques *p_s, O_Octet o, unsigned long n) {
    (*p_s)[O_octetVersNaturel(o)] = n;
}

unsigned long S_obtenirOccurence(S_Statistiques s, O_Octet o) {
    return s[O_octetVersNaturel(o)];
}