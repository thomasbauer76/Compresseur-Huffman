#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "statistiques.h"
#include "fileDePrioriteDArbreDeHuffman.h"
#include "codeBinaire.h"

int init_suite_success(void) {
    return 0;
}

int clean_suite_success(void) {
    return 0;
}


/* Tests statistiques.c */

void test_statistiques_vides(void) {
    Statistiques s;
    S_statistiques(&s);

    for(unsigned short o = 0; o < MAX_OCTET; o++) {
        CU_ASSERT_EQUAL(S_obtenirOccurence(s,o),0);
    }
}

void test_statistiques_incrementees(void) {
    Statistiques s;
    S_statistiques(&s);

    Octet o = O_naturelVersOctet(241);
    unsigned long ancienneOccurence = S_obtenirOccurence(s,o);

    S_incrementerOccurence(&s,o);
    unsigned long nouvelleOccurence = S_obtenirOccurence(s,o);

    CU_ASSERT_EQUAL(nouvelleOccurence,ancienneOccurence+1);
}

void test_statistiques_fixer_occurence(void) {
    Statistiques s;
    S_statistiques(&s);

    Octet o = O_naturelVersOctet(241);
    unsigned long n = 1234;
    S_fixerOccurence(&s,o,n);

    CU_ASSERT_EQUAL(S_obtenirOccurence(s,o),n);
}


/* Tests codeBinaire.c */

void test_creation_codebinaire(void) {
  Bit b = bitA0;
  CodeBinaire cb = CB_creerCodeBinaire(b);
  CU_ASSERT_EQUAL(CB_obtenirLongueur(cb), 1);
  CU_ASSERT_EQUAL(CB_obtenirIemeBit(cb, 0), b);
}

void test_ajout_bit(void) {
  CodeBinaire cb = CB_creerCodeBinaire(bitA0);
  unsigned short ancienneLongueur = CB_obtenirLongueur(cb);
  Bit b = bitA1;
  CB_ajouterBit(&cb,b);
  unsigned short nouvelleLongueur = CB_obtenirLongueur(cb);
  CU_ASSERT_EQUAL(nouvelleLongueur, ancienneLongueur+1);
  CU_ASSERT_EQUAL(CB_obtenirIemeBit(cb, nouvelleLongueur-1), b);
}

/* Tests arbreDeHuffman.c */

void test_creation_arbreDeHuffman(void) {
  Octet o; 
  unsigned long f;
 
  CU_ASSERT(ADH_estUneFeuille(ADH_arbreDeHuffman(o,f)));
  CU_ASSERT_EQUAL(ADH_obtenirFrequence(ADH_arbreDeHuffman(o,f)), f);
}

void test_fussioner_ADH(void) {
  Octet o;
  unsigned long n;
  ArbreDeHuffman ad = ADH_arbreDeHuffman(o, n);
  ArbreDeHuffman ag = ADH_arbreDeHuffman(o, n);
  
  CU_ASSERT_EQUAL(ADH_obtenirFrequence(ADH_fusionner(ad,ag)),ADH_obtenirFrequence(ag) + ADH_obtenirFrequence(ad));
  CU_ASSERT_EQUAL(ADH_obtenirFilsDroit(ADH_fusionner(ag,ad)),ag);
  CU_ASSERT_EQUAL(ADH_obtenirFilsGauche(ADH_fusionner(ag,ad)),ad);
  CU_ASSERT(ADH_estUneFeuille(ADH_fusionner(ag,ad)));
}

void test_estUneFeuille(void) {
  Octet o; 
  unsigned long f;
  
  CU_ASSERT(ADH_estUneFeuille(ADH_arbreDeHuffman(o, f)));
}

void test_obtenir_octet(void) {
  Octet o; 
  unsigned long f;
  
  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_arbreDeHuffman(o, f)), o);
}

void test_obtenir_frequence_ADH(void) {
  Octet o; 
  unsigned long f;

  ArbreDeHuffman ad = ADH_arbreDeHuffman(o, f);
  ArbreDeHuffman ag = ADH_arbreDeHuffman(o, f);

  
  CU_ASSERT_EQUAL(ADH_obtenirFrequence(ADH_fusionner(ad, ag)), ADH_obtenirFrequence(ag) + ADH_obtenirFrequence(ad));
  CU_ASSERT_EQUAL(ADH_obtenirFrequence(ADH_arbreDeHuffman(o, f)), f);
}

void test_obtenir_fils_gauche(void) {
  Octet o; 
  unsigned long f;

  ArbreDeHuffman ad = ADH_arbreDeHuffman(o, f);
  ArbreDeHuffman ag = ADH_arbreDeHuffman(o, f);

  CU_ASSERT_EQUAL(ADH_obtenirFilsGauche(ADH_fusionner(ag,ad)), ad);
}

void test_obtenir_fils_droit(void) {
  Octet o; 
  unsigned long f;

  ArbreDeHuffman ad = ADH_arbreDeHuffman(o, f);
  ArbreDeHuffman ag = ADH_arbreDeHuffman(o, f);

  CU_ASSERT_EQUAL(ADH_obtenirFilsDroit(ADH_fusionner(ag,ad)), ag);
}

/* Tests FileDePriorite.c */

void test_creation_filedePriorite(void) {
  FileDePriorite fdp;
  fdp = FDPAH_fileDePriorite();

  CU_ASSERT(FDPAH_estVide(FDPAH_fileDePriorite()));
}

void test_estVide_filedePriorite(void) {
  FileDePriorite fdp;
  fdp = FDPAH_fileDePriorite();
  

  CU_ASSERT(FDPAH_estVide(FDPAH_fileDePriorite()));
}

void test_enfiler(void) {
  Octet o; 
  unsigned long f;
  FileDePriorite fdp;
  fdp = FDPAH_fileDePriorite();
  ArbreDeHuffman a = ADH_arbreDeHuffman(o, f);
  FDPAH_enfiler(&fdp, a);
  CU_ASSERT(FDPAH_estVide(FDPAH_fileDePriorite()));
  CU_ASSERT(FDPAH_estVide(&fdp));
}

void test_obtenirElement_et_Defiler(void) {
  Octet o; 
  unsigned long f;
  FileDePriorite fdp;
  fdp = FDPAH_fileDePriorite();
  ArbreDeHuffman a = ADH_arbreDeHuffman(o, f);
  FDPAH_enfiler(&fdp, a);
  CU_ASSERT_EQUAL((FDPAH_obtenirElementEtDefiler(&fdp)), fdp);
  CU_ASSERT_EQUAL((FDPAH_obtenirElementEtDefiler(&fdp)), a);
}


int main(int argc, char** argv){

  /* initialisation du registre de tests */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* ajout d'une suite de test pour statistiques.c */
  CU_pSuite pSuiteStatistiques = CU_add_suite("Test statistiques", init_suite_success, clean_suite_success);
  if (NULL == pSuiteStatistiques) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Ajout des tests à la suite statistiques */
  if ((NULL == CU_add_test(pSuiteStatistiques, "Création des statistiques aux occurences vides", test_statistiques_vides)) 
    || (NULL == CU_add_test(pSuiteStatistiques, "Incrementation de l'occurence d'un octet", test_statistiques_incrementees))
    || (NULL == CU_add_test(pSuiteStatistiques, "Fixer le nombre d'occurences d'un octet", test_statistiques_fixer_occurence))
      ) 
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* ajout d'une suite de test pour codeBinaire.c */
  CU_pSuite pSuiteCodeBinaire = CU_add_suite("Test codeBinaire", init_suite_success, clean_suite_success);
  if (NULL == pSuiteCodeBinaire) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Ajout des tests à la suite codeBinaire */
  if ((NULL == CU_add_test(pSuiteCodeBinaire, "Creation Code Binaire", test_creation_codebinaire))
    || (NULL == CU_add_test(pSuiteCodeBinaire, "Ajout d'un bit", test_ajout_bit))
      ) 
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* Lancement des tests */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  printf("\n");
  CU_basic_show_failures(CU_get_failure_list());
  printf("\n\n");

  /* Nettoyage du registre */
  CU_cleanup_registry();
  return CU_get_error();
}