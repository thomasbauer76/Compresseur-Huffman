/**
 * \file construireArbreDeHuffman.h
 * \brief Implémentation des fonctions utilisées pour construire un arbre de Huffman à partir de statistiques
 * \author T. Bauer
 * \date 19/12/2023
 *
 */

#ifndef __CONSTRUIRE_ARBRE_DE_HUFFMAN__
#define __CONSTRUIRE_ARBRE_DE_HUFFMAN__

#include "arbreDeHuffman.h"
#include "fileDePrioriteDArbreDeHuffman.h"
#include "statistiques.h"

/**
 * \fn FDPAH_FileDePriorite CADH_construireFileDePriorite(S_Statistiques s)
 * \brief Fonction permettant de construire la file de priorité contenant les feuilles d'occurences non nulles à partir de statistiques
 *
 * \param s : les statistiques
 * \return FDPAH_FileDePriorite
 */
FDPAH_FileDePriorite CADH_construireFileDePriorite(S_Statistiques s);

/**
 * \fn ADH_ArbreDeHuffman CADH_construireArbreDeHuffman(S_Statistiques s)
 * \brief Fonction permettant de construire l'arbre de Huffman à partir de statistiques
 *
 * \param s : les statistiques
 * \return ADH_ArbreDeHuffman
 */
ADH_ArbreDeHuffman CADH_construireArbreDeHuffman(S_Statistiques s);

#endif