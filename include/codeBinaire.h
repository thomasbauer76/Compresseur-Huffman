/**
 * \file codeBinaire.h
 * \brief Implantation du TAD CodeBinaire pour le compresseur d'Huffman
 * \author T. Bauer
 * \date 17/12/2023
 *
 */

#ifndef __CODE_BINAIRE__
#define __CODE_BINAIRE__


#include "octet.h"

#define MAX_CB (MAX_OCTET - 1)
/**
 * \brief Le type CodeBinaire permet de stocker des bits dans un ordre donné
 * 
 */

typedef struct CodeBinaire {
    unsigned long long codeBinaire; /**< les octets (stockés sous forme de naturel) contenant ces bits */
    unsigned short nbBits; /**< le nombre de bits du code binaire */
} CodeBinaire;


/**
 * \fn CodeBinaire CB_creerCodeBinaire(Bit b)
 * \brief Fonction de création d'un code binaire à 1 bit
 *
 * \param b : le bit
 * \return CodeBinaire
 */
CodeBinaire CB_creerCodeBinaire(Bit b);

/**
 * \fn void CB_ajouterBit(CodeBinaire *p_cb, Bit b)
 * \brief Procédure permettant d'ajouter un bit à un code binaire
 *
 * \param p_cb : un pointeur sur le code binaire à modifier
 * \param b : le bit à ajouter
 */
void CB_ajouterBit(CodeBinaire *p_cb, Bit b);

/**
 * \fn Bit CB_obtenirIemeBit(CodeBinaire cb, unsigned short i)
 * \brief Fonction permettant de retourner le bit à d'indice i (0 étant le bit le plus à gauche et 7 le plus à droite) d'un code binaire
 *
 * \param cb : le code binaire
 * \param i : l'indice du bit à retourner
 * \return CodeBinaire
 */
Bit CB_obtenirIemeBit(CodeBinaire cb, unsigned short i);

/**
 * \fn unsigned short CB_obtenirLongueur(CodeBinaire cb)
 * \brief Fonction permettant d'obtenir le nombre de bits présents dans un code binaire
 *
 * \param cb : le code binaire
 * \return unsigned short
 */
unsigned short CB_obtenirLongueur(CodeBinaire cb);


#endif