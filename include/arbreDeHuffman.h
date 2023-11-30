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

ArbreDeHuffman ADH_arbreDeHuffman(Octet o, unsigned long n);
ArbreDeHuffman ADH_fusionner(ArbreDeHuffman ag, ArbreDeHuffman ad);
bool ADH_estUneFeuille(ArbreDeHuffman a);
void ADH_obtenirOctet(ArbreDeHuffman a, Octet o); //Octet est un tableau, c'est donc une Entrée/Sortie
unsigned long ADH_obtenirFrequence(ArbreDeHuffman a);
ArbreDeHuffman ADH_obtenirFilsGauche(ArbreDeHuffman a);
ArbreDeHuffman ADH_obtenirFilsDroit(ArbreDeHuffman a);


#endif