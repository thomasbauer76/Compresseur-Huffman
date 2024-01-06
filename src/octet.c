#include "octet.h"

#include <assert.h>
#include <stdio.h>

Octet O_creerOctet(Bit b7, Bit b6, Bit b5, Bit b4, Bit b3, Bit b2, Bit b1, Bit b0) {
    return b0 + (b1 << 1) + (b2 << 2) + (b3 << 3) + (b4 << 4) + (b5 << 5) + (b6 << 6) + (b7 << 7);
}

Bit O_obtenirIemeBit(Octet o, unsigned short i) {
    assert(i < MAX_BITS);
    return (o >> i) & 1;
    // L'opérateur >> est un décalage de i vers la droite de l'octet o, ce qui correspond à une divison par 2^i
    // L'opérateur & compare bit à bit : en comparant avec 1 (0000001), on obtient la parité de l'opérande de gauche, ce qui correspond à un modulo 2
}

unsigned char O_octetVersNaturel(Octet o) {
    return o;
}

Octet O_naturelVersOctet(unsigned char n) {
    return n;
}
