#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "statistiques.h"
#include "codeBinaire.h"

#include "compression.c"

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
  CU_ASSERT_EQUAL(CB_obtenirLongueur(cb),1);
  CU_ASSERT_EQUAL(CB_obtenirIemeBit(cb,1),b);
}

void test_ajout_bit(void) {
  CodeBinaire cb = CB_creerCodeBinaire(bitA0);
  unsigned short ancienneLongueur = CB_obtenirLongueur(cb);
  Bit b = bitA1;
  CB_ajouterBit(&cb,b);
  unsigned short nouvelleLongueur = CB_obtenirLongueur(cb);
  CU_ASSERT_EQUAL(nouvelleLongueur,ancienneLongueur+1);
  CU_ASSERT_EQUAL(CB_obtenirIemeBit(cb,nouvelleLongueur-1),b);
}


/* Tests compression.c */

void test_obtenir_statistiques(void) {
  FILE *tempFile = tmpfile();
  unsigned long i;

  unsigned char o_125 = 125;
  unsigned long n_125 = 13;
  for (i = 1; i <= n_125; i++)
    fwrite(&o_125, sizeof(unsigned char), 1, tempFile);

  unsigned char o_243 = 243;
  unsigned long n_243 = 3452;
  for (i = 1; i <= n_243; i++)
    fwrite(&o_243, sizeof(unsigned char), 1, tempFile);
  
  unsigned char o_63 = 63;
  unsigned long n_63 = 1;
  for (i = 1; i <= n_63; i++)
    fwrite(&o_63, sizeof(unsigned char), 1, tempFile);
  
  Statistiques s;
  unsigned long taille;
  obtenirStatistiquesEtTailleFichier(tempFile, &s, &taille);

  CU_ASSERT_EQUAL(S_obtenirOccurence(s, O_naturelVersOctet(125)), n_125);
  CU_ASSERT_EQUAL(S_obtenirOccurence(s, O_naturelVersOctet(243)), n_243);
  CU_ASSERT_EQUAL(S_obtenirOccurence(s, O_naturelVersOctet(63)), n_63);
}

void test_obtenir_taille_fichier(void) {
  FILE *tempFile = tmpfile();
  unsigned long i;

  unsigned char o_125 = 125;
  unsigned long n_125 = 13;
  for (i = 1; i <= n_125; i++)
    fwrite(&o_125, sizeof(unsigned char), 1, tempFile);

  unsigned char o_243 = 243;
  unsigned long n_243 = 3452;
  for (i = 1; i <= n_243; i++)
    fwrite(&o_243, sizeof(unsigned char), 1, tempFile);
  
  unsigned char o_63 = 63;
  unsigned long n_63 = 1;
  for (i = 1; i <= n_63; i++)
    fwrite(&o_63, sizeof(unsigned char), 1, tempFile);
  
  Statistiques s;
  unsigned long taille;
  obtenirStatistiquesEtTailleFichier(tempFile, &s, &taille);

  CU_ASSERT_EQUAL(taille, n_125 + n_243 + n_63);
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
  
  /* ajout d'une suite de test pour compression.c */
  CU_pSuite pSuiteCompression = CU_add_suite("Test compression", init_suite_success, clean_suite_success);
  if (NULL == pSuiteCompression) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Ajout des tests à la suite compression */
  if ((NULL == CU_add_test(pSuiteCompression, "Obtenir statistiques d'un fichier", test_obtenir_statistiques))
    || (NULL == CU_add_test(pSuiteCodeBinaire, "Obtenir taille d'un fichier", test_obtenir_taille_fichier))
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