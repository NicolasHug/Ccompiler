#ifndef TABLE_DES_SYMBOLES_H
#define TABLE_DES_SYMBOLES_H

/*
 * Fichier tableDesSymboles.h
 * Contient les fonctions liées à la manipulation de la table des symboles
 */

#define INT 0
#define CONST 1
#define PT 2
#define TEMP 3
#define TAILLE_TABLE 500

// Structure d'un symbole (un symbole = une variable, temporaire ou non)
struct unSymbole {
  char * nom;
  char type;
  char estInit;
  char estUnArg;
};
typedef struct unSymbole unSymbole;

// Ajoute un symbole dans la table
void ajouterSymbole(char * nom, char type, char estInit, char estUnArg) ;

// Ajoute un tableau dans la table
void ajouterPlusieursSymboles(char * nom, char type, int taille);

// Renvoi l'adresse d'un symbole, -1 si non trouve
int getAdresse(char * nom);

// Renvoi le symbole souhaitee, NULL si non trouve
unSymbole * getSymbole(char * nom);

// set le symbole à "initialisé"
void setInitialise (char * nom);

// Efface les dernières variables temporaires de la table en modifiant indiceCourant
void cleanTable();

// Efface toutes les entrees de la table
void viderTableSymboles();

// Affiche la table des symboles
void afficherTable();

// Renvoie le nombre de variables locales de la table
// Prend en compte les variables temporaires
int getNombreVariablesLocales();

// Renvoie le nombre d'arguments présents dans la table
int getNbArgs();

// Verifie si la variable peut être affectée ou non
void checkAffectation(char * nom);

// Verifie si la variable est bien un pointeur
void checkAffectationInd(char * nom);
#endif
