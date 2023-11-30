#ifndef __FILE_DE_PRIORITE_D_ARBRE_DE_HUFFMAN__
#define __FILE_DE_PRIORITE_D_ARBRE_DE_HUFFMAN__


#include <stdbool.h>
#include "arbreDeHuffman.h"

typedef struct NoeudFileDePriorite *FileDePriorite;

typedef struct NoeudFileDePriorite {
    ArbreDeHuffman arbre;
    FileDePriorite fileSuivante;
} NoeudFileDePriorite;

FileDePriorite FDPAH_fileDePriorite();
bool FDPAH_estVide(FileDePriorite fdp);
void FDPAH_enfiler(FileDePriorite *fdp, ArbreDeHuffman a);
ArbreDeHuffman FDPAH_obtenirElementEtDefiler(FileDePriorite *fdp);


#endif