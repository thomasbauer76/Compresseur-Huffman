#ifndef __FILE_DE_PRIORITE_D_ARBRE_DE_HUFFMAN__
#define __FILE_DE_PRIORITE_D_ARBRE_DE_HUFFMAN__


#include <stdbool.h>
#include "arbreDeHuffman.h"

typedef struct NoeudFileDePriorite *FileDePriorite;

typedef struct NoeudFileDePriorite {
    ArbreDeHuffman arbre;
    FileDePriorite fileSuivante;
} NoeudFileDePriorite;

FileDePriorite fileDePriorite();
bool estVide(FileDePriorite fdp);
void enfiler(FileDePriorite *fdp, ArbreDeHuffman a);
ArbreDeHuffman obtenirElementEtDefiler(FileDePriorite *fdp);


#endif