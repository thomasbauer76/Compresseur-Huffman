#include <stddef.h>
#include <stdlib.h>
#include "arbreDeHuffman.h"

ArbreDeHuffman ADH_arbreDeHuffman(Octet o, unsigned long n) {
    return NULL;
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
    return a->arbreGauche;
}

Octet obtenirOctet(ArbreDeHuffman a){
	if (a->estUneFeuille){
		return a->octet;}
	else{
		return EXIT_FAILURE;}
		}

ArbreDeHuffman ADH_obtenirFilsDroit(ArbreDeHuffman a) {
    return a->arbreDroit;
}

ArbreDeHuffman arbreDeHuffman(Octet o, unsigned int f){
	ArbreDeHuffman a = (ArbreDeHuffman)malloc(sizeof(ArbreDeHuffman));
	a->octet=o;
	a->frequence=f;
	a->arbreGauche=NULL;
	a->arbreDroit=NULL;
	
	return a;

}

