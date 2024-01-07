/**
 * \file codeBinaire.h
 * \brief Implémentation du TAD CodeBinaire pour le compresseur d'Huffman
 * \author T. Bauer
 * \date 17/12/2023
 *
 */

#ifndef __CODE_BINAIRE__
#define __CODE_BINAIRE__

#include "octet.h"

#define MAX_CB (8 * sizeof(unsigned long long))
/**
 * \brief Le type CB_CodeBinaire permet de stocker des bits à la suite
 *
 */

typedef struct CB_CodeBinaire {
    unsigned long long codeBinaire; /**< les octets (stockés sous forme de naturel) contenant ces bits */
    unsigned short nbBits;          /**< le nombre de bits du code binaire */
} CB_CodeBinaire;

/**
 * \fn CB_CodeBinaire CB_creerCodeBinaire(O_Bit b)
 * \brief Fonction de création d'un code binaire à 1 bit
 *
 * \param b : le bit
 * \return CB_CodeBinaire
 */
CB_CodeBinaire CB_creerCodeBinaire(O_Bit b);

/**
 * \fn void CB_ajouterBit(CB_CodeBinaire *p_cb, O_Bit b)
 * \brief Procédure permettant d'ajouter un bit à un code binaire
 *
 * \param p_cb : un pointeur sur le code binaire à modifier
 * \param b : le bit à ajouter
 */
void CB_ajouterBit(CB_CodeBinaire *p_cb, O_Bit b);

/**
 * \fn O_Bit CB_obtenirIemeBit(CB_CodeBinaire cb, unsigned short i)
 * \brief Fonction permettant de retourner le bit à d'indice i d'un code binaire
 *
 * \param cb : le code binaire
 * \param i : l'indice du bit à retourner
 * \return CB_CodeBinaire
 */
O_Bit CB_obtenirIemeBit(CB_CodeBinaire cb, unsigned short i);

/**
 * \fn unsigned short CB_obtenirLongueur(CB_CodeBinaire cb)
 * \brief Fonction permettant d'obtenir le nombre de bits présents dans un code binaire
 *
 * \param cb : le code binaire
 * \return unsigned short
 */
unsigned short CB_obtenirLongueur(CB_CodeBinaire cb);

#endif