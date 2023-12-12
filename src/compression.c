#include <stdio.h>
#include <string.h>
#include "tableDeCodage.h"
#include "codeBinaire.h"
#include "compression.h"

void concatenerCodeBinaireEnOctet(CodeBinaire cb, FILE *fb) {

}

void encoder(FILE *f, char *filename, TableDeCodage tdc) {
    FILE *fbCompresse = fopen(strcat(filename,".huff"), "wb");
    rewind(f);

    CodeBinaire cb;
    int o;
    while ((o = fgetc(f)) != EOF) {
        cb = TDC_octetVersCodeBinaire(tdc,O_naturelVersOctet(o));
        concatenerCodeBinaireEnOctet(cb,fbCompresse);
    }

    fclose(fbCompresse);
}

void compresser(FILE *f, char *filename) {

}