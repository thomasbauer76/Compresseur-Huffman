/**
 * \file statistiques.h
 * \brief Implémentation du TAD Statistiques pour le compresseur d'Huffman
 * \author T. Bauer
 * \date 17/12/2023
 *
 */

#ifndef __STATISTIQUES__
#define __STATISTIQUES__

#include "octet.h"

/**
 * \brief Le type S_Statistiques permet de stocker le nombre d'occurences des 256 octets possiblement présents dans un fichier
 *
 */
typedef unsigned long S_Statistiques[MAX_OCTET];

/**
 * \fn void S_statistiques(S_Statistiques *p_s)
 * \brief Procédure de création de statistiques à occurences nulles
 *
 * \param p_s : un pointeur sur les Statistiques à retourner
 */
void S_statistiques(S_Statistiques *p_s);

/**
 * \fn void S_incrementerOccurence(S_Statistiques *p_s, O_Octet o)
 * \brief Procédure d'incrémentation de l'occurence d'un octet
 *
 * \param p_s : un pointeur sur les Statstiques à modifier
 * \param o : l'octet dont l'occurence sera incrémentée
 */
void S_incrementerOccurence(S_Statistiques *p_s, O_Octet o);

/**
 * \fn void S_fixerOccurence(S_Statistiques *p_s, O_Octet o, unsigned long n)
 * \brief Procédure permettant de fixer le nombre d'occurences d'un octet
 *
 * \param p_s : un pointeur sur les Statstiques à modifier
 * \param o : l'octet dont l'occurence sera fixée
 * \param n : le nombre d'occurences de l'octet
 */
void S_fixerOccurence(S_Statistiques *p_s, O_Octet o, unsigned long n);

/**
 * \fn unsigned long S_obtenirOccurence(S_Statistiques s, O_Octet o)
 * \brief Fonction permettant d'obtenir le nombre d'occurences d'un octet
 *
 * \param s : les statistiques
 * \param o : l'octet
 * \return unsigned long
 */
unsigned long S_obtenirOccurence(S_Statistiques s, O_Octet o);

#endif