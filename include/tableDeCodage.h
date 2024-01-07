#ifndef __TABLE_DE_CODAGE__
#define __TABLE_DE_CODAGE__

#include <stdbool.h>

#include "codeBinaire.h"
#include "octet.h"

typedef struct TDC_TableDeCodage {
    CB_CodeBinaire tableDeCodeBinaire[MAX_OCTET];
    bool tableDePresence[MAX_OCTET];
} TDC_TableDeCodage;

TDC_TableDeCodage TDC_creerTableCodage();
void TDC_ajouterCodage(TDC_TableDeCodage* p_tdc, O_Octet o, CB_CodeBinaire cb);
CB_CodeBinaire TDC_octetVersCodeBinaire(TDC_TableDeCodage tdc, O_Octet o);
bool TDC_octetPresent(TDC_TableDeCodage tdc, O_Octet o);

#endif