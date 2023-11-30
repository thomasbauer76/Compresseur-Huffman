#include "codeBinaire.h"

CodeBinaire CB_creerCodeBinaire(Bit b) {
    CodeBinaire cb;
    cb.tableBit[0] = b;
    cb.nbElements = 1;
    return cb;
}

Bit CB_obtenirIemeBit(CodeBinaire cb, unsigned short i) {
    return cb.tableBit[i];
}

unsigned short CB_obtenirLongueur(CodeBinaire cb) {
    return cb.nbElements;
}

void CB_ajouterBit(CodeBinaire *cb, Bit b) {
    cb->tableBit[CB_obtenirLongueur(*cb)] = b;
    cb->nbElements++;
}