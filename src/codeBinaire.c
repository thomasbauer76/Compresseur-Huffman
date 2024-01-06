#include "codeBinaire.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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
    cb->codeBinaire = cb->codeBinaire + (b << cb->nbBits);
    cb->nbBits++;
}

Bit CB_obtenirIemeBit(CodeBinaire cb, unsigned short i) {
    assert(i < cb.nbBits);
    return (cb.codeBinaire >> i) & 1;
}