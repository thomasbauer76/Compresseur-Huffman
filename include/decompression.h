/**
 * \file decompression.h
 * \brief Implémentation de la fonction decompresser pour le compresseur d'Huffman
 * \author M. Saunier
 * \date 31/12/2023
 *
 */

#ifndef __DECOMPRESSION__
#define __DECOMPRESSION__


#include <stdio.h>

/**
 * \fn D_decompresser(FILE *fbCompresse, char *filename)
 * \brief Fonction permettant la décompression d'un fichier, dont le nom est donné en entrée, préalablement compressé par notre algortithme du compresseur d'Huffman. Le fichier décompressé est crée par la fonction et portera le nom du fichier compressé sans l'extension '.huff'
 *
 * \param fbCompresse : le FichierBinaire compressé
 * \param filename : le nom du fichier compressé
 */
void D_decompresser(FILE *fbCompresse, char *filename);


#endif