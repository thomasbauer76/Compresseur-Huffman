#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "fileDePrioriteDArbreDeHuffman.h"
#include "arbreDeHuffman.h"

FileDePriorite FDPAH_fileDePriorite() {
	return NULL;
}

bool FDPAH_estVide(FileDePriorite fdp) {
	return (fdp == NULL);
}
/*
void FDPAH_enfiler(FileDePriorite *p_fdp, ArbreDeHuffman a) {
	if ((FDPAH_estVide(*p_fdp)) || (ADH_obtenirFrequence(a) < ADH_obtenirFrequence((*p_fdp)->arbre)) 
		|| ((ADH_obtenirFrequence(a) == ADH_obtenirFrequence((*p_fdp)->arbre)) 
		&& (ADH_obtenirOctet(a) < ADH_obtenirOctet((*p_fdp)->arbre)))
		) {
		FileDePriorite* p_temp = p_fdp;
		//allocation de la taille de file
		FileDePriorite p_noeud = (FileDePriorite)malloc(sizeof(NoeudFileDePriorite));
		p_noeud -> arbre = a;
		p_noeud -> fileSuivante = *p_temp;
		p_fdp = &p_noeud;
	}
	else {
		FDPAH_enfiler(&((*p_fdp) -> fileSuivante), a);
	}
}
*/

void FDPAH_enfiler(FileDePriorite *p_fdp, ArbreDeHuffman a) {
    if (FDPAH_estVide(*p_fdp) || ADH_obtenirFrequence(a) < ADH_obtenirFrequence((*p_fdp)->arbre)
        || (ADH_obtenirFrequence(a) == ADH_obtenirFrequence((*p_fdp)->arbre)
            && ADH_obtenirOctet(a) < ADH_obtenirOctet((*p_fdp)->arbre))) 
	{

        FileDePriorite p_noeud = (FileDePriorite)malloc(sizeof(NoeudFileDePriorite));
        p_noeud->arbre = a;
        p_noeud->fileSuivante = *p_fdp;

        *p_fdp = p_noeud;
    } else {
        FDPAH_enfiler(&((*p_fdp)->fileSuivante), a);
    }
}

ArbreDeHuffman FDPAH_obtenirElementEtDefiler(FileDePriorite *p_fdp) {
	assert(!FDPAH_estVide(*p_fdp));
	ArbreDeHuffman a = (*p_fdp) -> arbre;
	FileDePriorite* p_temp = p_fdp;
	p_fdp = &((*p_temp) -> fileSuivante);
	free(p_temp);
	return a;
}
