#ifndef __ARBRE_DE_HUFFMAN__
#define __ARBRE_DE_HUFFMAN__


#include <stdbool.h>
#include "octet.h"

typedef struct Noeud *ArbreDeHuffman;

typedef struct Noeud {
    Octet octet;
    unsigned int frequence;
    bool estUneFeuille;
    ArbreDeHuffman arbreGauche;
    ArbreDeHuffman arbreDroit;
} Noeud;


#endif