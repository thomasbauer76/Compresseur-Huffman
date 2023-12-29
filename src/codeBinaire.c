#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "codeBinaire.h"

CodeBinaire CB_creerCodeBinaire(Bit b) {
    CodeBinaire cb;
    if (b == bitA1)
        cb.codeBinaire = 1;
    else
        cb.codeBinaire = 0;
    cb.nbBits = 1;
    return cb;
}

unsigned short CB_obtenirLongueur(CodeBinaire cb) {
    return cb.nbBits;
}

void CB_ajouterBit(CodeBinaire *cb, Bit b) {
    if (b == bitA1)
        cb->codeBinaire = cb->codeBinaire + (1 << cb->nbBits);
    cb->nbBits++;
}

Bit CB_obtenirIemeBit(CodeBinaire cb, unsigned short i) {
    assert(i < CB_obtenirLongueur(cb));
    return (cb.codeBinaire >> i) & 1;
}