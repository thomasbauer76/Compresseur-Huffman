#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "statistiques.h"
#include "fileDePrioriteDArbreDeHuffman.h"
#include "codeBinaire.h"

#include "compression.c"
#include "decompression.c"

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

/* Tests ArbreDeHuffman.c */

void test_creation_arbreDeHuffman(void) {
  ArbreDeHuffman a = ADH_arbreDeHuffman();
  
  Octet o; 
  unsigned long f;
 
  CU_ASSERT_EQUAL(ADH_estUneFeuille(ADH_arbreDeHuffman(o,f)));
  CU_ASSERT_EQUAL(ADH_obtenirFrequence(ADH_arbreDeHuffman(o,f)) = f);
}

void test_fussioner_ADH(void) {
  ArbreDeHuffman ad = ADH_arbreDeHuffman();
  ArbreDeHuffman ag = ADH_arbreDeHuffman();
  Octet o; 
  unsigned long f;
 
  CU_ASSERT_EQUAL(ADH_obtenirFrequence(ADH_fusionner(ad,ag)) = ADH_obtenirFrequence(ag) + ADH_obtenirFrequence(ad));
 
}
/* Tests compression.c */

FILE *fichierTemporaireRempli() {
  FILE *tempFile = tmpfile();

  // Reprise des données du sujet pour effectuer les tests unitaires
  fprintf(tempFile,"BACFGABDDACEACG");

  return tempFile;
}

void test_obtenir_statistiques(void) {
  FILE *tempFile = fichierTemporaireRempli();
  
  Statistiques s;
  unsigned long taille;
  obtenirStatistiquesEtTailleFichier(tempFile, &s, &taille);

  CU_ASSERT_EQUAL(S_obtenirOccurence(s, O_naturelVersOctet('A')), 4);
  CU_ASSERT_EQUAL(S_obtenirOccurence(s, O_naturelVersOctet('B')), 2);
  CU_ASSERT_EQUAL(S_obtenirOccurence(s, O_naturelVersOctet('C')), 3);
  CU_ASSERT_EQUAL(S_obtenirOccurence(s, O_naturelVersOctet('D')), 2);
  CU_ASSERT_EQUAL(S_obtenirOccurence(s, O_naturelVersOctet('E')), 1);
  CU_ASSERT_EQUAL(S_obtenirOccurence(s, O_naturelVersOctet('F')), 1);
  CU_ASSERT_EQUAL(S_obtenirOccurence(s, O_naturelVersOctet('G')), 2);
}

void test_obtenir_taille_fichier(void) {
  FILE *tempFile = fichierTemporaireRempli();
  
  Statistiques s;
  unsigned long taille;
  obtenirStatistiquesEtTailleFichier(tempFile, &s, &taille);

  CU_ASSERT_EQUAL(taille, 4 + 2 + 3 + 2 + 1 + 1 + 2);
}

void test_file_de_priorite(void) {
  FILE *tempFile = fichierTemporaireRempli();
  
  Statistiques s;
  unsigned long taille;
  obtenirStatistiquesEtTailleFichier(tempFile, &s, &taille);

  FileDePriorite fdp = construireFileDePriorite(s);

  CU_ASSERT_EQUAL(ADH_obtenirOctet(FDPAH_obtenirElementEtDefiler(&fdp)), 'E');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(FDPAH_obtenirElementEtDefiler(&fdp)), 'F');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(FDPAH_obtenirElementEtDefiler(&fdp)), 'B');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(FDPAH_obtenirElementEtDefiler(&fdp)), 'D');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(FDPAH_obtenirElementEtDefiler(&fdp)), 'G');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(FDPAH_obtenirElementEtDefiler(&fdp)), 'C');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(FDPAH_obtenirElementEtDefiler(&fdp)), 'A');
}

void test_arbre_de_huffman(void) {
  FILE *tempFile = fichierTemporaireRempli();
  
  Statistiques s;
  unsigned long taille;
  obtenirStatistiquesEtTailleFichier(tempFile, &s, &taille);

  ArbreDeHuffman a = construireArbreDeHuffman(s);

  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_obtenirFilsGauche(ADH_obtenirFilsGauche(a))), 'C');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_obtenirFilsDroit(ADH_obtenirFilsGauche(a))), 'A');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_obtenirFilsGauche(ADH_obtenirFilsGauche(ADH_obtenirFilsDroit(a)))), 'B');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_obtenirFilsDroit(ADH_obtenirFilsGauche(ADH_obtenirFilsDroit(a)))), 'D');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_obtenirFilsGauche(ADH_obtenirFilsDroit(ADH_obtenirFilsDroit(a)))), 'G');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_obtenirFilsGauche(ADH_obtenirFilsDroit(ADH_obtenirFilsDroit(ADH_obtenirFilsDroit(a))))), 'E');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_obtenirFilsDroit(ADH_obtenirFilsDroit(ADH_obtenirFilsDroit(ADH_obtenirFilsDroit(a))))), 'F');
}

void test_table_de_codage(void) {
  FILE *tempFile = fichierTemporaireRempli();
  
  Statistiques s;
  unsigned long taille;
  obtenirStatistiquesEtTailleFichier(tempFile, &s, &taille);

  ArbreDeHuffman a = construireArbreDeHuffman(s);

  TableDeCodage tdc = obtenirTableDeCodage(a);

  CodeBinaire cb;
  
  // On effectue un test sur 3 octets
  cb = TDC_octetVersCodeBinaire(tdc, O_naturelVersOctet('A'));
  CU_ASSERT_EQUAL(CB_obtenirIemeBit(cb, 0), bitA0);
  CU_ASSERT_EQUAL(CB_obtenirIemeBit(cb, 1), bitA1);

  cb = TDC_octetVersCodeBinaire(tdc, O_naturelVersOctet('C'));
  CU_ASSERT_EQUAL(CB_obtenirIemeBit(cb, 0), bitA0);
  CU_ASSERT_EQUAL(CB_obtenirIemeBit(cb, 1), bitA0);

  cb = TDC_octetVersCodeBinaire(tdc, O_naturelVersOctet('E'));
  CU_ASSERT_EQUAL(CB_obtenirIemeBit(cb, 0), bitA1);
  CU_ASSERT_EQUAL(CB_obtenirIemeBit(cb, 1), bitA1);
  CU_ASSERT_EQUAL(CB_obtenirIemeBit(cb, 2), bitA1);
  CU_ASSERT_EQUAL(CB_obtenirIemeBit(cb, 3), bitA0);
}

void test_code_binaire_8_bits_vers_octet(void) {
  unsigned short i;

  Octet o = O_naturelVersOctet('K');

  CodeBinaire cb = CB_creerCodeBinaire(O_obtenirIemeBit(o, 0));
  for (i = 1; i < MAX_CB; i++)
    CB_ajouterBit(&cb, O_obtenirIemeBit(o, i));
  
  for (i = 0; i < MAX_CB; i++)
    CU_ASSERT_EQUAL(CB_obtenirIemeBit(cb, i), O_obtenirIemeBit(o, i))
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
  if ((NULL == CU_add_test(pSuiteCompression, "Obtention des statistiques d'un fichier", test_obtenir_statistiques))
    || (NULL == CU_add_test(pSuiteCompression, "Obtention de la taille d'un fichier", test_obtenir_taille_fichier))
    || (NULL == CU_add_test(pSuiteCompression, "Construction de la file de priorité à partir des statistiques", test_file_de_priorite))
    || (NULL == CU_add_test(pSuiteCompression, "Construction de l'arbre de Huffman à partir des statistiques", test_arbre_de_huffman))
    || (NULL == CU_add_test(pSuiteCompression, "Obtention de la table de codage à partir de l'arbre de huffman", test_table_de_codage))
    || (NULL == CU_add_test(pSuiteCompression, "Conversion d'un code binaire de 8 bits vers un octet", test_code_binaire_8_bits_vers_octet))
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