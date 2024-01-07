#include "octet.h"

#include <assert.h>
#include <stdio.h>

O_Octet O_creerOctet(O_Bit b7, O_Bit b6, O_Bit b5, O_Bit b4, O_Bit b3, O_Bit b2, O_Bit b1, O_Bit b0) {
    return b0 + (b1 << 1) + (b2 << 2) + (b3 << 3) + (b4 << 4) + (b5 << 5) + (b6 << 6) + (b7 << 7);
}

O_Bit O_obtenirIemeBit(O_Octet o, unsigned short i) {
    assert(i < MAX_BITS);
    return (o >> i) & 1;
    // L'opérateur >> est un décalage de i vers la droite de l'octet o, ce qui correspond à une divison par 2^i
    // L'opérateur & compare bit à bit : en comparant avec 1 (0000001), on obtient la parité de l'opérande de gauche, ce qui correspond à un modulo 2
}

unsigned char O_octetVersNaturel(O_Octet o) {
    return o;
}

O_Octet O_naturelVersOctet(unsigned char n) {
    return n;
}
