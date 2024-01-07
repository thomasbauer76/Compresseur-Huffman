/**
 * \file fileDePrioriteDArbreDeHuffman.h
 * \brief Implémentation du TAD FileDePriorite pour le compresseur d'Huffman
 * \author M. Saunier
 * \date 31/12/2023
 *
 */

#ifndef __FILE_DE_PRIORITE_D_ARBRE_DE_HUFFMAN__
#define __FILE_DE_PRIORITE_D_ARBRE_DE_HUFFMAN__

#include <stdbool.h>

#include "arbreDeHuffman.h"

/**
 * \brief Le type FileDePriorite est un pointeur vers un NoeudFileDePriorite
 *
 */
typedef struct NoeudFileDePriorite *FileDePriorite;

/**
 * \brief Le type NoeudFileDePriorite est une structure qui contient 2 champs : un ArbreDeHuffan et une autre FileDePriorite
 *
 */
typedef struct NoeudFileDePriorite {
    ADH_ArbreDeHuffman arbre;
    FileDePriorite fileSuivante;
} NoeudFileDePriorite;

/**
 * \fn FileDePriorite FDPAH_fileDePriorite(void)
 * \brief Fonction créant une FileDePriorite, pointant sur NULL, pour des ArbreDeHuffman
 *
 * \return FileDePriorite
 */
FileDePriorite FDPAH_fileDePriorite(void);

/**
 * \fn bool FDPAH_estVide(FileDePriorite fdp)
 * \brief Fonction renvoyant VRAI si une FileDePriorite est vide, càd qu'elle ne contient aucun ArbreDeHuffman. Retourne FAUX sinon.
 *
 * \param fdp : FileDePriorite
 * \return Booleen
 */
bool FDPAH_estVide(FileDePriorite fdp);

/**
 * \fn void FDPAH_enfiler(FileDePriorite *p_fdp, ADH_ArbreDeHuffman a)
 * \brief Fonction permettant d'insérer à l'endroit correct (par rapport à l'élément contenu dans la racine de l'arbre) un ArbreDeHuffman dans une FileDePriorite.
 *
 * \param p_fdp : la FileDePriorite à modifier
 * \param a : l'ADH_ArbreDeHuffman à insérer
 */
void FDPAH_enfiler(FileDePriorite *p_fdp, ADH_ArbreDeHuffman a);

/**
 * \fn ADH_ArbreDeHuffman FDPAH_obtenirElementEtDefiler(FileDePriorite *p_fdp)
 * \brief Fonction permettant d'extraire l'ArbreDeHuffman au bout de la FileDePriorite
 *
 * \param p_fdp : FileDePriorite dont on extrait l'ArbreDeHuffman
 * \return ADH_ArbreDeHuffman
 */
ADH_ArbreDeHuffman FDPAH_obtenirElementEtDefiler(FileDePriorite *p_fdp);

#endif