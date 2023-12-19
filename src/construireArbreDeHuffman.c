#include <stdio.h>
#include "statistiques.h"
#include "arbreDeHuffman.h"
#include "fileDePrioriteDArbreDeHuffman.h"

FileDePriorite CADH_construireFileDePriorite(Statistiques s) {
    FileDePriorite fdp;
    Octet octet;
    unsigned long occurence;

    fdp = FDPAH_fileDePriorite();

    for(unsigned char o = 0; o < 256; o++) {
        octet = O_naturelVersOctet(o);
        occurence = S_obtenirOccurence(s, octet);

        if(occurence > 0) {
            FDPAH_enfiler(&fdp, ADH_arbreDeHuffman(octet, occurence));
        }
    }

    return fdp;
}

ArbreDeHuffman CADH_construireArbreDeHuffman(Statistiques s){
    return NULL;
}