#include "fileDePriorite.h"
#include "arbreDeHuffman.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

FileDePriorite fileDePriorite() {
    return NULL;
}

bool estVide(FileDePriorite fileDePriorite) {
    return fileDePriorite == NULL;
}

void fixerFileSuivante(FileDePriorite *fileDePriorite, ArbreDeHuffman arbreDeHuffman) {
    FileDePriorite temp = *fileDePriorite;
    *fileDePriorite = (FileDePriorite)malloc(sizeof(FileDePriorite));
    (*fileDePriorite)->arbreDeHuffman = arbreDeHuffman;
    (*fileDePriorite)->fileSuivante = temp;
}

void enfiler(FileDePriorite *fileDePriorite, ArbreDeHuffman arbreDeHuffman) {
    if (estVide(*fileDePriorite) || obtenirFrequence((*fileDePriorite)->arbreDeHuffman) >= obtenirFrequence(arbreDeHuffman)) // Changer condition pour gérer aussi l'ordre alphabétique
        fixerFileSuivante(fileDePriorite,arbreDeHuffman);
    else
        enfiler(&(*fileDePriorite)->fileSuivante,arbreDeHuffman);
}

ArbreDeHuffman obtenirArbreEtDefiler(FileDePriorite *fileDePriorite) {
    FileDePriorite temp = *fileDePriorite;
    ArbreDeHuffman arbre = temp->arbreDeHuffman;
    *fileDePriorite = temp->fileSuivante;
    free(temp);
    return arbre;
}