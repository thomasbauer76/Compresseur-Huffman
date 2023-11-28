#ifndef __ARBRE_DE_HUFFMAN__
#define __ARBRE_DE_HUFFMAN__


#include "octet.h"

typedef struct Noeud *ArbreDeHuffman;

typedef struct Noeud {
    Octet octet;
    unsigned int frequence;
    ArbreDeHuffman arbreGauche;
    ArbreDeHuffman arbreDroit;
} Noeud;


#endif