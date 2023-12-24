#ifndef __FILE_DE_PRIORITE_D_ARBRE_DE_HUFFMAN__
#define __FILE_DE_PRIORITE_D_ARBRE_DE_HUFFMAN__


#include <stdbool.h>
#include "arbreDeHuffman.h"

typedef struct NoeudFileDePriorite *FileDePriorite;

typedef struct NoeudFileDePriorite {
    ArbreDeHuffman arbre;
    FileDePriorite fileSuivante;
} NoeudFileDePriorite;

/*!
\brief Fonction créant une FileDePriorite pour des ArbreDeHuffman
\return FileDePriorite pointant sur NULL
*/
FileDePriorite FDPAH_fileDePriorite(void);

/*!
\brief Fonction renvoyant VRAI si une FileDePriorite est vide, càd qu'elle ne contient aucun ArbreDeHuffman. Retourne FAUX sinon.
\param FileDePriorite que l'on veut tester
\return Booleen indiquant si la FileDePriorite en paramètre est vide ou non
*/
bool FDPAH_estVide(FileDePriorite fdp);

/*!
\brief Fonction permettant d'insérer à l'endroit correct (par rapport à l'élément contenu dans la racine de l'arbre) un ArbreDeHuffman dans une FileDePriorite. 
\param FileDePriorite à laquelle on aimerait ajouter un ArbreDeHuffman, cette dernière sera modifiée
\param ArbreDeHuffman que l'on souhaiter enfiler dans la FileDePriorite
*/
void FDPAH_enfiler(FileDePriorite *p_fdp, ArbreDeHuffman a);

/*!
\brief Fonction permettant d'extraire l'ArbreDeHuffman au bout de la FileDePriorite
\param FileDePriorite de laquelle on souhaiterait défiler un ArbreDeHuffman, cette dernière sera modifiée
\return L'ArbreDeHuffman obtenu grâce au défilement de la FileDePriorite donnée en paramètre
*/
//ArbreDeHuffman FDPAH_obtenirElementEtDefiler(FileDePriorite *p_fdp);
void FDPAH_obtenirElementEtDefiler(FileDePriorite *fdp, ArbreDeHuffman *a);



#endif