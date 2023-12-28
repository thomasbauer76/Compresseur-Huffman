#include <stdlib.h>
#include <string.h>
#include "compression.h"
#include "decompression.h"

void printUtilisation() {
    printf("Utilisation :\n");
    printf("\t- pour compresser : huffman c nomFichier\n");
    printf("\t- pour décompresser : huffman d nomFichier.huff\n");
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (strcmp(argv[1], "c") == 0) {
            FILE *f = fopen(argv[2], "rb");
            if (f != NULL) {
                C_compresser(f, argv[2]);
                fclose(f);
            }
            else {
                printf("Erreur : fichier inexistant ou corrompu\n");
                printUtilisation();
            }
        }
        else if (strcmp(argv[1], "d") == 0) {
            if (strstr(argv[2], ".huff") != NULL) {
                FILE *f = fopen(argv[2], "rb");
                if (f != NULL) {
                    D_decompresser(f, argv[2]);
                    fclose(f);
                }
                else {
                    printf("Erreur : fichier inexistant ou corrompu\n");
                    printUtilisation();
                }
            }
            else {
                printf("Erreur : impossible de décompresser un fichier non compressé\n");
                printUtilisation();
            }
        }
        else {
            printf("Erreur : deuxième paramètre incorrect\n");
            printUtilisation();
        }
    }
    else {
        printf("Erreur : nombre de paramètres incorrect\n");
        printUtilisation();
    }
    return EXIT_SUCCESS;
}