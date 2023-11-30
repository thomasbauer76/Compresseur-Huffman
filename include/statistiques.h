#ifndef __STATISTIQUES__
#define __STATISTIQUES__


#include "octet.h"

typedef unsigned long Statistiques[256];

void S_statistiques(Statistiques s);
void S_incrementerOccurence(Statistiques *s, Octet o);
unsigned long S_obtenirOccurence(Statistiques s, Octet o);


#endif