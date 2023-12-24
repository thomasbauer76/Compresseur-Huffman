#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "statistiques.h"
#include "fileDePrioriteDArbreDeHuffman.h"
#include "codeBinaire.h"
#include "arbreDeHuffman.h"
#include "octet.h"
#include "tableDeCodage.h"


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
  Octet o = 65; 
  unsigned long f = 2;
  ArbreDeHuffman a = ADH_arbreDeHuffman(o,f);
  CU_ASSERT(ADH_estUneFeuille(a));
  CU_ASSERT_EQUAL(ADH_obtenirFrequence(a), f);
  free(a);
}

void test_fussioner_ADH(void) {
  Octet og = 241;
  unsigned long ng = 2;
  Octet od = 121;
  unsigned long nd = 3;
  ArbreDeHuffman ad = ADH_arbreDeHuffman(od, nd);
  ArbreDeHuffman ag = ADH_arbreDeHuffman(og, ng);
  
  CU_ASSERT_EQUAL(ADH_obtenirFrequence(ADH_fusionner(ad,ag)),ADH_obtenirFrequence(ag) + ADH_obtenirFrequence(ad));
  CU_ASSERT_EQUAL(ADH_obtenirFilsDroit(ADH_fusionner(ag,ad)),ag);
  CU_ASSERT_EQUAL(ADH_obtenirFilsGauche(ADH_fusionner(ag,ad)),ad);
  CU_ASSERT(!ADH_estUneFeuille(ADH_fusionner(ag,ad)));
}

void test_estUneFeuille(void) {
  Octet o = 241; 
  unsigned long f = 2;

  CU_ASSERT(ADH_estUneFeuille(ADH_arbreDeHuffman(o, f)));
}

void test_obtenir_octet_ADH(void) {
  Octet o = 241; 
  unsigned long f = 2;
  
  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_arbreDeHuffman(o, f)), o);
}

void test_obtenir_frequence_ADH(void) {
  Octet og = 241;
  unsigned long ng = 2;
  Octet od = 242;
  unsigned long nd = 3;
  ArbreDeHuffman ad = ADH_arbreDeHuffman(od, nd);
  ArbreDeHuffman ag = ADH_arbreDeHuffman(og, ng);

  CU_ASSERT_EQUAL(ADH_obtenirFrequence(ADH_arbreDeHuffman(od, nd)), nd);
  CU_ASSERT_EQUAL(ADH_obtenirFrequence(ADH_arbreDeHuffman(og, ng)), ng);
  CU_ASSERT_EQUAL(ADH_obtenirFrequence(ADH_fusionner(ad, ag)), ADH_obtenirFrequence(ag) + ADH_obtenirFrequence(ad));
}

void test_obtenir_fils_gauche(void) {
  Octet og = 241;
  unsigned long ng = 2;
  Octet od = 121;
  unsigned long nd = 3;
  ArbreDeHuffman ad = ADH_arbreDeHuffman(od, nd);
  ArbreDeHuffman ag = ADH_arbreDeHuffman(og, ng);

  CU_ASSERT_EQUAL(ADH_obtenirFilsGauche(ADH_fusionner(ag,ad)), ag);
}

void test_obtenir_fils_droit(void) {
  Octet og = 241;
  unsigned long ng = 2;
  Octet od = 121;
  unsigned long nd = 3;
  ArbreDeHuffman ad = ADH_arbreDeHuffman(od, nd);
  ArbreDeHuffman ag = ADH_arbreDeHuffman(og, ng);
  ArbreDeHuffman a = ADH_fusionner(ag,ad);
  CU_ASSERT_EQUAL(ADH_obtenirFilsDroit(a), ad);
}

/* Tests FileDePriorite.c */

void test_creation_filedePriorite(void) {
  FileDePriorite fdp = FDPAH_fileDePriorite();
  
  CU_ASSERT(FDPAH_estVide(fdp));
}

void test_estVide_filedePriorite(void) {
  FileDePriorite fdp = FDPAH_fileDePriorite();
  
  CU_ASSERT(FDPAH_estVide(fdp));
}

void test_enfiler(void) {
  Octet o = 241; 
  unsigned long f = 2;
  FileDePriorite fdp;
  bool nonEstVide = 0;
  fdp = FDPAH_fileDePriorite();
  ArbreDeHuffman a = ADH_arbreDeHuffman(o, f);
  FDPAH_enfiler(&fdp, a);
  CU_ASSERT_EQUAL(!(FDPAH_estVide(fdp)), nonEstVide);
}

void test_obtenirElement_et_Defiler(void) {
  Octet o = 241; 
  unsigned long f = 2;
  FileDePriorite fdp;
  fdp = FDPAH_fileDePriorite();
  ArbreDeHuffman a = ADH_arbreDeHuffman(o, f);
  FDPAH_enfiler(&fdp, a);
  CU_ASSERT_EQUAL((FDPAH_obtenirElementEtDefiler(&fdp)), fdp);
  CU_ASSERT_EQUAL((FDPAH_obtenirElementEtDefiler(&fdp)), a);
}


/* Tests tableDeCodage.c */

void test_creerTableCodage(void) {
  /* Utilisation d'un do while ... pour éviter le rique d'un dépassement de mémoire (256 avec un unsigned char) */
  TableDeCodage tdc = TDC_creerTableCodage();
  unsigned char i = 0;
  do {
    if (i==42) {
      CU_ASSERT_EQUAL(TDC_octetPresent(tdc, i), 1);
    } else {
      CU_ASSERT_EQUAL(TDC_octetPresent(tdc, i), 0);
    }
  }
  while (i==255);
}

void test_octetPresent(void) {
  TableDeCodage tdc = TDC_creerTableCodage();
  CodeBinaire cb_test = CB_creerCodeBinaire(bitA1);
  TDC_ajouterCodage(&tdc, 42, cb_test);
  unsigned char i = 0;
  do {
    CU_ASSERT_EQUAL(TDC_octetPresent(tdc, i), 0);
  }
  while (i==255);
}

void test_ajouterCodage(void) {
  TableDeCodage tdc = TDC_creerTableCodage();
  CodeBinaire cb_42_test = CB_creerCodeBinaire(bitA1);
  TDC_ajouterCodage(&tdc, 42, cb_42_test);
  CodeBinaire cb_43_test = CB_creerCodeBinaire(bitA1);
  CB_ajouterBit(&cb_43_test, bitA0);
  TDC_ajouterCodage(&tdc, 43, cb_43_test);

  unsigned char i = 0;
  do {
    if ((i==42) || (i==43)) {
      if (i==42) {
        CU_ASSERT_EQUAL(TDC_octetPresent(tdc, i), 1);
        CodeBinaire cb_42_lu = TDC_octetVersCodeBinaire(tdc,i);
        CU_ASSERT((CB_obtenirIemeBit(cb_42_lu, 0) == CB_obtenirIemeBit(cb_42_test, 0)));
        CU_ASSERT((CB_obtenirLongueur(cb_42_lu) == CB_obtenirLongueur( cb_42_test)));
        CU_ASSERT((CB_obtenirLongueur(cb_42_lu) == 1));
     } else {
        CU_ASSERT_EQUAL(TDC_octetPresent(tdc, i), 1);
        CodeBinaire cb_43_lu = TDC_octetVersCodeBinaire(tdc,i);
        CU_ASSERT((CB_obtenirIemeBit(cb_43_lu, 0) == CB_obtenirIemeBit(cb_43_test, 0)));
        CU_ASSERT((CB_obtenirIemeBit(cb_43_lu, 1) == CB_obtenirIemeBit(cb_43_test, 1)));
        CU_ASSERT((CB_obtenirLongueur(cb_43_lu) == CB_obtenirLongueur( cb_43_test)));
        CU_ASSERT((CB_obtenirLongueur(cb_43_lu) == 2));
     }
    } else {
      CU_ASSERT_EQUAL(TDC_octetPresent(tdc, i), 0);
    }
  }
  while (i==255);
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

  /* ajout d'une suite de test pour fileDePrioriteDArbreDeHuffman.c */
  CU_pSuite pSuiteFileDePriorite = CU_add_suite("Test fileDePrioriteDArbreDeHuffman", init_suite_success, clean_suite_success);
  if (NULL == pSuiteFileDePriorite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Ajout des tests à la suite FileDePriorite*/
  if ((NULL == CU_add_test(pSuiteFileDePriorite, "Création d'une File De Priorité vide", test_creation_filedePriorite)) 
    || (NULL == CU_add_test(pSuiteFileDePriorite, "Verifier q'une File De priorité est Vide ", test_estVide_filedePriorite))
    || (NULL == CU_add_test(pSuiteFileDePriorite, "Enfiler des éléments dans une File De Priorité ", test_enfiler))
    //|| (NULL == CU_add_test(pSuiteFileDePriorite, "Obtenir un élément et défiler la File De Priorité", test_obtenirElement_et_Defiler))
  )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  
  /* ajout d'une suite de test pour tableDeCodage.c */
  CU_pSuite pTableDeCodage = CU_add_suite("Test tableDeCodage", init_suite_success, clean_suite_success);
  if (NULL == pTableDeCodage) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* ajout des tests à la suite tableDeCodage */
  if ((NULL == CU_add_test(pTableDeCodage, "Création d'une tableDeCodage 'vide'", test_creerTableCodage))
    || (NULL == CU_add_test(pTableDeCodage, "Vérification qu'un unique élement inséré est retourné présent mais pas les autres", test_octetPresent))
    || (NULL == CU_add_test(pTableDeCodage, "Vérifications multiples après l'ajout de 2 CodeBinaire de tailles différentes dans la TableDeCodage", test_ajouterCodage))
  )
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* ajout d'une suite de test pour arbreDeHuffman.c */
  CU_pSuite pSuiteArbreDeHuffman = CU_add_suite("Test arbreDeHuffman", init_suite_success, clean_suite_success);
  if (NULL == pSuiteArbreDeHuffman) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Ajout des tests à la suite arbreDeHuffman */
  if ((NULL == CU_add_test(pSuiteArbreDeHuffman, "Creation d'un arbre de Huffman à partir d'un octet et une occurence", test_creation_arbreDeHuffman)) 
    || (NULL == CU_add_test(pSuiteArbreDeHuffman, "Fusion de deux feuilles pour cree un arbre de Huffman", test_fussioner_ADH))
    || (NULL == CU_add_test(pSuiteArbreDeHuffman, "Savoir si l'arbre de Huffman est une Feuille ", test_estUneFeuille))
    || (NULL == CU_add_test(pSuiteArbreDeHuffman, "Obtenir l'octet present sur une feuille", test_obtenir_octet_ADH))
    || (NULL == CU_add_test(pSuiteArbreDeHuffman, "Obtenir la frequence d'apparition present sur une feuille", test_obtenir_frequence_ADH))
    || (NULL == CU_add_test(pSuiteArbreDeHuffman, "Obtenir le Fils gauche d'un arbre de Huffman", test_obtenir_fils_gauche))
    || (NULL == CU_add_test(pSuiteArbreDeHuffman, "Obtenir le Fils droit d'un arbre de Huffman", test_obtenir_fils_droit))
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