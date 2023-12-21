#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "compression.h"
#include "octet.h"
#include "arbreDeHuffman.h"
#include "fileDePrioriteDArbreDeHuffman.h"
#include "arbreDeHuffman.h"
#include "tableDeCodage.h"
#include "statistiques.h"
#include "codeBinaire.h"
#include "construireArbreDeHuffman.h"

void C_obtenirStatistiquesEtTailleFichier(FILE *f, Statistiques *s,  unsigned long *taille) {
    rewind(f);

    S_statistiques(s);
    *taille = 0;

    short o;
    while ((o = fgetc(f)) != EOF) {
        S_incrementerOccurence(s, O_naturelVersOctet(o));
        (*taille)++;
    }
}

void C_obtenirTableDeCodageRecursif(TableDeCodage *tdc, ArbreDeHuffman a, CodeBinaire cb) {
    CodeBinaire cbCopie;
    
    if (ADH_estUneFeuille(a)) {
        TDC_ajouterCodage(tdc, ADH_obtenirOctet(a), cb);
    }
    else {
        memcpy(&cbCopie, &cb, sizeof(CodeBinaire));
        
        CB_ajouterBit(&cbCopie, bitA0);
        C_obtenirTableDeCodageRecursif(tdc, ADH_obtenirFilsGauche(a), cbCopie);
        CB_ajouterBit(&cb, bitA1);
        C_obtenirTableDeCodageRecursif(tdc, ADH_obtenirFilsDroit(a), cb);
    }

}

TableDeCodage C_obtenirTableDeCodage(ArbreDeHuffman a) {
    TableDeCodage tdc = TDC_creerTableCodage();

    if(ADH_estUneFeuille(a)) { 
        TDC_ajouterCodage(&tdc, ADH_obtenirOctet(a), CB_creerCodeBinaire(bitA0));
    }
    else {
        CodeBinaire cbGauche = CB_creerCodeBinaire(bitA0);
        CodeBinaire cbDroit = CB_creerCodeBinaire(bitA1);
        C_obtenirTableDeCodageRecursif(&tdc, ADH_obtenirFilsGauche(a), cbGauche);
        C_obtenirTableDeCodageRecursif(&tdc, ADH_obtenirFilsDroit(a), cbDroit);
    }
    return tdc;
}

void C_ecrireIdentifiant(FILE *f) {
    unsigned short identifiant = IDENTIFIANT;
    fwrite(&identifiant, sizeof(unsigned short), 1, f);
}

void C_ecrireTailleFichier(FILE *f, unsigned long long taille) {
    fwrite(&taille, sizeof(unsigned long long), 1, f);
}

void C_ecrireStatistiques(FILE *f, Statistiques s) {
    unsigned short o;
    for (o = 0; o < MAX_OCTET; o++) {
        unsigned long occurence = S_obtenirOccurence(s, O_naturelVersOctet(o));
        fwrite(&occurence, sizeof(unsigned long), 1, f);
    }
}

Octet C_codeBinaireEnOctet(CodeBinaire cb) {
    assert(CB_obtenirLongueur(cb) == MAX_CB);
    return O_creerOctet(CB_obtenirIemeBit(cb, 0),
                        CB_obtenirIemeBit(cb, 1),
                        CB_obtenirIemeBit(cb, 2),
                        CB_obtenirIemeBit(cb, 3),
                        CB_obtenirIemeBit(cb, 4),
                        CB_obtenirIemeBit(cb, 5),
                        CB_obtenirIemeBit(cb, 6),
                        CB_obtenirIemeBit(cb, 7));
}
void C_concatenerCodeBinaireDansFichier(FILE *f, CodeBinaire *p_cbTemp, CodeBinaire cb) {
    unsigned short i, j;

    if (CB_obtenirLongueur(*p_cbTemp) == 8)
        *p_cbTemp = cb;
    
    unsigned short tailleCbTemp = CB_obtenirLongueur(*p_cbTemp);
    unsigned short tailleCb = CB_obtenirLongueur(cb);
    unsigned short tailleTotale = tailleCbTemp + tailleCb;

    if (tailleTotale > 8) {
        for (i = 0; i < MAX_CB - tailleCbTemp; i++)
            CB_ajouterBit(p_cbTemp, CB_obtenirIemeBit(cb, i));
        unsigned char octet = O_octetVersNaturel(C_codeBinaireEnOctet(*p_cbTemp));
        fwrite(&octet, sizeof(unsigned char), 1, f);

        *p_cbTemp = CB_creerCodeBinaire(CB_obtenirIemeBit(cb, i+1));
        for (j = i + 2; j < tailleCb; j++)
            CB_ajouterBit(p_cbTemp, CB_obtenirIemeBit(cb, j));
    }
    else {
        for (i = tailleCbTemp; i < tailleTotale; i++)
            CB_ajouterBit(p_cbTemp, CB_obtenirIemeBit(cb, i));

        if (CB_obtenirLongueur(*p_cbTemp) == 8) {
            unsigned char octet = O_octetVersNaturel(C_codeBinaireEnOctet(*p_cbTemp));
            fwrite(&octet, sizeof(unsigned char), 1, f);
        }
    }
}

void C_encoder(FILE *f, FILE *fbCompresse, TableDeCodage tdc) {
    unsigned short i;

    // Création d'un code binaire temporaire initalisé à 8 bits pour rentrer dans la première condition de la fonction concatenerCodeBinaireEnOctet
    CodeBinaire cbTemp = CB_creerCodeBinaire(bitA0);
    for (i = 1; i < MAX_CB; i++)
        CB_ajouterBit(&cbTemp, bitA0);
    
    // Boucle d'encodage
    CodeBinaire cb;
    short o;
    while ((o = fgetc(f)) != EOF) {
        cb = TDC_octetVersCodeBinaire(tdc, O_naturelVersOctet(o));
        C_concatenerCodeBinaireDansFichier(fbCompresse, &cbTemp, cb);
    }

    // Ecriture du dernier octet si le dernier code binaire n'est pas de taille 8 et n'a donc pas été écrit dans le fichier compressé
    if (CB_obtenirLongueur(cbTemp) < 8) {
        for (i = CB_obtenirLongueur(cbTemp); i < MAX_CB; i++)
            CB_ajouterBit(&cbTemp, bitA0);
        unsigned char octet = O_octetVersNaturel(C_codeBinaireEnOctet(cbTemp));
        fwrite(&octet, sizeof(unsigned char), 1, fbCompresse);
    }
}

void C_compresser(FILE *f, char *filename) {
    Statistiques s;
    unsigned long taille;

    rewind(f);
    FILE *fbCompresse = fopen(strcat(filename,".huff"), "wb");

    C_obtenirStatistiquesEtTailleFichier(f, &s, &taille);

    // Ecriture des données importantes avant d'encoder
    C_ecrireIdentifiant(fbCompresse);
    C_ecrireTailleFichier(fbCompresse, taille);
    if(taille > 0) {
        C_ecrireStatistiques(fbCompresse, s);
        C_encoder(f, fbCompresse, C_obtenirTableDeCodage(CADH_construireArbreDeHuffman(s)));
    }
   
    fclose(fbCompresse);
}