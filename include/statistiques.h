#ifndef __STATISTIQUES__
#define __STATISTIQUES__


#include "octet.h"

typedef unsigned int Statistiques[256];

void statistiques(Statistiques stats);
void incrementerOccurence(Statistiques *stats, Octet octet);
unsigned int obtenirOccurence(Statistiques stats, Octet octet);


#endif