#include "exprArithmetiques.h"
#include "tableDesSymboles.h"
#include "compilateur.h"
#include <stdio.h>


void yyerror(char *s);
extern char messageErreur[100];
extern int erreurExiste;


int exprEntier (int entier) {
  ajouterSymbole(NULL,TEMP,1,0);
  fprintf_afc(getNombreVariablesLocales()-1, entier);
  return getNombreVariablesLocales()-1;
}

int exprNom (char * nom) {
  unSymbole * s = getSymbole (nom);
  if (s!= NULL && !s->estInit) {
    sprintf(messageErreur,"Lecture sur %s %d non initialisee",nom,s->estInit);
    yyerror(messageErreur);
    erreurExiste = 1;
  }
  ajouterSymbole(NULL,TEMP,1,0);
  fprintf_cop(getNombreVariablesLocales()-1, getAdresse(nom));
  return getNombreVariablesLocales() -1;
}

int exprPlus (int op1, int op2) {
  fprintf_add (op1, op1,op2);
  return op1;
};

int exprMoins (int op1, int op2) {
  fprintf_sou (op1, op1,op2);
  return op1;
};

int exprFois (int op1, int op2) {
  fprintf_mul (op1, op1,op2);
  return op1;
};

int exprDiv (int op1, int op2) {
  fprintf_div (op1, op1,op2);
  return op1;
};

int exprOppose (int entier) {
  ajouterSymbole(NULL,TEMP,1,0);
  fprintf_afc(getNombreVariablesLocales() - 1, 0);
  fprintf_sou (entier, getNombreVariablesLocales() - 1,entier);
  return entier;
}

int exprEqu(int op1, int op2) {
  fprintf_equ(op1,op1,op2);
  return op1;
}

int exprInf(int op1, int op2) {
  fprintf_inf(op1,op1,op2);
  return op1;
}

int exprInfEgal (int op1, int op2) {
  ajouterSymbole(NULL,TEMP,1,0);
  fprintf_inf(getNombreVariablesLocales() - 1, op1, op2);
  ajouterSymbole(NULL,TEMP,1,0);
  fprintf_equ(getNombreVariablesLocales() - 1, op1, op2);
  fprintf_add(getNombreVariablesLocales() - 1,
              getNombreVariablesLocales() - 1,
              getNombreVariablesLocales() - 2);
  return getNombreVariablesLocales() - 1;
}

int exprSup(int op1, int op2) {
  fprintf_sup(op1,op1,op2);
  return op1;
}

int exprSupEgal (int op1, int op2) {
  ajouterSymbole(NULL,TEMP,1,0);
  fprintf_sup(getNombreVariablesLocales() - 1, op1, op2);
  ajouterSymbole(NULL,TEMP,1,0);
  fprintf_equ(getNombreVariablesLocales() - 1, op1, op2);
  fprintf_add(getNombreVariablesLocales() - 1, getNombreVariablesLocales() - 1,
              getNombreVariablesLocales() - 2);
  return getNombreVariablesLocales() - 1;
}

int exprOu (int op1, int op2) {
  ajouterSymbole(NULL,TEMP,1,0);
  fprintf_add(getNombreVariablesLocales() - 1, op1,op2) ;
  return getNombreVariablesLocales() - 1;
}

int exprAcces (int op1) {
  ajouterSymbole(NULL,TEMP,1,0);
  fprintf_cpi(getNombreVariablesLocales() - 1, op1);
  return getNombreVariablesLocales() - 1;
}

int exprAdresse (char * op1) {
  ajouterSymbole(NULL,TEMP,1,0);
  fprintf_afc(getNombreVariablesLocales() - 1, getAdresse(op1));
  ajouterSymbole(NULL,TEMP,1,0);
  fprintf_addEBP(getNombreVariablesLocales() - 1,
                 getNombreVariablesLocales() - 2);
  return getNombreVariablesLocales() - 1;
}

int exprCrochet (char * tab, int indice) {
  checkAffectationInd(tab);
  ajouterSymbole(NULL,TEMP,1,0);
  fprintf_add(getNombreVariablesLocales() - 1,getAdresse(tab),indice);
  ajouterSymbole(NULL,TEMP,1,0);
  fprintf_cpi (getNombreVariablesLocales() - 1,
               getNombreVariablesLocales() - 2);
  return getNombreVariablesLocales() - 1;
}

int exprAppel (char * fonction, int nbArgsPushes) {
  appel(fonction, nbArgsPushes);
  ajouterSymbole(NULL,TEMP,1,0);
  fprintf_copEIP(getNombreVariablesLocales() - 1);
  return getNombreVariablesLocales() - 1;
}
