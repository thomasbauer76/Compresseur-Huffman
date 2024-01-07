/**
 * \file compression.h
 * \brief Implémentation de la fonction compresser pour le compresseur d'Huffman
 * \author O.Taoba
 * \date 07/01/2024
 *
 */

#ifndef __COMPRESSION__
#define __COMPRESSION__

#include <stddef.h>
#include <stdio.h>

#define IDENTIFIANT 1000

/**
 * \fn C_Compresser(FILE *f, char *filename)
 * \brief Fonction permettant la compression d'un fichier par la méthode du codage de Huffman 
 *
 * \param f : le fichier à compresser
 * \param filename : le nom du fichier à compresser
 */
void C_compresser(FILE *f, char *filename);

#endif
