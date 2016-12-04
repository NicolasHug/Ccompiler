#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions.h"
#include "tableDesSymboles.h"
#include "compilateur.h"
#include "utilitaires.h"

void yyerror(char *s);
extern char messageErreur[100];
extern int erreurExiste;


uneFonction fonctions[NOMBRE_MAX_FONCTIONS];
int nbFonctions;

// La fonction couramment appellee (manipulee dans les fonctions d'appel pour la gestion des types d'arguments)
uneFonction * fonctionAppellee; 

void debutFonction(char * nom, int doitRetourner) {
  
  viderTableSymboles();

  if (strcmp(nom,"main") == 0) {
    unJump startJump = {0,-1,cmptInst};
    jumps[nbJumps++] = startJump;
  }
  else {
    FILE * fd = ouvrirFichier(0);
    fprintf(fd,"psh ebp\n");
    fprintf(fd,"mov ebp esp\n");
    fclose(fd);
    cmptInst += 2;
  }

  // Ajout de la fonction dans la table des fonctions
  uneFonction f;
  strcpy(f.nom,nom);
  f.ligneDeb = cmptInst;
  f.doitRetourner = doitRetourner;
  f.aRetourne = 0;
  f.nbArgs = 0;
  f.nbArgsPushes = 0;
  fonctions[nbFonctions++] = f;
}


int getAdresseFonction (char * nom) {
  int i = 0;
  int trouve = 0;
  int ret = 0;
  while (i < nbFonctions && !trouve) {
    if (strcmp(fonctions[i].nom,nom) == 0) {
      trouve = 1;
      ret = fonctions[i].ligneDeb;
    }
    i++;
  }
  return ret - 2; // -2 car il y a psh ebp et mov ebp esp juste avant
}

/*int fonctionExiste(char * nom) {
  int i = 0;
  int trouve = 0;
  while (i<nbFonctions && !trouve) {
    if (strcmp(fonctions[i].nom, nom) == 0) {
      trouve = 1;
    }
    i++;
  }
  return trouve;
}*/

uneFonction * getFonction (char * nom) {
  int i = 0;
  int trouve = 0;
  uneFonction * f = NULL;
  while (i < nbFonctions && !trouve) {
    if (strcmp(fonctions[i].nom,nom) == 0) {
      trouve = 1;
      f = malloc(sizeof(uneFonction));
      *f = fonctions[i];
    }
    i++;
  }
  return f;
}

// Demande l'incrémentation d'esp du nombre de variables déclarés dans la fonction appellante
void debutAppel(char * nom) { 
  fonctionAppellee = getFonction(nom);
  if (fonctionAppellee != NULL) {
    FILE * fd = ouvrirFichier(0);
    fprintf(fd,"esp %d\n", getNombreVariablesLocales());
    fclose(fd);
    cmptInst++;
  } else {
    sprintf(messageErreur,"Fonction %s n'est pas connue",nom);
    yyerror(messageErreur);
    erreurExiste = 1;
  }
}

// Effecture le cal
void appel(char * nom, int nbArgsPushes) {
  uneFonction * f = getFonction(nom);
  if (f!= NULL && nbArgsPushes != f->nbArgs) {
    sprintf(messageErreur,"Nombre d'arguments attendus : %d",f->nbArgs);
    yyerror(messageErreur);
    erreurExiste = 1;
  }
  if (fonctionAppellee != NULL) {
    fonctionAppellee->nbArgsPushes = 0; // On reinitialise pour les prochains appels
  }
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"cal %d\n", getAdresseFonction(nom));
  fclose(fd);
  cmptInst++;
}

// Push un paramètre dans la ram
void pushParam (char * var) {
  unSymbole * s = getSymbole (var);
  if (s!= NULL && !s->estInit) {
    sprintf(messageErreur,"Lecture sur %s non initialisee",var);
    yyerror(messageErreur);
    erreurExiste = 1;
  }
  if (fonctionAppellee != NULL) {
      if (fonctionAppellee->args[fonctionAppellee->nbArgsPushes].type != s->type) {
        sprintf(messageErreur,"Mauvais type passé en argument.");
        yyerror(messageErreur);
        erreurExiste = 1;
      }
      fonctionAppellee->nbArgsPushes += 1;
  }
  FILE * fd = ouvrirFichier(0);
  fprintf(fd, "psh %d\n", getAdresse(var));
  fclose(fd);
  cmptInst++;
}

void afficherTableFonctions() {
  int i = 0;
  printf("---------\nTable des fonctions\n");

  for (i = 0; i<nbFonctions;i++) {
    printf("%s %d %d %d\n",fonctions[i].nom, fonctions[i].ligneDeb, fonctions[i].doitRetourner, fonctions[i].aRetourne);
  }
}

void finFonction() {
  uneFonction fonctionCourante = fonctions[nbFonctions - 1];
  if (fonctionCourante.doitRetourner && ! fonctionCourante.aRetourne) {
    sprintf(messageErreur,"%s doit retourner",fonctionCourante.nom);
    yyerror(messageErreur);
    erreurExiste = 1;
  }
  else if (!fonctionCourante.doitRetourner && fonctionCourante.aRetourne) {
    sprintf(messageErreur,"%s ne doit pas retourner",fonctionCourante.nom);
    yyerror(messageErreur);
    erreurExiste = 1;
  }

  else if (!fonctionCourante.doitRetourner) {
    FILE * fd = ouvrirFichier(0);
    fprintf(fd,"mov esp ebp\n");
    fprintf(fd,"pop ebp\n");
    fprintf(fd,"ret %d\n", getNbArgs());
    fclose(fd);
    cmptInst += 3;
  }

  cleanTable(); // Il faut cleaner pour la variable temporaire squattée par le ert
  afficherTable();
}

void retour(int adr) {
  uneFonction * fonctionCourante = &fonctions[nbFonctions - 1];
  if (strcmp(fonctionCourante->nom,"main") != 0) {
    FILE * fd = ouvrirFichier(0);
    fprintf(fd,"ert %d\n", adr);
    fprintf(fd,"mov esp ebp\n");
    fprintf(fd,"pop ebp\n");
    fprintf(fd,"ret %d\n", getNbArgs());
    fclose(fd);
    cmptInst += 4;
  }
  fonctionCourante->aRetourne = 1;
  cleanTable(); // Il faut cleaner pour la variable temporaire squattée par le ert
}

// Permet de connaitre le nombre d'args d'une fonction, leurs types et leurs noms
void definirArg(int type, char * nom) {
  uneFonction *fCourante = &fonctions[nbFonctions-1];
  unArg newArg;

  newArg.type = type;
  strcpy(newArg.nom, nom);
  fCourante->args[fCourante->nbArgs++] = newArg;

  ajouterSymbole(nom,type,1,1);
}

