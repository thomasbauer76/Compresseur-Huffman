/**
 * \file arbreDeHuffman.h
 * \brief Implantation du TAD ArbreDeHuffman pour le compresseur d'Huffman
 * \author M. Saunier
 * \date 31/12/2023
 *
 */

#ifndef __ARBRE_DE_HUFFMAN__
#define __ARBRE_DE_HUFFMAN__


#include <stdbool.h>
#include "octet.h"

/**
 * \brief Le type ArbreDeHuffman est un pointeur vers un NoeudArbreDeHuffman
 * 
 */
typedef struct NoeudArbreDeHuffman *ArbreDeHuffman;

/**
 * \brief Le type NoeudArbreDeHuffman est une structure qui contient un octet ainsi qu'une fréquence
 * associée à cet octet. Ces valeurs n'ont un sens que si le noeud est une feuille et cette information
 * est stocée dans le booléen 'estUneFeuille'. Les deux derniers champs de cette structure sont 2 ArbreDeHuffman
 * qui représentent un fils gauche et un fils droit
 * 
 */
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
Octet ADH_obtenirOctet(ArbreDeHuffman a);
unsigned long ADH_obtenirFrequence(ArbreDeHuffman a);
ArbreDeHuffman ADH_obtenirFilsGauche(ArbreDeHuffman a);
ArbreDeHuffman ADH_obtenirFilsDroit(ArbreDeHuffman a);
void ADH_liberer(ArbreDeHuffman a);


#endif