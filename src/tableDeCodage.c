#include "tableDeCodage.h"
#include "octet.h"

TableDeCodage TDC_creerTableCodage(){
   TableDeCodage tdc; 
    for(unsigned short octet=0; octet<255; octet++){
        tdc.tableDePresence[octet]=0;
    }
    return tdc;
}

void TDC_ajouterCodage(TableDeCodage* tdc, Octet o, CodeBinaire cb){
    int oc= O_octetVersNaturel(o);
    tdc->tableDeCodeBinaire[oc]= cb;
    (*tdc).tableDePresence[oc]= 1;
}

CodeBinaire TDC_octetVersCodeBinaire(TableDeCodage tdc, Octet o){
    return tdc.tableDeCodeBinaire[O_octetVersNaturel(o)];
}   


bool TDC_octetPresent(TableDeCodage tdc, Octet o){
    return tdc.tableDePresence[O_octetVersNaturel(o)];
}

