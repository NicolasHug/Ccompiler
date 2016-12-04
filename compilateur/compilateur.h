#ifndef COMPILTAEUR_H 
#define COMPILATEUR_H

/* 
 * Fichier compilateur.h
 * Contient ou inclut toutes les fonctions necessaires au compilateur
 */

#include "fonctions.h"
#include "utilitaires.h"
#include "tableDesSymboles.h"

#define NOMBRE_MAX_JUMPS 1000

// structure d'un saut pour les if et les while
struct unJump {
  int ligneIns;
  int ligneAvantCond; // Uniquement pour les while
  int ligneSaut;
};
typedef struct unJump unJump;

struct jumpFor {
  int ligneCond;
  int ligneJmf;
  int ligneAffect;
  int ligneInstr;
  int ligneFin;
};
typedef struct jumpFor jumpFor;

extern int cmptInst; // Nombre courant d'instructions écrites
extern unJump jumps[NOMBRE_MAX_JUMPS]; // Tableau des sauts rempli au fur et à mesure du parsing
extern int nbJumps; // indice courant dans jumps

// Initialisation du compilateur
void initCompilateur();
// remplace tous les '@' par le numéro de ligne de saut adéquat
void secondePasse() ;

// Fonctions pour traitement des while
void condWhile();
void debutWhile();
void finWhile();

// Fonctions pour traitement des if
void debutIf();
void finIf();
void debutElse();
void finElse();

// Fonctions pour traitement des for
void condFor();
void debutFor();
void milieuFor();
void finFor();

#endif
