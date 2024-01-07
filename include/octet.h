/**
 * \file codeBinaire.h
 * \brief Implémentation du TAD octet pour le compresseur d'Huffman
 * \author A. Hamdani
 * \date 06/01/2023
 *
 */
#ifndef __OCTET__
#define __OCTET__
/**
 * \brief Le type octet est un type composé de 8 bits
 *
 */

#include <stdbool.h>

#define MAX_BITS 8    /**< le nombre de bits maximum que contient un octet*/
#define bitA0 0       /**< valeur 0 d'un bit */
#define bitA1 1       /**< valeur 1 d'un bit*/
#define MAX_OCTET 256 /**< valeur maximal d'un octet*/

typedef bool Bit;            /**le type bool peut valoir soit 0 soit 1*/
typedef unsigned char Octet; /**la valeur de l'octet est comprise entre 0 et 255*/

/**
 * \fn Octet O_creerOctet(Bit b7, Bit b6, Bit b5, Bit b4, Bit b3, Bit b2, Bit b1, Bit b0);
 * \brief Fonction de création d'un octet de 8 bit
 *
 * \param b7: le bit le plus à gauche ou 1er bit
 * \param b6: 2ème bit
 * \param b5: 3ème bit
 * \param b4: 4ème bit
 * \param b3: 5ème bit
 * \param b2: 6ème bit
 * \param b1: 7ème bit
 * \param b0: 8ème bit le bit le plus à droite

 * \return Octet
 */

Octet O_creerOctet(Bit b7, Bit b6, Bit b5, Bit b4, Bit b3, Bit b2, Bit b1, Bit b0);

/**
 * \fn Bit O_obtenirIemeBit(Octet o, unsigned short i);
 * \brief Fonction qui retourne la valeur du bit situé à la ième position
 *
 * \param o : un octet de 8 bits
 * \param i : position du bit dont on cherche la valeur
 * \return Octet
 */

Bit O_obtenirIemeBit(Octet o, unsigned short i);

/**
 * \fn CB_CodeBinaire CB_creerCodeBinaire(Bit b)
 * \brief Fonction qui retourne le naturel associé à l'octet o
 *
 * \param o : un octet de 8 bits
 * \return Unsigned char
 */
unsigned char O_octetVersNaturel(Octet o);

/**
 * \fn Octet O_naturelVersOctet(unsigned char n);
 * \brief Fonction qui retourne l'octet associé à un naturel compris entre 0 et 255
 *
 * \param n : naturel compris entre 0-255
 * \return Octet
 */
Octet O_naturelVersOctet(unsigned char n);

#endif
