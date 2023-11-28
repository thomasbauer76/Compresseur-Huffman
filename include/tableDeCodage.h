#ifndef __TABLE_DE_CODAGE__
#define __TABLE_DE_CODAGE__


#include <stdbool.h>
#include "octet.h"
#include "codeBinaire.h"

typedef struct TableDeCodage {
    Octet tableDOctet[256];
    bool tableDePresence[256];
} TableDeCodage;

TableDeCodage creerTableCodage();
void ajouterCodage(TableDeCodage* tdc, Octet o, CodeBinaire cb);
CodeBinaire octetVersCodeBinaire(TableDeCodage tdc, Octet o);
bool octetPresent(TableDeCodage tdc, Octet o);


#endif