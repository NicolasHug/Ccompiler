#ifndef EXPR_ARITHMETIQUES_H
#define EXPR_ARITHMETIQUES_H

/* 
 * Fichier exprArithmetiques.h
 * Contient les fonctions appelées lorsque yacc rencontre une expression
 * arithmetique
 */

int exprEntier (int entier);
int exprNom (char * nom);
int exprPlus (int op1, int op2);
int exprMoins (int op1, int op2);
int exprFois (int op1, int op2);
int exprDiv (int op1, int op2);
int exprOppose (int entier);
int exprEqu (int op1, int op2);
int exprInf (int op1, int op2);
int exprInfEgal (int op1, int op2);
int exprSup(int op1, int op2);
int exprSupEgal (int op1, int op2);
int exprOu (int op1, int op2);
int exprAcces (int op1);
int exprAdresse (char * op1);
int exprCrochet (char * tab, int indice);
int exprAppel (char * fonction, int nbArgsPushes);

#endif
