#include <assert.h>
#include "codeBinaire.h"

CodeBinaire CB_creerCodeBinaire(Bit b) {
    CodeBinaire cb;
    cb.tableBit[0] = b;
    cb.nbElements = 1;
    return cb;
}

void CB_ajouterBit(CodeBinaire *cb, Bit b) {
    assert(CB_obtenirLongueur(*cb) <= MAX_CB );
    cb->tableBit[CB_obtenirLongueur(*cb)] = b;
    cb->nbElements++;
}

Bit CB_obtenirIemeBit(CodeBinaire cb, unsigned short i) {
    assert(i < CB_obtenirLongueur(cb));
    return cb.tableBit[i];
}

unsigned short CB_obtenirLongueur(CodeBinaire cb) {
    return cb.nbElements;
}