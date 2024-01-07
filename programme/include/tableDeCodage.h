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
 * \brief Le type TDC_TableDeCodage est une structure contenant 2 champs : un tableau de CodeBinaire et un Tableau de Booleen qui donne la présence d'un code binaire associé à un octet particulier
 *
 */
typedef struct TDC_TableDeCodage {
    CB_CodeBinaire tableDeCodeBinaire[MAX_OCTET];   /**< le tableau contenant les codes binaires */
    bool tableDePresence[MAX_OCTET];                /**< le tableau permettant de connaître la présence ou non des codes binaires */
} TDC_TableDeCodage;

/**
 * \fn TDC_TableDeCodage TDC_creerTableCodage(void)
 * \brief Fonction permettant de créer une TableDeCodage Vide
 *
 * \return TDC_TableDeCodage
 */
TDC_TableDeCodage TDC_creerTableCodage();

/**
 * \fn void TDC_ajouterCodage(TDC_TableDeCodage* p_tdc, O_Octet o, CB_CodeBinaire cb)
 * \brief Fonction permettant d'ajouter un codeBinaire à une table de codage
 *
 * \param p_tdc : un pointeur sur la TableDeCodage à modifier
 * \param o : l'Octet correspondant au CodeBinaire à ajouter
 * \param cb : le CodeBinaire à ajouter à la TableDeCodage
 */
void TDC_ajouterCodage(TDC_TableDeCodage* p_tdc, O_Octet o, CB_CodeBinaire cb);
/**
 * \fn CB_CodeBinaire TDC_octetVersCodeBinaire(TDC_TableDeCodage tdc, O_Octet o)
 * \brief Procédure permettant de retourner le CodeBinaire associé à un Octet en entrée à partir d'une TableDeCodage
 *
 * \param tdc : la table de codage permettant de récupérer les données
 * \param o : l'octet dont on souhaite recupérer le code binaire
 * \return CB_CodeBinaire
 */
CB_CodeBinaire TDC_octetVersCodeBinaire(TDC_TableDeCodage tdc, O_Octet o);
/**
 * \fn bool TDC_octetPresent(TDC_TableDeCodage tdc, O_Octet o)
 * \brief Fonction permettant de savoir si le CodeBinaire d'un Octet est présent dans une table de codage
 * 
 * \param tdc : la table de codage permettant de récupérer les données
 * \param o : l'Octet dont on veux vérifier la présence
 * \return Booleen
 */
bool TDC_octetPresent(TDC_TableDeCodage tdc, O_Octet o);

#endif
