#ifndef __STATISTIQUES__
#define __STATISTIQUES__


#include "octet.h"

typedef unsigned long Statistiques[256];

void statistiques(Statistiques s);
void incrementerOccurence(Statistiques *s, Octet o);
unsigned long obtenirOccurence(Statistiques s, Octet o);


#endif