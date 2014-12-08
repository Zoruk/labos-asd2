/*============================================================================
 * Name        : ArbreHuffmanBranche.cpp
 * Date        : 18 juil. 2013
 * Author      : Fabien Dutoit
 * Version     : 1.0
 *
 * Description : Classe représentant un arbre de Huffman
 *               Implémentation d'une branche contenant deux sous arbres
 *============================================================================*/

#ifndef ARBREHUFFMANBRANCHE_CPP
#define	ARBREHUFFMANBRANCHE_CPP

#include <vector>

#include "ArbreHuffmanBranche.h"

/*
 * Constructeur d'un arbre vide
 */
ArbreHuffmanBranche::ArbreHuffmanBranche() {
    gauche = nullptr;
    droite = nullptr;
}
/*
 * But: Vérifie si le caractère appartient à l'arbre
 * Entrée: Le caractère dont la présence doit être vérifiée
 * Sortie: Booléen indiquant la présence
 */
bool ArbreHuffmanBranche::contient(char caracter) {
    return (gauche && gauche->contient(caracter)) || (droite && droite->contient(caracter));
}

/*
 * But: Obtenir la fréquence des caractères contenu dans cet arbre
 * Exception: SousArbreVide si au moins un des sous-arbres est non-défini
 */
long ArbreHuffmanBranche::getFrequence() const
{
    if (!gauche || !droite)
    {
        throw SousArbreVide();
    }
    return gauche->getFrequence() + droite->getFrequence();
}

/*
 * But: Setter une valeur de fréquence particulière
 * Entrée: valeur de la fréquence
 * Exception: OperationUniquementPossibleSurUneFeuille si appliqué sur une branche
 */
void ArbreHuffmanBranche::setFrequence(long /*freq*/) {
    throw OperationUniquementPossibleSurUneFeuille();
}

/*
 * But: Opération permettant d'incrémenter la fréquence d'un élément
 * Exception: OperationUniquementPossibleSurUneFeuille si appliqué sur une branche
 */
void ArbreHuffmanBranche::incrementeFrequence() {
    throw OperationUniquementPossibleSurUneFeuille();
}

/*
 * But: Opérations permettant d'accrocher un sous-arbre à gauche ou a droite de l'arbre courant
 * Exception: OperationUniquementPossibleSurUneBranche si appliqué sur une feuille
 */
void ArbreHuffmanBranche::accrocheGauche(ArbreHuffman* sousArbre) {
    if (gauche)
        delete gauche;
    gauche = sousArbre;
}

void ArbreHuffmanBranche::accrocheDroite(ArbreHuffman* sousArbre) {
    if (droite)
        delete droite;
    droite = sousArbre;
}

/*
 * But: Sérialisation de l'arbre
 * Exception: SousArbreVide si au moins un des sous-arbres est non-défini
 */
std::string ArbreHuffmanBranche::toString() {
    if(gauche == nullptr || droite == nullptr){
        throw SousArbreVide();
    }
    
    std::stringstream sstrings;
    sstrings << "(" << gauche->toString() << ";" << droite->toString() << ")";
    return sstrings.str();
}

/*
 * But: Compresser un caractère
 * Entrée: Le caractère à encoder
 * Sortie: Un vecteur représentant les bits correspondant au caractère
 * Exception: SousArbreVide si au moins un des sous-arbres est non-défini
 *            ProblemeEncodage en cas d'erreur d'encodage (caractère manquant pas ex.)
 */
std::vector<bool> ArbreHuffmanBranche::compresse(char caractere)
{
    if (!gauche || !droite)
        throw SousArbreVide();

    std::vector<bool> buffer, tmp;
    if (gauche->contient(caractere)) {
        buffer.push_back(false);
        tmp = gauche->compresse(caractere);
    }
    else if (droite->contient(caractere)) {
        buffer.push_back(true);
        tmp = droite->compresse(caractere);
    }
    else {
        throw ProblemeEncodage();
    }

    buffer.insert(buffer.end(), tmp.begin(), tmp.end());
    return buffer;
}

/*
 * But: Décompresser un caractère
 * Entrée: Un pointeur sur le vecteur de bits à utiliser
 *         Les bits utilisés seront consommés, en cas de problème (par ex.: BitStreamTropCourt) le vecteur ne doit pas être modifié
 * Sortie: Le caractère décompressé
 * Exceptions: SousArbreVide si au moins un des sous-arbres est non-défini
 *             BitStreamTropCourt si le vecteur de bits est trop court pour déterminer un unique caractère             
 */
char ArbreHuffmanBranche::decompresse(std::vector<bool>* bits)
{
    if (!gauche || !droite)
        throw SousArbreVide();

    if (bits->size() == 0)
        throw BitStreamTropCourt();

    std::vector<bool> backup(*bits);

    try
    {
        bool isRight = bits->at(0);
        bits->erase(bits->begin());

        if (isRight)
            return droite->decompresse(bits);
        else
            return gauche->decompresse(bits);
    } catch (const BitStreamTropCourt&) {
        *bits = backup;
        throw;
    } catch (const SousArbreVide&) {
        *bits = backup;
        throw;
    }
}

/*
 * Destructeur
 * Détruit récursivement tout l'arbre
 */
ArbreHuffmanBranche::~ArbreHuffmanBranche() {
    delete gauche;
    delete droite;
}

#endif	/* ARBREHUFFMANBRANCHE_CPP */
