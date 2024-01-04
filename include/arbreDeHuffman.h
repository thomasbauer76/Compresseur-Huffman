/**
 * \file arbreDeHuffman.h
 * \brief Implémentation du TAD ArbreDeHuffman pour le compresseur d'Huffman
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
 * associée à cet octet. La valeur de l'octet n'a de sens que si le noeud est une feuille et cette information
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

/**
 * \fn ArbreDeHuffman ADH_arbreDeHuffman(Octet o, unsigned long n)
 * \brief Fonction de création d'un ArbreDeHuffman "feuille" (avec un octet et une fréquence associée)
 *
 * \param o : l'octet
 * \param n : la fréquence associé à l'octet
 * \return ArbreDeHuffman
 */
ArbreDeHuffman ADH_arbreDeHuffman(Octet o, unsigned long n);

/**
 * \fn ArbreDeHuffman ADH_fusionner(ArbreDeHuffman ag, ArbreDeHuffman ad)
 * \brief Fonction permettant la fusion de 2 ArbreDeHuffman avec une racine qui a pour fréquence la somme des fréquences des 2 ArbreDeHuffman
 *
 * \param ag : ArbreDeHuffman
 * \param ad : ArbreDeHuffman
 * \return ArbreDeHuffman
 */
ArbreDeHuffman ADH_fusionner(ArbreDeHuffman ag, ArbreDeHuffman ad);

/**
 * \fn ADH_estUneFeuille(ArbreDeHuffman a)
 * \brief Fonction permettant de savoir si un ArbreDeHuffman est une feuille
 *
 * \param a : ArbreDeHuffman
 * \return Booleen
 */
bool ADH_estUneFeuille(ArbreDeHuffman a);

/**
 * \fn ADH_obtenirOctet(ArbreDeHuffman a)
 * \brief Fonction permettant d'obtenir l'octet d'un ArbreDeHuffman
 *
 * \param a : ArbreDeHuffman
 * \return Octet
 */
Octet ADH_obtenirOctet(ArbreDeHuffman a);

/**
 * \fn ADH_obtenirFrequence(ArbreDeHuffman a)
 * \brief Fonction permettant d'obtenir la fréquence d'un ArbreDeHuffman
 *
 * \param a : ArbreDeHuffman
 * \return unsigned long
 */
unsigned long ADH_obtenirFrequence(ArbreDeHuffman a);

/**
 * \fn ADH_obtenirFilsGauche(ArbreDeHuffman a)
 * \brief Fonction permettant d'obtenir le fils gauche d'un ArbreDeHuffman
 *
 * \param a : ArbreDeHuffman
 * \return ArbreDeHuffman
 */
ArbreDeHuffman ADH_obtenirFilsGauche(ArbreDeHuffman a);

/**
 * \fn ADH_obtenirFilsDroit(ArbreDeHuffman a)
 * \brief Fonction permettant d'obtenir le fils droit d'un ArbreDeHuffman
 *
 * \param a : ArbreDeHuffman
 * \return ArbreDeHuffman
 */
ArbreDeHuffman ADH_obtenirFilsDroit(ArbreDeHuffman a);

/**
 * \fn ADH_liberer(ArbreDeHuffman a)
 * \brief Fonction permettant de libérer la mémoire associée à un ArbreDeHuffman
 *
 * \param a : ArbreDeHuffman
 */
void ADH_liberer(ArbreDeHuffman a);


#endif