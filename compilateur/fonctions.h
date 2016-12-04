#ifndef FONCTIONS_H
#define FONCTIONS_H

/*
 * Fichier fonctions.h
 * Contient les fonctions liées aux déclarations et aux appels de fonctions
 */

#define NOMBRE_MAX_FONCTIONS 1000
#define NOMBRE_MAX_ARGS 100

// Structure d'un argument
struct unArg {
  int type;
  char nom[20];
};
typedef struct unArg unArg;

// Structure d'une fonction
struct uneFonction {
  char nom[20]; // Nom de la fonction
  int ligneDeb; // ligne où commence la fonction. C'est là que l'on saute lors d'un call
  int nbArgs; // Nombre de parametres que prend la fonction
  int nbArgsPushes; // Nombre de parametres actuellement pushés
  int doitRetourner; // Indique si la fonction est une fonction ou une procedure
  int aRetourne; // Indique si un return a deja été écrit dans le corps de la fonction
  unArg args [NOMBRE_MAX_ARGS]; // tableau des arguments de la fonction
};
typedef struct uneFonction uneFonction;

extern int nbFonctions; // Le nombre de fonction rencontrées jusqu'alors


// Fonctions par ordre de lecture par Yacc

// manipule ebp et esp pour mettre en place le contexte de la nouvelle fonction
void debutFonction(char * nom, int doitRetourner);
// indique que la fonction rencontre prend l'argument nom de type type
void definirArg(int type, char * nom) ;
// Restaure le contexte de la fonction précédente
void finFonction();
// Incrémente esp du nombre de variables locales déclarees
void debutAppel(char * nom);
// Push la variable var pour la passer en parametre
void pushParam (char * var);
// Effectue le Call
void appel(char * nom, int nbArgsPushes);
// Stoque le retour dans ert restaure le contexte précédent
void retour(int adr);

void afficherTableFonctions() ;


#endif // FONCTIONS_H
