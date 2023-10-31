#ifndef __ARBRE_DE_HUFFMAN__
#define __ARBRE_DE_HUFFMAN__


#include <stdbool.h>

#define OCTET_VIDE 0 //Valeur qui représente un arbre sans octet

typedef struct Racine *ArbreDeHuffman; 

struct Racine {
    unsigned int octet;
    unsigned int frequence;
    ArbreDeHuffman arbreGauche;
    ArbreDeHuffman arbreDroit;
};

ArbreDeHuffman arbreDeHuffman(int octet, int frequence); //Changer l'entrée de cette fonction pour correspondre aux Statistiques
unsigned int obtenirOctet(ArbreDeHuffman arbreDeHuffman);
unsigned int obtenirFrequence(ArbreDeHuffman arbreDeHuffman);
ArbreDeHuffman fusionner(ArbreDeHuffman arbreGauche, ArbreDeHuffman arbreDroit);
bool estUneFeuille(ArbreDeHuffman arbreDeHuffman);
ArbreDeHuffman obtenirFilsGauche(ArbreDeHuffman arbreDeHuffman);
ArbreDeHuffman obtenirFilsDroit(ArbreDeHuffman arbreDeHuffman);


#endif