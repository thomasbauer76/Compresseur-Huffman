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

ArbreDeHuffman arbreDeHuffman(Octet o, unsigned int n);
ArbreDeHuffman fusionner(ArbreDeHuffman ag, ArbreDeHuffman ad);
bool estUneFeuille(ArbreDeHuffman a);
Octet obtenirOctet(ArbreDeHuffman a);
unsigned int obtenirFrequence(ArbreDeHuffman a);
ArbreDeHuffman obtenirFilsGauche(ArbreDeHuffman a);
ArbreDeHuffman obtenirFilsDroit(ArbreDeHuffman a);

#endif