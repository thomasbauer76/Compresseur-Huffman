#ifndef __TABLE_DE_CODAGE__
#define __TABLE_DE_CODAGE__


#include <stdbool.h>
#include "octet.h"
#include "codeBinaire.h"

typedef struct TableDeCodage {
    CodeBinaire tableDeCodeBinaire[MAX_OCTET];
    bool tableDePresence[MAX_OCTET];
} TableDeCodage;

TableDeCodage TDC_creerTableCodage();
void TDC_ajouterCodage(TableDeCodage* p_tdc, Octet o, CodeBinaire cb);
CodeBinaire TDC_octetVersCodeBinaire(TableDeCodage tdc, Octet o);
bool TDC_octetPresent(TableDeCodage tdc, Octet o);


#endif