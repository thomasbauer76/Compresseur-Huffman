#include "arbreDeHuffman.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

ADH_ArbreDeHuffman ADH_arbreDeHuffman(O_Octet o, unsigned long n) {
    ADH_ArbreDeHuffman a = (ADH_ArbreDeHuffman)malloc(sizeof(ADH_Noeud));
    a->octet = o;
    a->frequence = n;
    a->estUneFeuille = true;
    a->arbreGauche = NULL;
    a->arbreDroit = NULL;
    return a;
}

unsigned long ADH_obtenirFrequence(ADH_ArbreDeHuffman a) {
    return a->frequence;
}

ADH_ArbreDeHuffman ADH_fusionner(ADH_ArbreDeHuffman ag, ADH_ArbreDeHuffman ad) {
    ADH_ArbreDeHuffman racine = (ADH_ArbreDeHuffman)malloc(sizeof(ADH_Noeud));
    racine->arbreGauche = ag;
    racine->arbreDroit = ad;
    racine->estUneFeuille = false;
    racine->frequence = ADH_obtenirFrequence(ag) + ADH_obtenirFrequence(ad);
    return racine;
}

bool ADH_estUneFeuille(ADH_ArbreDeHuffman a) {
    return a->estUneFeuille;
}

ADH_ArbreDeHuffman ADH_obtenirFilsGauche(ADH_ArbreDeHuffman a) {
    assert(!ADH_estUneFeuille(a));
    return a->arbreGauche;
}

O_Octet ADH_obtenirOctet(ADH_ArbreDeHuffman a) {
    assert(ADH_estUneFeuille(a));
    return a->octet;
}

ADH_ArbreDeHuffman ADH_obtenirFilsDroit(ADH_ArbreDeHuffman a) {
    assert(!ADH_estUneFeuille(a));
    return a->arbreDroit;
}

void ADH_liberer(ADH_ArbreDeHuffman a) {
    if (!(ADH_estUneFeuille(a))) {
        ADH_liberer(ADH_obtenirFilsGauche(a));
        ADH_liberer(ADH_obtenirFilsDroit(a));
    }
    free(a);
}