/**
 * \file statistiques.h
 * \brief Implémentation du TAD TableDeCodage pour le compresseur d'Huffman
 * \author O.Taoba
 * \date 07/01/2024
 *
 */
#ifndef __TABLE_DE_CODAGE__
#define __TABLE_DE_CODAGE__

#include <stdbool.h>

#include "codeBinaire.h"
#include "octet.h"
/**
 * \brief Le type TDC_TableDeCodage est une structure contenant qui contient 2 champs : un tableau de CodeBinaire et un Tableau de Booleen qui retourne le booleen associé à la présence d'un code binaire associé à un octet particulier
 *
 */
typedef struct TDC_TableDeCodage {
    CB_CodeBinaire tableDeCodeBinaire[MAX_OCTET];   /**< le tableau contenant les codes binaires */
    bool tableDePresence[MAX_OCTET];                /**< le tableau permettant de connaître la présence ou non des codes binaires */
} TDC_TableDeCodage;

/**
 * \fn TDC_TableDeCodage TDC_creerTableCodage(void)
 * \brief Fonction créant une TableDeCodage Vide
 *
 * \return TDC_TableDeCodage
 */
TDC_TableDeCodage TDC_creerTableCodage();

/**
 * \fn void TDC_ajouterCodage(TDC_TableDeCodage* p_tdc, O_Octet o, CB_CodeBinaire cb)
 * \brief Fonction permettant ajouter un codeBinaire à notre table de codage
 *
 * \param p_tdc : un pointeur sur la table de codage à modifié
 * \param o : l'octet en entree correspondant à l'octet associé au code binaire qui va etre inserer
 * \param cb : le codeBinaire à ajouter à la tableDeCodage
 */
void TDC_ajouterCodage(TDC_TableDeCodage* p_tdc, O_Octet o, CB_CodeBinaire cb);
/**
 * \fn CB_CodeBinaire TDC_octetVersCodeBinaire(TDC_TableDeCodage tdc, O_Octet o)
 * \brief Procédure permettant de retourner le codeBinaire associé à un octet en entrée à partir de la tableDeCodage
 *
 * \param tdc : la table de codage à partir de laquelle je recupère mes données
 * \param o : l'octet dont on veut recuper le code binaire
 * \return CB_CodeBinaire
 */
CB_CodeBinaire TDC_octetVersCodeBinaire(TDC_TableDeCodage tdc, O_Octet o);
/**
 * \fn bool TDC_octetPresent(TDC_TableDeCodage tdc, O_Octet o)
 * \brief Fonction qui retourne un booleen afin de savoir si un octet est present dans notre table de codage
 * \param tdc : la table de codage à partir de laquelle je recupère mes données
 * \param o : l'octet dont on veux verifier la présence
 * \return Booleen
 */
bool TDC_octetPresent(TDC_TableDeCodage tdc, O_Octet o);

#endif
