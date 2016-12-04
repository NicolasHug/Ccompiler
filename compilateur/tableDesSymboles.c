#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "tableDesSymboles.h"

void yyerror(char *s);
extern char messageErreur[100];
extern int erreurExiste;



int indiceCourant = 0;
unSymbole table[TAILLE_TABLE];


void afficherTable() {
  int i = 0;
  printf("---------\nTable des symboles : \n");
  for (i= 0; i<indiceCourant ; i++) {
    printf("%d : %s %d %d\n", i, table[i].nom, table[i].type,
           table[i].estUnArg);
  }
  printf("---------\n");
}


// cleanTable() doit être appelée à chaque fois que des variables temporelles
// sont créés, mais seulement après qu'elles ont toutes été utilisées
// ex : après une affectation, après un if (pour les variables temporelles
// d'évaluation de la cond) après un while (idem)...
void cleanTable() {
  while (indiceCourant > 0 && table[indiceCourant - 1].type == TEMP) {
    indiceCourant--;
  }
}

// Renvoi un symbole a partir de son nom, NULL si non trouvé
unSymbole * getSymbole (char * nom) {
  int i = 0;
  int trouve = 0;
  unSymbole * symbole = NULL;

  while (!trouve && i < indiceCourant) {
    if (table[i].nom != NULL && !strcmp(table[i].nom,nom)) {
      symbole = &table[i];
      trouve = 1;
    }
    i++;
  }
  return symbole;
} 

void checkAffectation(char * nom) {
  unSymbole * symbole = getSymbole(nom);
  if (symbole != NULL && symbole->type == CONST) {
    sprintf(messageErreur,"%s est de type const",nom);
    yyerror(messageErreur);
    erreurExiste = 1;
  }
}
  
void checkAffectationInd(char * nom) {
  unSymbole * symbole = getSymbole(nom);
  if (symbole != NULL && symbole->type != PT) {
    sprintf(messageErreur,"%s n'est pas un pointeur",nom);
    yyerror(messageErreur);
    erreurExiste = 1;
  }
}


void ajouterSymbole(char * nom, char type, char estInit, char estUnArg) {
  if (nom != NULL && getSymbole(nom) != NULL) {
    sprintf(messageErreur,"Symbole %s existe deja",nom);
    yyerror(messageErreur);
    erreurExiste = 1;
  } else {
    unSymbole symbole ;
    symbole.nom = nom;
    symbole.type = type;
    symbole.estInit = estInit;
    symbole.estUnArg = estUnArg;
    table[indiceCourant++] = symbole;
  }
}

void ajouterPlusieursSymboles(char * nom, char type, int taille) {
  unSymbole symbole;
  symbole.nom = nom;
  symbole.type = type;
  symbole.estInit = 1;
  table[indiceCourant++] = symbole;
  indiceCourant += taille;
}

int getNbArgs() {
  int nbArgs = 0;
  while(table[nbArgs].estUnArg) {
    nbArgs++;
  }
  return nbArgs;
}

int getAdresse(char * nom) {
  int i = 0;
  int trouve = 0;
  int adresse = -1;
  int nbArgs = getNbArgs();

  while (!trouve && i < indiceCourant) {
    if (table[i].nom != NULL && ! strcmp(table[i].nom,nom)) {
      trouve = 1;
      if (table[i].estUnArg) {
        adresse = -(nbArgs - i) - 2; // -2 car il y a ebp et pc pushés
      } else {
        adresse = -(nbArgs - i) ;
      }
    }
    i++;
  }
  if (adresse == -1) {
    sprintf(messageErreur,"Symbole %s inconnu",nom);
    yyerror(messageErreur);
    erreurExiste = 1;
  }
  return adresse;
}    

void setInitialise (char * nom) {
  unSymbole * symbole = getSymbole(nom);
  if (symbole != NULL) {
    symbole->estInit = 1;
  }
}

void popTable(int nbPop) {
  indiceCourant -= nbPop;
}

void viderTableSymboles () {
  indiceCourant = 0;
  memset(table,0,TAILLE_TABLE);
}

int getNombreVariablesLocales() {
  return indiceCourant - getNbArgs();
}
