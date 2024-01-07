#include "codeBinaire.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

CB_CodeBinaire CB_creerCodeBinaire(O_Bit b) {
    CB_CodeBinaire cb;
    cb.codeBinaire = b;
    cb.nbBits = 1;
    return cb;
}

unsigned short CB_obtenirLongueur(CB_CodeBinaire cb) {
    return cb.nbBits;
}

void CB_ajouterBit(CB_CodeBinaire *cb, O_Bit b) {
    cb->codeBinaire = cb->codeBinaire + (b << cb->nbBits);
    cb->nbBits++;
}

O_Bit CB_obtenirIemeBit(CB_CodeBinaire cb, unsigned short i) {
    assert(i < cb.nbBits);
    return (cb.codeBinaire >> i) & 1;
}