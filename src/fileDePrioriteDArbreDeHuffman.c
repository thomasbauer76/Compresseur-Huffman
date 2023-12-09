#include <stddef.h>
#include <stdlib.h>
#include "fileDePrioriteDArbreDeHuffman.h"
#include "arbreDeHuffman.h"

/*!
*\brief Fonction créant une FileDePriorite pour des Arbres d'Huffman
*/
FileDePriorite FDPAH_fileDePriorite() {
	return NULL;
}

/*!
*\brief Fonction renvoyant VRAI si une FileDePriorite est vide, càd qu'elle ne contient aucun Arbre d'Huffman. Retourne FAUX sinon.
*/
bool FDPAH_estVide(FileDePriorite fdp) {
	return (fdp == NULL);
}

/*!
*\brief Fonction permettant d'insérer à l'endroit correct (par rapport à l'élément contenu dans la racine de l'arbre) un Arbre d'Huffman dans une FileDePriorite. 
*/
void FDPAH_enfiler(FileDePriorite *p_fdp, ArbreDeHuffman a) {
	if ((FDPAH_estVide(*p_fdp)) || (ADH_obtenirFrequence(a) < ADH_obtenirFrequence((*p_fdp)->arbre))) {
		FileDePriorite* p_temp = p_fdp;
		//allocation de la taille de file
		FileDePriorite p_noeud = (FileDePriorite)malloc(sizeof(NoeudFileDePriorite));
		p_noeud->arbre = a;
		p_noeud->fileSuivante = *p_temp;
		p_fdp = &p_noeud;
	}
	else {
		FDPAH_enfiler(&((*p_fdp)->fileSuivante), a);
	}
}

/*!
*\brief Fonction permettant d'extraire l'Arbre d'Huffman au bout de la FileDePriorite
*/
ArbreDeHuffman FDPAH_obtenirElementEtDefiler(FileDePriorite *p_fdp) {
	ArbreDeHuffman a = (*p_fdp)->arbre;
	FileDePriorite* p_temp = p_fdp;
	p_fdp = &((*p_temp)->fileSuivante);
	free(p_temp);
	return a;
}
