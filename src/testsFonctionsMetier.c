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

FILE *fichierTemporaireEncode() {
  FILE *tempFile = tmpfile();
  // Pour avoir la version compressé de l'exemple du sujet je vais écrire les 5 entiers en dessous sous forme de 5 unsigned char
  // 137 249 150 167 38
  unsigned char octet1 = 137;
  unsigned char octet2 = 249;
  unsigned char octet3 = 150;
  unsigned char octet4 = 167;
  unsigned char octet5 = 38;
  // Pour être certain d'écrire au début du fichier
  rewind(tempFile);
  fwrite(&octet1, sizeof(unsigned char), 1, tempFile);
  fwrite(&octet2, sizeof(unsigned char), 1, tempFile);
  fwrite(&octet3, sizeof(unsigned char), 1, tempFile);
  fwrite(&octet4, sizeof(unsigned char), 1, tempFile);
  fwrite(&octet5, sizeof(unsigned char), 1, tempFile);
  return tempFile;
}

FILE *fichierTemporaireVide() {
  FILE *tempFile = tmpfile();

  return tempFile;
}


/* Tests construireArbreDeHuffman.c */

void test_file_de_priorite(void) {
  FILE *tempFile = fichierTemporaireRempli();
  
  Statistiques s;
  unsigned long taille;
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
  unsigned long taille;
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
  unsigned long taille;
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
  unsigned long taille;
  C_obtenirStatistiquesEtTailleFichier(tempFile, &s, &taille);

  CU_ASSERT_EQUAL(taille, 4 + 2 + 3 + 2 + 1 + 1 + 2);
}

void test_table_de_codage(void) {
  FILE *tempFile = fichierTemporaireRempli();
  
  Statistiques s;
  unsigned long taille;
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


void test_ecrire_taille_fichier(void) {
  FILE *tempFileEntree = fichierTemporaireRempli();
  
  Statistiques s;
  unsigned long taille;

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
    unsigned long taille;
    C_obtenirStatistiquesEtTailleFichier(tempFileEntree, &s_entree, &taille);

    fclose(tempFileEntree);

    FILE *tempFileSortie = tmpfile();

    C_ecrireStatistiques(tempFileSortie, s_entree);

    rewind(tempFileSortie);

    unsigned long occurence_lue;
    unsigned short o;
    for (o = 0; o < MAX_OCTET; o++) {
        unsigned long occurence_attendue = 0;
        if (o == O_naturelVersOctet('A')) occurence_attendue = 4;
        else if (o == O_naturelVersOctet('B')) occurence_attendue = 2;
        else if (o == O_naturelVersOctet('C')) occurence_attendue = 3;
        else if (o == O_naturelVersOctet('D')) occurence_attendue = 2;
        else if (o == O_naturelVersOctet('E')) occurence_attendue = 1;
        else if (o == O_naturelVersOctet('F')) occurence_attendue = 1;
        else if (o == O_naturelVersOctet('G')) occurence_attendue = 2;

        CU_ASSERT_EQUAL(fread(&occurence_lue, sizeof(unsigned long), 1, tempFileSortie), 1);
        CU_ASSERT_EQUAL(occurence_lue, occurence_attendue);
    }

    fclose(tempFileSortie);
}

void test_concatener_codes_binaires(void) {

    CodeBinaire cbA = CB_creerCodeBinaire(bitA0);
    CB_ajouterBit(&cbA, bitA1);
  
    CodeBinaire cbB = CB_creerCodeBinaire(bitA1);
    CB_ajouterBit(&cbB, bitA0);
    CB_ajouterBit(&cbB, bitA0);
  

    CodeBinaire cbC = CB_creerCodeBinaire(bitA0);
    CB_ajouterBit(&cbC, bitA0);

 
    CodeBinaire cbD = CB_creerCodeBinaire(bitA1);
    CB_ajouterBit(&cbD, bitA0);
    CB_ajouterBit(&cbD, bitA1);
  
  
    CodeBinaire cbE = CB_creerCodeBinaire(bitA1);
    CB_ajouterBit(&cbE, bitA1);
    CB_ajouterBit(&cbE, bitA1);
    CB_ajouterBit(&cbE, bitA0);
  
  
    CodeBinaire cbF = CB_creerCodeBinaire(bitA1);
    CB_ajouterBit(&cbF, bitA1);
    CB_ajouterBit(&cbF, bitA1);
    CB_ajouterBit(&cbF, bitA1);
  

    CodeBinaire cbG = CB_creerCodeBinaire(bitA1);
    CB_ajouterBit(&cbG, bitA1);
    CB_ajouterBit(&cbG, bitA0);

    CodeBinaire cbTemp = CB_creerCodeBinaire(bitA0);
    for (unsigned short i = 1; i < MAX_CB; i++)
        CB_ajouterBit(&cbTemp, bitA0);
    

  FILE *tempFileSortie = tmpfile();
  C_concatenerCodeBinaireDansFichier(tempFileSortie,&cbTemp,cbB);
  C_concatenerCodeBinaireDansFichier(tempFileSortie,&cbTemp,cbA);
  C_concatenerCodeBinaireDansFichier(tempFileSortie,&cbTemp,cbC);
  C_concatenerCodeBinaireDansFichier(tempFileSortie,&cbTemp,cbF);
  C_concatenerCodeBinaireDansFichier(tempFileSortie,&cbTemp,cbG);
  C_concatenerCodeBinaireDansFichier(tempFileSortie,&cbTemp,cbA);

  fseek(tempFileSortie, 0, SEEK_SET);
  unsigned char octet1, octet2;
  fread(&octet1, sizeof(unsigned char), 1, tempFileSortie);
  fread(&octet2, sizeof(unsigned char), 1, tempFileSortie);

  CU_ASSERT_EQUAL(octet1, 0x89);  // 10001001 en binaire
  CU_ASSERT_EQUAL(octet2, 0xFC);  // 11111100 en binaire

  fclose(tempFileSortie);
}

/* Tests D_decoder */

void test_decoder(void) {
  FILE *fichierTest = fichierTemporaireRempli();
  Statistiques s;
  unsigned long longueur;
  C_obtenirStatistiquesEtTailleFichier(fichierTest, &s, &longueur);
  ArbreDeHuffman a = CADH_construireArbreDeHuffman(s);

  FILE *fichierTestEncode = fichierTemporaireEncode();
  FILE *fichierTestDecode = tmpfile();

  D_decoder(a, longueur, fichierTestEncode, fichierTestDecode);

  rewind(fichierTest);
  rewind(fichierTestDecode);
  for (unsigned int i=1; i<=longueur; i++) {
    unsigned char octetActuelFichierTest;
    fread(&octetActuelFichierTest, sizeof(unsigned char), 1, fichierTest);
    unsigned char octetActuelFichierTestDecode;
    fread(&octetActuelFichierTestDecode, sizeof(unsigned char), 1, fichierTestDecode);
    CU_ASSERT((octetActuelFichierTest == octetActuelFichierTestDecode));
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
    || (NULL == CU_add_test(pSuiteCompression, "concatener les codes binaire dans un fichiers", test_concatener_codes_binaires))
    || (NULL == CU_add_test(pSuiteCompression, "Decodage d'un fichier et vérification que ça a marché", test_decoder))
    //|| (NULL == CU_add_test(pSuiteCompression, "encoder le fichier de sortie de codebinaires", test_encoder_fichier))
    //|| (NULL == CU_add_test(pSuiteCompression, "compressé le fichier", test_compression_fichier)) 
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