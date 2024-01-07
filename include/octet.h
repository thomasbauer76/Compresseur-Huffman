/**
 * \file codeBinaire.h
 * \brief Implémentation du TAD octet pour le compresseur d'Huffman
 * \author A. Hamdani
 * \date 06/01/2023
 *
 */
#ifndef __OCTET__
#define __OCTET__

#include <stdbool.h>

#define MAX_BITS    8
#define bitA0       0      
#define bitA1       1      
#define MAX_OCTET   256

/**
 * \brief Le type O_Bit est un booléen pouvant prendre la valeur bitA0 (0) ou bitA1 (1)
 *
 */
typedef bool O_Bit;

/**
 * \brief Le type O_Octet est un naturel pouvant prendre des valeurs comprises entre 0 et 255 (soit 8 bits)
 *
 */
typedef unsigned char O_Octet;

/**
 * \fn O_Octet O_creerOctet(O_Bit b7, O_Bit b6, O_Bit b5, O_Bit b4, O_Bit b3, O_Bit b2, O_Bit b1, O_Bit b0);
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

 * \return O_Octet
 */
O_Octet O_creerOctet(O_Bit b7, O_Bit b6, O_Bit b5, O_Bit b4, O_Bit b3, O_Bit b2, O_Bit b1, O_Bit b0);

/**
 * \fn O_Bit O_obtenirIemeBit(O_Octet o, unsigned short i);
 * \brief Fonction qui retourne la valeur du bit situé à la ième position
 *
 * \param o : un octet de 8 bits
 * \param i : position du bit dont on cherche la valeur
 * \return O_Octet
 */
O_Bit O_obtenirIemeBit(O_Octet o, unsigned short i);

/**
 * \fn CB_CodeBinaire CB_creerCodeBinaire(O_Bit b)
 * \brief Fonction qui retourne le naturel associé à l'octet o
 *
 * \param o : un octet de 8 bits
 * \return Unsigned char
 */
unsigned char O_octetVersNaturel(O_Octet o);

/**
 * \fn O_Octet O_naturelVersOctet(unsigned char n);
 * \brief Fonction qui retourne l'octet associé à un naturel compris entre 0 et 255
 *
 * \param n : naturel compris entre 0-255
 * \return O_Octet
 */
O_Octet O_naturelVersOctet(unsigned char n);

#endif
