#include "fileDePrioriteDArbreDeHuffman.h"

FileDePriorite FDPAH_fileDePriorite() {
	return NULL;
}

bool FDPAH_estVide(FileDePriorite fdp) {
	return (fdp == NULL);
}

void FDPAH_enfiler(FileDePriorite *p_fdp, ArbreDeHuffman a) {
	if ((FDPAH_estVide(*p_fdp)) || (a < *p_fdp.arbre)) {
		FileDePriorite* p_temp = p_fdp;
		//allocation de la taille de file
		*p_file.arbre = a;
		*p_file.fileSuivante = p_temp;
	}
	else {
		FDPAH_enfiler(*p_file.fileSuivante, a);
	}
}

ArbreDeHuffman FDPAH_obtenirElementEtDefiler(FileDePriorite *p_fdp) {
	ArbreDeHuffman a = *p_fdp.arbre;
	FileDePriorite* p_temp = p_fdp;
	p_file = &(*temp.fileSuivante);
	//désallocation de temp
	return a;
}
