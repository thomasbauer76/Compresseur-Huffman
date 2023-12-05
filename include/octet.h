#ifndef __OCTET__
#define __OCTET__


#include <stdbool.h>

typedef bool Bit;

typedef unsigned char Octet;

void O_creerOctet(Bit b0, Bit b1, Bit b2, Bit b3, Bit b4, Bit b5, Bit b6, Bit b7, Octet o);
Bit O_obtenirIemeBit(Octet o, unsigned short i);
unsigned char O_octetVersNaturel(Octet o);
Octet O_naturelVersOctet(unsigned char n);


#endif
