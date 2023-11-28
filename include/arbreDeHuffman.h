#ifndef __ARBRE_DE_HUFFMAN__
#define __ARBRE_DE_HUFFMAN__


#include <stdbool.h>
#include "octet.h"

typedef struct NoeudArbreDeHuffman *ArbreDeHuffman;

typedef struct NoeudArbreDeHuffman {
    Octet octet;
    unsigned long frequence;
    bool estUneFeuille;
    ArbreDeHuffman arbreGauche;
    ArbreDeHuffman arbreDroit;
} NoeudArbreDeHuffman;

ArbreDeHuffman arbreDeHuffman(Octet o, unsigned long n);
ArbreDeHuffman fusionner(ArbreDeHuffman ag, ArbreDeHuffman ad);
bool estUneFeuille(ArbreDeHuffman a);
void obtenirOctet(ArbreDeHuffman a, Octet o); //Octet est un tableau, c'est donc une Entrée/Sortie
unsigned long obtenirFrequence(ArbreDeHuffman a);
ArbreDeHuffman obtenirFilsGauche(ArbreDeHuffman a);
ArbreDeHuffman obtenirFilsDroit(ArbreDeHuffman a);


#endif