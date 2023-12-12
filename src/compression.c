#include <stdio.h>
#include <string.h>
#include "tableDeCodage.h"
#include "codeBinaire.h"
#include "compression.h"

void concatenerCodeBinaireEnOctet(CodeBinaire cb, FILE *fb) {

}

void encoder(FILE *f, char *filename, TableDeCodage tdc) {
    rewind(f);
    FILE *fbCompresse = fopen(strcat(filename,".huff"), "w");
    unsigned char c;
    while ((c = fgetc(f)) != EOF) {
        
    }
}

void compresser(FILE *f) {

}