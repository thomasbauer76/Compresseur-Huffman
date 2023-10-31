#include "fileDePriorite.h"
#include "arbreDeHuffman.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

FileDePriorite fileDePriorite() 
{
    return NULL;
}

bool estVide(FileDePriorite fileDePriorite) 
{
    return fileDePriorite == NULL;
}

void enfiler(FileDePriorite *fileDePriorite, ArbreDeHuffman arbreDeHuffman) 
{
    if (estVide(*fileDePriorite) || 
        obtenirFrequence(arbreDeHuffman) < obtenirFrequence((*fileDePriorite)->arbreDeHuffman) ||
        (obtenirFrequence(arbreDeHuffman) == obtenirFrequence((*fileDePriorite)->arbreDeHuffman) &&
         obtenirOctet(arbreDeHuffman) < obtenirOctet((*fileDePriorite)->arbreDeHuffman))) 
    {
        FileDePriorite temp = *fileDePriorite;
        *fileDePriorite = (FileDePriorite)malloc(sizeof(FileDePriorite));
        (*fileDePriorite)->arbreDeHuffman = arbreDeHuffman;
        (*fileDePriorite)->fileSuivante = temp;
    }
    else
        enfiler(&(*fileDePriorite)->fileSuivante,arbreDeHuffman);
}

ArbreDeHuffman obtenirArbreEtDefiler(FileDePriorite *fileDePriorite) 
{
    FileDePriorite temp = *fileDePriorite;
    ArbreDeHuffman arbre = temp->arbreDeHuffman;
    *fileDePriorite = temp->fileSuivante;
    free(temp);
    return arbre;
}