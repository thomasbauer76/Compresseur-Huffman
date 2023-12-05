#ifndef __CODE_BINAIRE__
#define __CODE_BINAIRE__


#include "octet.h"

#define MAX_CB

typedef struct CodeBinaire {
    Bit tableBit[MAX_CB];
    unsigned short nbElements;
} CodeBinaire;

CodeBinaire CB_creerCodeBinaire(Bit b);
Bit CB_obtenirIemeBit(CodeBinaire cb, unsigned short i);
unsigned short CB_obtenirLongueur(CodeBinaire cb);
void CB_ajouterBit(CodeBinaire *p_cb, Bit b);


#endif