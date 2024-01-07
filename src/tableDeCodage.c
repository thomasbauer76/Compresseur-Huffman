#include "tableDeCodage.h"

#include <assert.h>

#include "octet.h"

TableDeCodage TDC_creerTableCodage() {
    TableDeCodage tdc;
    for (unsigned short octet = 0; octet < MAX_OCTET; octet++) {
        tdc.tableDePresence[octet] = 0;
    }
    return tdc;
}

bool TDC_octetPresent(TableDeCodage tdc, O_Octet o) {
    return tdc.tableDePresence[O_octetVersNaturel(o)];
}

void TDC_ajouterCodage(TableDeCodage *tdc, O_Octet o, CB_CodeBinaire cb) {
    assert(!TDC_octetPresent(*tdc, o));
    int octet = O_octetVersNaturel(o);
    tdc->tableDeCodeBinaire[octet] = cb;
    tdc->tableDePresence[octet] = 1;
}

CB_CodeBinaire TDC_octetVersCodeBinaire(TableDeCodage tdc, O_Octet o) {
    return tdc.tableDeCodeBinaire[O_octetVersNaturel(o)];
}