#ifndef __FILE_DE_PRIORITE__
#define __FILE_DE_PRIORITE__


#include "arbreDeHuffman.h"

#include <stdbool.h>

typedef struct Noeud *FileDePriorite;

struct Noeud {
    ArbreDeHuffman arbreDeHuffman;
    FileDePriorite fileSuivante;
};

FileDePriorite fileDePriorite();
bool estVide(FileDePriorite fileDePriorite);
void enfiler(FileDePriorite *fileDePriorite, ArbreDeHuffman arbreDeHuffman);
ArbreDeHuffman obtenirArbreEtDefiler(FileDePriorite *fileDePriorite);

#endif