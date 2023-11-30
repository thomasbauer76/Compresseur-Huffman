#include <stdio.h>
#include <math.h>

#include "octet.h"

unsigned char O_octetVersNaturel(Octet o) {
    return o;
}

Bit O_obtenirIemeBit(Octet o, unsigned short b) {
    return (o / (int)pow(2,7-b)) % 2;
}