#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "codeBinaire.h"

CodeBinaire CB_creerCodeBinaire(Bit b) {
    CodeBinaire cb;
    cb.codeBinaire = b;
    cb.nbBits = 1;
    return cb;
}

unsigned short CB_obtenirLongueur(CodeBinaire cb) {
    return cb.nbBits;
}

void CB_ajouterBit(CodeBinaire *cb, Bit b) {
    assert(CB_obtenirLongueur(*cb) <= MAX_CB);
    cb->codeBinaire = cb->codeBinaire + (b << cb->nbBits);
    cb->nbBits++;
}

Bit CB_obtenirIemeBit(CodeBinaire cb, unsigned short i) {
    return (cb.codeBinaire >> i) & 1;
}