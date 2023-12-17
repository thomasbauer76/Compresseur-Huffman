#ifndef __STATISTIQUES__
#define __STATISTIQUES__


#include "octet.h"

typedef unsigned long Statistiques[MAX_OCTET];

void S_statistiques(Statistiques *p_s);
void S_incrementerOccurence(Statistiques *p_s, Octet o);
unsigned long S_obtenirOccurence(Statistiques s, Octet o);


#endif