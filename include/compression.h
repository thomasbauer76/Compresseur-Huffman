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
 * \brief Fonction permettant la compression d'un fichier, dont le nom est donné en entrée afin de reduire le nombre d'octet à la décompression en gardant exactement les mêmes données. 
 *
 * \param f : le FichierBinaire initiale
 * \param filename : le nom du FichierBinaire compressé
 */
void C_compresser(FILE *f, char *filename);

#endif
