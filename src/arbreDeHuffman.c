#include "arbreDeHuffman.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

ArbreDeHuffman arbreDeHuffman(int octet, int frequence) // Changer l'entrée de cette fonction pour correspondre aux Statistiques
{ 
    ArbreDeHuffman feuille = (ArbreDeHuffman)malloc(sizeof(ArbreDeHuffman));
    feuille->octet = octet;
    feuille->frequence = frequence;
    feuille->arbreGauche = NULL; //Je ne suis pas sûr que ça soit nécessaire
    feuille->arbreDroit = NULL;
    return feuille;
}

unsigned int obtenirOctet(ArbreDeHuffman arbreDeHuffman) 
{
    return arbreDeHuffman->octet;
}

unsigned int obtenirFrequence(ArbreDeHuffman arbreDeHuffman) 
{
    return arbreDeHuffman->frequence;
}

ArbreDeHuffman fusionner(ArbreDeHuffman arbreGauche, ArbreDeHuffman arbreDroit)  
{
    ArbreDeHuffman racine = (ArbreDeHuffman)malloc(sizeof(ArbreDeHuffman));
    racine->arbreGauche = arbreGauche;
    racine->arbreDroit = arbreDroit;
    racine->octet = OCTET_VIDE;
    racine->frequence = obtenirFrequence(arbreGauche) + obtenirFrequence(arbreDroit);
    return racine;
}

bool estUneFeuille(ArbreDeHuffman arbreDeHuffman) 
{
    return arbreDeHuffman->octet != OCTET_VIDE;
}

ArbreDeHuffman obtenirFilsGauche(ArbreDeHuffman arbreDeHuffman) 
{
    return arbreDeHuffman->arbreGauche;
}

ArbreDeHuffman obtenirFilsDroit(ArbreDeHuffman arbreDeHuffman) 
{
    return arbreDeHuffman->arbreDroit;
}