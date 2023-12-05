#include <stdio.h>

#include "octet.h"

unsigned char O_octetVersNaturel(Octet o) {
    return o;
}

Bit O_obtenirIemeBit(Octet o, unsigned short i) {
    return (o >> (7-i)) & 1;
    //L'opérateur >> est un décalage de (7-i) vers la droite de l'octet o, ce qui correspond à une divison par 2^(7-i)
    //L'opérateur & compare bit à bit : en comparant avec 1 (0000001), on obtient la parité de l'opérande de gauche, ce qui correspond à un modulo 2
}