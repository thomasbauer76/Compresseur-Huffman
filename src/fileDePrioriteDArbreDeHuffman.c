#include "fileDePrioriteDArbreDeHuffman.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "arbreDeHuffman.h"

FileDePriorite FDPAH_fileDePriorite() {
    return NULL;
}

bool FDPAH_estVide(FileDePriorite fdp) {
    return (fdp == NULL);
}

void FDPAH_enfiler(FileDePriorite *p_fdp, ArbreDeHuffman a) {
    if (FDPAH_estVide(*p_fdp) || ADH_obtenirFrequence(a) < ADH_obtenirFrequence((*p_fdp)->arbre)
        // Si les deux fréquences sont égales, on compare (si on peut) leurs octets
        || (ADH_obtenirFrequence(a) == ADH_obtenirFrequence((*p_fdp)->arbre) && ADH_estUneFeuille(a) && ADH_estUneFeuille((*p_fdp)->arbre) && O_octetVersNaturel(ADH_obtenirOctet(a)) < O_octetVersNaturel(ADH_obtenirOctet((*p_fdp)->arbre)))) {
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
