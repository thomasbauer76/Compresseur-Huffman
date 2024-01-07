#include <stdio.h>

#include "arbreDeHuffman.h"
#include "fileDePrioriteDArbreDeHuffman.h"
#include "octet.h"
#include "statistiques.h"

FDPAH_FileDePriorite CADH_construireFileDePriorite(Statistiques s) {
    FDPAH_FileDePriorite fdp;
    O_Octet octet;
    unsigned long occurence;

    fdp = FDPAH_fileDePriorite();

    unsigned short o;
    for (o = 0; o < MAX_OCTET; o++) {
        octet = O_naturelVersOctet(o);
        occurence = S_obtenirOccurence(s, octet);

        if (occurence > 0) {
            FDPAH_enfiler(&fdp, ADH_arbreDeHuffman(octet, occurence));
        }
    }

    return fdp;
}

ADH_ArbreDeHuffman CADH_construireArbreDeHuffman(Statistiques s) {
    FDPAH_FileDePriorite fdp;
    bool dernierElement;
    ADH_ArbreDeHuffman a1, a2, aFusion;

    fdp = CADH_construireFileDePriorite(s);
    dernierElement = 0;
    while (!(dernierElement)) {
        a1 = FDPAH_obtenirElementEtDefiler(&fdp);
        if (FDPAH_estVide(fdp)) {
            dernierElement = true;
        } else {
            a2 = FDPAH_obtenirElementEtDefiler(&fdp);
            aFusion = ADH_fusionner(a1, a2);
            FDPAH_enfiler(&fdp, aFusion);
        }
    }
    return a1;
}