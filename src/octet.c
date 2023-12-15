#include <stdio.h>

#include "octet.h"

Octet O_creerOctet(Bit b0, Bit b1, Bit b2, Bit b3, Bit b4, Bit b5, Bit b6, Bit b7){
		
	return b7+(b6<<1)+(b5<<2)+(b4<<3)+(b3<<4)+(b2<<5)+(b1<<6)+(b0<<7);
}

Bit O_obtenirIemeBit(Octet o, unsigned short i) {
    return (o >> (7-i)) & 1;
    //L'opérateur >> est un décalage de (7-i) vers la droite de l'octet o, ce qui correspond à une divison par 2^(7-i)
    //L'opérateur & compare bit à bit : en comparant avec 1 (0000001), on obtient la parité de l'opérande de gauche, ce qui correspond à un modulo 2
}

unsigned char O_octetVersNaturel(Octet o) {
    return o;
}
	
Octet O_naturelVersOctet (unsigned char n){
	return n;
}
