#ifndef __DECOMPRESSION__
#define __DECOMPRESSION__


#include <stdio.h>
#include "arbreDeHuffman.h"

void decompresser(FILE *f);
void seDeplacerDansLArbre(int bit, ArbreDeHuffman *a);
void libererArbreDeHuffman(ArbreDeHuffman a);
#endif