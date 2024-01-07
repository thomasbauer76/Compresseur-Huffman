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
 * \brief Le type ADH_ArbreDeHuffman est un pointeur vers un ADH_Noeud
 *
 */
typedef struct ADH_Noeud *ADH_ArbreDeHuffman;

/**
 * \brief Le type ADH_Noeud est une structure qui contient un octet ainsi qu'une fréquence
 * associée à cet octet. La valeur de l'octet n'a de sens que si le noeud est une feuille et cette information
 * est stocée dans le booléen 'estUneFeuille'. Les deux derniers champs de cette structure sont 2 ArbreDeHuffman
 * qui représentent un fils gauche et un fils droit
 *
 */
typedef struct ADH_Noeud {
    O_Octet octet;                  /**< l'octet contenu dans l'arbre feuille */
    unsigned long frequence;        /**< la fréquence de l'octet si l'arbre est une feuille, la somme des fréquences de ses fils sinon */
    bool estUneFeuille;             /**< booléen permettant de savoir si l'arbre est une feuille */
    ADH_ArbreDeHuffman arbreGauche; /**< le sous-arbre gauche */
    ADH_ArbreDeHuffman arbreDroit;  /**< le sous-arbre droit */
} ADH_Noeud;

/**
 * \fn ADH_ArbreDeHuffman ADH_arbreDeHuffman(O_Octet o, unsigned long n)
 * \brief Fonction de création d'un ArbreDeHuffman "feuille" (avec un octet et une fréquence associée)
 *
 * \param o : l'octet
 * \param n : la fréquence associé à l'octet
 * \return ADH_ArbreDeHuffman
 */
ADH_ArbreDeHuffman ADH_arbreDeHuffman(O_Octet o, unsigned long n);

/**
 * \fn ADH_ArbreDeHuffman ADH_fusionner(ADH_ArbreDeHuffman ag, ADH_ArbreDeHuffman ad)
 * \brief Fonction permettant la fusion de 2 ArbreDeHuffman avec une racine qui a pour fréquence la somme des fréquences des 2 ArbreDeHuffman
 *
 * \param ag : ADH_ArbreDeHuffman
 * \param ad : ADH_ArbreDeHuffman
 * \return ADH_ArbreDeHuffman
 */
ADH_ArbreDeHuffman ADH_fusionner(ADH_ArbreDeHuffman ag, ADH_ArbreDeHuffman ad);

/**
 * \fn ADH_estUneFeuille(ADH_ArbreDeHuffman a)
 * \brief Fonction permettant de savoir si un ArbreDeHuffman est une feuille
 *
 * \param a : ADH_ArbreDeHuffman
 * \return Booleen
 */
bool ADH_estUneFeuille(ADH_ArbreDeHuffman a);

/**
 * \fn ADH_obtenirOctet(ADH_ArbreDeHuffman a)
 * \brief Fonction permettant d'obtenir l'octet d'un ArbreDeHuffman
 *
 * \param a : ADH_ArbreDeHuffman
 * \return O_Octet
 */
O_Octet ADH_obtenirOctet(ADH_ArbreDeHuffman a);

/**
 * \fn ADH_obtenirFrequence(ADH_ArbreDeHuffman a)
 * \brief Fonction permettant d'obtenir la fréquence d'un ArbreDeHuffman
 *
 * \param a : ADH_ArbreDeHuffman
 * \return unsigned long
 */
unsigned long ADH_obtenirFrequence(ADH_ArbreDeHuffman a);

/**
 * \fn ADH_obtenirFilsGauche(ADH_ArbreDeHuffman a)
 * \brief Fonction permettant d'obtenir le fils gauche d'un ArbreDeHuffman
 *
 * \param a : ADH_ArbreDeHuffman
 * \return ADH_ArbreDeHuffman
 */
ADH_ArbreDeHuffman ADH_obtenirFilsGauche(ADH_ArbreDeHuffman a);

/**
 * \fn ADH_obtenirFilsDroit(ADH_ArbreDeHuffman a)
 * \brief Fonction permettant d'obtenir le fils droit d'un ArbreDeHuffman
 *
 * \param a : ADH_ArbreDeHuffman
 * \return ADH_ArbreDeHuffman
 */
ADH_ArbreDeHuffman ADH_obtenirFilsDroit(ADH_ArbreDeHuffman a);

/**
 * \fn ADH_liberer(ADH_ArbreDeHuffman a)
 * \brief Fonction permettant de libérer la mémoire associée à un ArbreDeHuffman
 *
 * \param a : ADH_ArbreDeHuffman
 */
void ADH_liberer(ADH_ArbreDeHuffman a);

#endif