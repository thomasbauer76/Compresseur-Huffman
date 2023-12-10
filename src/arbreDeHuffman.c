#include <stddef.h>
#include <stdlib.h>
#include "arbreDeHuffman.h"

ArbreDeHuffman ADH_arbreDeHuffman(Octet o, unsigned long n) {
    return NULL;
}

unsigned long ADH_obtenirFrequence(ArbreDeHuffman a) {
    return a->frequence;
}

//Question à poser au prof : faut-il faire disparaître (désallouer) arbre gauche et droit pour éviter une surchage de la mémoire ?
ArbreDeHuffman ADH_fusionner(ArbreDeHuffman ag, ArbreDeHuffman ad) {
    ArbreDeHuffman racine = (ArbreDeHuffman)malloc(sizeof(NoeudArbreDeHuffman));
    racine->arbreGauche = ag;
    racine->arbreDroit = ad;
    racine->estUneFeuille = false;
    racine->frequence = ADH_obtenirFrequence(ag) + ADH_obtenirFrequence(ad);
    return racine;
}

bool ADH_estUneFeuille(ArbreDeHuffman a) {
    return 0;
}

//Octet est un tableau, c'est donc une Entrée/Sortie
void ADH_obtenirOctet(ArbreDeHuffman a, Octet o) {

}

ArbreDeHuffman ADH_obtenirFilsGauche(ArbreDeHuffman a) {
    return a->arbreGauche;
}

ArbreDeHuffman ADH_obtenirFilsDroit(ArbreDeHuffman a) {
    return a->arbreDroit;
}