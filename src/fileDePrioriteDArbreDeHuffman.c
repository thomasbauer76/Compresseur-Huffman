#include "fileDePrioriteDArbreDeHuffman.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "arbreDeHuffman.h"

FDPAH_FileDePriorite FDPAH_fileDePriorite() {
    return NULL;
}

bool FDPAH_estVide(FDPAH_FileDePriorite fdp) {
    return (fdp == NULL);
}

void FDPAH_enfiler(FDPAH_FileDePriorite *p_fdp, ADH_ArbreDeHuffman a) {
    if (FDPAH_estVide(*p_fdp) || ADH_obtenirFrequence(a) < ADH_obtenirFrequence((*p_fdp)->arbre)
        // Si les deux fréquences sont égales, on compare (si on peut) leurs octets
        || (ADH_obtenirFrequence(a) == ADH_obtenirFrequence((*p_fdp)->arbre) && ADH_estUneFeuille(a) && ADH_estUneFeuille((*p_fdp)->arbre) && O_octetVersNaturel(ADH_obtenirOctet(a)) < O_octetVersNaturel(ADH_obtenirOctet((*p_fdp)->arbre)))) {
        FDPAH_FileDePriorite temp = (FDPAH_FileDePriorite)malloc(sizeof(FDPAH_Noeud));
        temp->arbre = a;
        temp->fileSuivante = *p_fdp;
        *p_fdp = temp;
    } else {
        FDPAH_enfiler(&((*p_fdp)->fileSuivante), a);
    }
}

ADH_ArbreDeHuffman FDPAH_obtenirElementEtDefiler(FDPAH_FileDePriorite *fdp) {
    assert(!FDPAH_estVide(*fdp));
    ADH_ArbreDeHuffman a = (*fdp)->arbre;
    FDPAH_FileDePriorite temp = *fdp;
    *fdp = temp->fileSuivante;
    free(temp);
    return a;
}
