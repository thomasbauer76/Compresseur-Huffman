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

void FDPAH_enfiler(FileDePriorite *p_fdp, ArbreDeHuffman a) {
    if (FDPAH_estVide(*p_fdp) || ADH_obtenirFrequence(a) < ADH_obtenirFrequence((*p_fdp)->arbre)
        || (ADH_obtenirFrequence(a) == ADH_obtenirFrequence((*p_fdp)->arbre)
            && ADH_obtenirOctet(a) < ADH_obtenirOctet((*p_fdp)->arbre))) 
	{
        FileDePriorite temp = (FileDePriorite)malloc(sizeof(NoeudFileDePriorite));
        temp->arbre = a;
        temp->fileSuivante = *p_fdp;
        *p_fdp = temp;
    } else {
        FDPAH_enfiler(&((*p_fdp)->fileSuivante), a);
    }
}

ArbreDeHuffman FDPAH_obtenirElementEtDefiler(FileDePriorite *fdp) {
    assert(!FDPAH_estVide(*fdp));
    ArbreDeHuffman a = (*fdp)->arbre;
	FileDePriorite temp = *fdp;
    *fdp = temp->fileSuivante;
    free(temp);
	return a;
}

