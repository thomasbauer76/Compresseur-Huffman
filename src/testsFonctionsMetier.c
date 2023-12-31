#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <CUnit/Basic.h>
#include "statistiques.h"
#include "fileDePrioriteDArbreDeHuffman.h"
#include "codeBinaire.h"
#include "octet.h"
#include "compression.c"
#include "decompression.c"


int init_suite_success(void) {
    return 0;
}

int clean_suite_success(void) {
    return 0;
}

FILE *fichierTemporaireRempli() {
  FILE *tempFile = tmpfile();

  // Reprise des données du sujet pour effectuer les tests unitaires
  fprintf(tempFile,"BACFGABDDACEACG");

  return tempFile;
}

// Fonction dépreciée, anciennement utilisée pour le test de decoder mais pas vérifiée
// FILE *fichierTemporaireEncode() {
//   FILE *tempFile = tmpfile();
//   // Pour avoir la version compressé de l'exemple du sujet je vais écrire les 5 entiers en dessous sous forme de 5 unsigned char
//   // 137 249 150 167 38
//   unsigned char octet1 = 137;
//   unsigned char octet2 = 249;
//   unsigned char octet3 = 150;
//   unsigned char octet4 = 167;
//   unsigned char octet5 = 38;
//   // Pour être certain d'écrire au début du fichier
//   rewind(tempFile);
//   fwrite(&octet1, sizeof(unsigned char), 1, tempFile);
//   fwrite(&octet2, sizeof(unsigned char), 1, tempFile);
//   fwrite(&octet3, sizeof(unsigned char), 1, tempFile);
//   fwrite(&octet4, sizeof(unsigned char), 1, tempFile);
//   fwrite(&octet5, sizeof(unsigned char), 1, tempFile);
//   return tempFile;
// }


/* Tests construireArbreDeHuffman.c */

void test_file_de_priorite(void) {
  FILE *tempFile = fichierTemporaireRempli();
  
  Statistiques s;
  unsigned long long taille;
  C_obtenirStatistiquesEtTailleFichier(tempFile, &s, &taille);

  FileDePriorite fdp = CADH_construireFileDePriorite(s);

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
  unsigned long long taille;
  C_obtenirStatistiquesEtTailleFichier(tempFile, &s, &taille);

  ArbreDeHuffman a = CADH_construireArbreDeHuffman(s);

  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_obtenirFilsGauche(ADH_obtenirFilsGauche(a))), 'C');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_obtenirFilsDroit(ADH_obtenirFilsGauche(a))), 'A');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_obtenirFilsGauche(ADH_obtenirFilsGauche(ADH_obtenirFilsDroit(a)))), 'B');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_obtenirFilsDroit(ADH_obtenirFilsGauche(ADH_obtenirFilsDroit(a)))), 'D');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_obtenirFilsGauche(ADH_obtenirFilsDroit(ADH_obtenirFilsDroit(a)))), 'G');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_obtenirFilsGauche(ADH_obtenirFilsDroit(ADH_obtenirFilsDroit(ADH_obtenirFilsDroit(a))))), 'E');
  CU_ASSERT_EQUAL(ADH_obtenirOctet(ADH_obtenirFilsDroit(ADH_obtenirFilsDroit(ADH_obtenirFilsDroit(ADH_obtenirFilsDroit(a))))), 'F');
}


/* Tests compression.c */

void test_obtenir_statistiques(void) {
  FILE *tempFile = fichierTemporaireRempli();
  
  Statistiques s;
  unsigned long long taille;
  C_obtenirStatistiquesEtTailleFichier(tempFile, &s, &taille);

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
  unsigned long long taille;
  C_obtenirStatistiquesEtTailleFichier(tempFile, &s, &taille);

  CU_ASSERT_EQUAL(taille, 4 + 2 + 3 + 2 + 1 + 1 + 2);
}

void test_table_de_codage(void) {
  FILE *tempFile = fichierTemporaireRempli();
  
  Statistiques s;
  unsigned long long taille;
  C_obtenirStatistiquesEtTailleFichier(tempFile, &s, &taille);

  ArbreDeHuffman a = CADH_construireArbreDeHuffman(s);

  TableDeCodage tdc = C_obtenirTableDeCodage(a);

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
  for (i = 1; i < MAX_BITS; i++)
    CB_ajouterBit(&cb, O_obtenirIemeBit(o, i));
  
  for (i = 0; i < MAX_BITS; i++)
    CU_ASSERT_EQUAL(CB_obtenirIemeBit(cb, i), O_obtenirIemeBit(o, i))
}

void test_ecrire_identifiant(void) {
  FILE *tempFile = tmpfile();
  
  C_ecrireIdentifiant(tempFile);

  rewind(tempFile);
  unsigned short identifiant_lue;
  unsigned short identifiant_attendue = IDENTIFIANT;

  CU_ASSERT_EQUAL(fread(&identifiant_lue, sizeof(unsigned short), 1, tempFile), 1);
  CU_ASSERT_EQUAL(identifiant_lue, identifiant_attendue);
  fclose(tempFile);
}

void test_seDeplacerDansLArbre(void) {
  FILE *tempFileEntree = fichierTemporaireRempli();
  Statistiques s;
  unsigned long long taille;
  C_obtenirStatistiquesEtTailleFichier(tempFileEntree, &s, &taille);
  ArbreDeHuffman abh = CADH_construireArbreDeHuffman(s);
  // On vérifie arbitrairement si on arrive à retrouver notre octet tout à gauche, celui tout à droite et un dernier entre les deux selon l'exemple du sujet
  // L'octet 'C' se situe 2 cran à gauche
  ArbreDeHuffman abhTest = abh;
  for (unsigned int i = 0; i<2; i++) {
    D_seDeplacerDansLArbre(bitA0, &abhTest);
  }
  CU_ASSERT(ADH_obtenirOctet(abhTest)=='C');

  // L'octet 'F' se situe 4 crans à droite
  abhTest = abh;
  for (unsigned int i = 0; i<4; i++) {
    D_seDeplacerDansLArbre(bitA1, &abhTest);
  }
  CU_ASSERT(ADH_obtenirOctet(abhTest)=='F');

  // L'octet 'D' se situe 1 cran à droite, puis 1 à gauche et enfin 1 à droite
  abhTest = abh;
  D_seDeplacerDansLArbre(bitA1, &abhTest);
  D_seDeplacerDansLArbre(bitA0, &abhTest);
  D_seDeplacerDansLArbre(bitA1, &abhTest);
  CU_ASSERT(ADH_obtenirOctet(abhTest)=='D');
}

void test_ecrire_taille_fichier(void) {
  FILE *tempFileEntree = fichierTemporaireRempli();
  
  Statistiques s;
  unsigned long long taille;

  C_obtenirStatistiquesEtTailleFichier(tempFileEntree, &s, &taille);
  fclose(tempFileEntree);

  FILE *tempFileSortie = tmpfile();
  
  C_ecrireTailleFichier(tempFileSortie, taille);

  rewind(tempFileSortie);
  unsigned long long taille_lue;
  
  CU_ASSERT_EQUAL(fread(&taille_lue, sizeof(unsigned long long), 1, tempFileSortie), 1);
  CU_ASSERT_EQUAL(taille_lue, taille);

  fclose(tempFileSortie);
}

void test_ecrire_statistiques(void) {
    FILE *tempFileEntree = fichierTemporaireRempli();

    Statistiques s_entree;
    unsigned long long taille;
    C_obtenirStatistiquesEtTailleFichier(tempFileEntree, &s_entree, &taille);

    fclose(tempFileEntree);

    FILE *tempFileSortie = tmpfile();

    C_ecrireStatistiques(tempFileSortie, s_entree);

    rewind(tempFileSortie);
    unsigned long occurence, octet;
    
    fread(&occurence, sizeof(unsigned long), 1, tempFileSortie);
    CU_ASSERT_EQUAL(occurence, 4);

    fread(&octet, sizeof(unsigned char), 1, tempFileSortie);
    CU_ASSERT_EQUAL(octet, 'A');

    fread(&occurence, sizeof(unsigned long), 1, tempFileSortie);
    CU_ASSERT_EQUAL(occurence, 2);

    fread(&octet, sizeof(unsigned char), 1, tempFileSortie);
    CU_ASSERT_EQUAL(octet, 'B');

    fread(&occurence, sizeof(unsigned long), 1, tempFileSortie);
    CU_ASSERT_EQUAL(occurence, 3);

    fread(&octet, sizeof(unsigned char), 1, tempFileSortie);
    CU_ASSERT_EQUAL(octet, 'C');

    fread(&occurence, sizeof(unsigned long), 1, tempFileSortie);
    CU_ASSERT_EQUAL(occurence, 2);

    fread(&octet, sizeof(unsigned char), 1, tempFileSortie);
    CU_ASSERT_EQUAL(octet, 'D');

    fread(&occurence, sizeof(unsigned long), 1, tempFileSortie);
    CU_ASSERT_EQUAL(occurence, 1);

    fread(&octet, sizeof(unsigned char), 1, tempFileSortie);
    CU_ASSERT_EQUAL(octet, 'E');

    fread(&occurence, sizeof(unsigned long), 1, tempFileSortie);
    CU_ASSERT_EQUAL(occurence, 1);

    fread(&octet, sizeof(unsigned char), 1, tempFileSortie);
    CU_ASSERT_EQUAL(octet, 'F');

    fread(&occurence, sizeof(unsigned long), 1, tempFileSortie);
    CU_ASSERT_EQUAL(occurence, 2);

    fread(&octet, sizeof(unsigned char), 1, tempFileSortie);
    CU_ASSERT_EQUAL(octet, 'G');
    
    fread(&occurence, sizeof(unsigned long), 1, tempFileSortie);
    CU_ASSERT_EQUAL(occurence, 0);

    fclose(tempFileSortie);
}

/* Tests C_encoder */
void test_encoder(void) {
  FILE *tempFileEntree = fichierTemporaireRempli();

  Statistiques s;
  unsigned long long longueur;
  C_obtenirStatistiquesEtTailleFichier(tempFileEntree, &s, &longueur);
  ArbreDeHuffman a = CADH_construireArbreDeHuffman(s);
  TableDeCodage tdc = C_obtenirTableDeCodage(a);

  fclose(tempFileEntree);
  FILE *tempFileSortie = tmpfile();

  C_encoder(tempFileEntree, tempFileSortie, tdc);

  rewind(tempFileSortie);

  unsigned char octet1, octet2;
  fread(&octet1, sizeof(unsigned char), 1, tempFileSortie);
  fread(&octet2, sizeof(unsigned char), 1, tempFileSortie);

  Octet otest1 = O_creerOctet(bitA1,bitA0,bitA0,bitA0,bitA1,bitA0,bitA0,bitA1);
  Octet otest2 = O_creerOctet(bitA1,bitA1,bitA1,bitA1,bitA1,bitA0,bitA0,bitA1);
  CU_ASSERT_EQUAL(octet1, otest1);  // 10001001 en binaire
  CU_ASSERT_EQUAL(octet2, otest2);  // 11111001 en binaire

  fclose(tempFileSortie);

}

/* Tests D_decoder */
void test_decoder(void) {
  FILE *fichierTest = fichierTemporaireRempli();
  Statistiques s;
  unsigned long long longueur;
  C_obtenirStatistiquesEtTailleFichier(fichierTest, &s, &longueur);
  ArbreDeHuffman a = CADH_construireArbreDeHuffman(s);

  //Création du fichier encoder de l'exemple
  FILE *fichierTestEncode = tmpfile();
  TableDeCodage tdc = C_obtenirTableDeCodage(a);
  C_encoder(fichierTest, fichierTestEncode, tdc);

  //On décode ce fichier fraichement encoder
  FILE *fichierTestDecode = tmpfile();
  D_decoder(a, longueur, fichierTestEncode, fichierTestDecode);

  //On regarde si tous les octets entre le fichier original et le fichier decoder sont égaux
  rewind(fichierTest);
  rewind(fichierTestDecode);
  for (unsigned int i=1; i<=longueur; i++) {
    unsigned char octetActuelFichierTest;
    fread(&octetActuelFichierTest, sizeof(unsigned char), 1, fichierTest);
    unsigned char octetActuelFichierTestDecode;
    fread(&octetActuelFichierTestDecode, sizeof(unsigned char), 1, fichierTestDecode);
    switch (octetActuelFichierTest)
    {
    // Il y a 4 occurences de A
    // 2 de B
    // 3 de C
    // 2 de D
    // 1 de E
    // 1 de F
    // 2 de G
    case 'A':
      CU_ASSERT((octetActuelFichierTest == 'A'));
      break;
    case 'B':
      CU_ASSERT((octetActuelFichierTest == 'B'));
      break;
    case 'C':
      CU_ASSERT((octetActuelFichierTest == 'C'));
      break;
    case 'D':
      CU_ASSERT((octetActuelFichierTest == 'D'));
      break;
    case 'E':
      CU_ASSERT((octetActuelFichierTest == 'E'));
      break;
    case 'F':
      CU_ASSERT((octetActuelFichierTest == 'F'));
      break;
    case 'G':
      CU_ASSERT((octetActuelFichierTest == 'G'));
      break;    
    default:
      break;
    }
  }
  
}

int main(int argc, char** argv){

  /* initialisation du registre de tests */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();


  /* ajout d'une suite de test pour compression.c et construireArbreDeHuffman.c */
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
    || (NULL == CU_add_test(pSuiteCompression, "ecrire un identifiant dans un fichier ", test_ecrire_identifiant))
    || (NULL == CU_add_test(pSuiteCompression, "ecrire la taille du fichier dans un fichier", test_ecrire_taille_fichier))
    || (NULL == CU_add_test(pSuiteCompression, "ecrire les statistique du fichier dans un fichier", test_ecrire_statistiques))
    || (NULL == CU_add_test(pSuiteCompression, "encodage d'un fichier et vérification que la concatenation fonctionne", test_encoder))
    || (NULL == CU_add_test(pSuiteCompression, "Decodage d'un fichier et vérification que ça a marché", test_decoder))
    || (NULL == CU_add_test(pSuiteCompression, "3 tests arbitraires pour D_seDeplacerDansLArbre", test_seDeplacerDansLArbre))
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