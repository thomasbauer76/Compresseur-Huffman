#include <assert.h>
#include "tableDeCodage.h"
#include "octet.h"

TableDeCodage TDC_creerTableCodage(){
   TableDeCodage tdc; 
    for(unsigned short octet = 0; octet < MAX_OCTET; octet++){
        tdc.tableDePresence[octet] = 0;
    }
    return tdc;
}

bool TDC_octetPresent(TableDeCodage tdc, Octet o){
    return tdc.tableDePresence[O_octetVersNaturel(o)];
}

void TDC_ajouterCodage(TableDeCodage *tdc, Octet o, CodeBinaire cb){
    assert(!TDC_octetPresent(*tdc, o));
    int octet = O_octetVersNaturel(o);
    tdc->tableDeCodeBinaire[octet] = cb;
    tdc->tableDePresence[octet] = 1;
}

CodeBinaire TDC_octetVersCodeBinaire(TableDeCodage tdc, Octet o){
    assert(TDC_octetPresent(tdc, o));
    return tdc.tableDeCodeBinaire[O_octetVersNaturel(o)];
}