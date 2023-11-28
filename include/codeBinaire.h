#ifndef __CODE_BINAIRE__
#define __CODE_BINAIRE__


#include "octet.h"

typedef struct CodeBinaire {
    Bit tableBit[8];
    unsigned short nbElements;
} CodeBinaire;

CodeBinaire creerCodeBinaire(Bit b);
Bit obtenirIemeBit(CodeBinaire cb, unsigned short i);
unsigned short obtenirLongueur(CodeBinaire cb);
void ajouterBit(CodeBinaire *cb, Bit b);


#endif