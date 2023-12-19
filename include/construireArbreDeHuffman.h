/**
 * \file construireArbreDeHuffman.h
 * \brief Implantation des fonctions utilisées pour construire un arbre de Huffman à partir de statistiques
 * \author T. Bauer
 * \date 19/12/2023
 *
 */

#ifndef __CONSTRUIRE_ARBRE_DE_HUFFMAN__
#define __CONSTRUIRE_ARBRE_DE_HUFFMAN__


#include "statistiques.h"
#include "arbreDeHuffman.h"
#include "fileDePrioriteDArbreDeHuffman.h"

/**
 * \fn FileDePriorite CADH_construireFileDePriorite(Statistiques s)
 * \brief Fonction permettant de construire la file de priorité contenant les feuilles d'occurences non nulles à partir de statistiques
 *
 * \param s : les statistiques
 * \return FileDePriorite
 */
FileDePriorite CADH_construireFileDePriorite(Statistiques s);

/**
 * \fn ArbreDeHuffman CADH_construireArbreDeHuffman(Statistiques s)
 * \brief Fonction permettant de construire l'arbre de Huffman à partir de statistiques
 *
 * \param s : les statistiques
 * \return ArbreDeHuffman
 */
ArbreDeHuffman CADH_construireArbreDeHuffman(Statistiques s);


#endif