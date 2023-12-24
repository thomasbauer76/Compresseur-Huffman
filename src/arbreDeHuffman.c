#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "arbreDeHuffman.h"


ArbreDeHuffman ADH_arbreDeHuffman(Octet o, unsigned long n){
    ArbreDeHuffman a = (ArbreDeHuffman)malloc(sizeof(NoeudArbreDeHuffman));
    a->octet = o;
    a->frequence = n;
    a->estUneFeuille = true;  
    a->arbreGauche = NULL;
    a->arbreDroit = NULL;
    return a;
}

unsigned long ADH_obtenirFrequence(ArbreDeHuffman a) {
    return a->frequence;
}

ArbreDeHuffman ADH_fusionner(ArbreDeHuffman ag, ArbreDeHuffman ad) {
    ArbreDeHuffman racine = (ArbreDeHuffman)malloc(sizeof(NoeudArbreDeHuffman));
    racine->arbreGauche = ag;
    racine->arbreDroit = ad;
    racine->estUneFeuille = false;
    racine->frequence = ADH_obtenirFrequence(ag) + ADH_obtenirFrequence(ad);
    return racine;
}

bool ADH_estUneFeuille(ArbreDeHuffman a) {
    return a->estUneFeuille;
}

ArbreDeHuffman ADH_obtenirFilsGauche(ArbreDeHuffman a) {
    assert(!ADH_estUneFeuille(a));
    return a->arbreGauche;
}

Octet ADH_obtenirOctet(ArbreDeHuffman a){
    assert(ADH_estUneFeuille(a));
    return a->octet;
}

ArbreDeHuffman ADH_obtenirFilsDroit(ArbreDeHuffman a) {
    assert(!ADH_estUneFeuille(a));
    return a->arbreDroit;
}

void ADH_liberer(ArbreDeHuffman a) {
    if (!(ADH_estUneFeuille(a))) {
        ADH_liberer(ADH_obtenirFilsDroit(a));
        ADH_liberer(ADH_obtenirFilsGauche(a));
    }
    free(a);
}