#ifndef UTILITAIRES_H
#define UTILITAIRES_H

#include <stdio.h>

/*
 * fichier utilitaires.h
 * Comporte des fonctions liées à l'écriture dans le fichier de sortie asm
 */

FILE * ouvrirFichier(int first);

extern char * fichierPremierePasse;  
extern char * fichierSecondePasse;  
  
/* Instructions assembleur */
void fprintf_add (int res, int a, int b);
void fprintf_addEBP (int res, int a);
void fprintf_mul (int res, int a, int b);
void fprintf_sou (int res, int a, int b);
void fprintf_div (int res, int a, int b);
void fprintf_cop (int res, int a);
void fprintf_copEIP (int adrRes);
void fprintf_afc (int res, int a);
void fprintf_jmp ();
void fprintf_jmf (int cond);
void fprintf_inf (int res, int a, int b);
void fprintf_sup (int res, int a, int b);
void fprintf_equ (int res, int a, int b);
void fprintf_pri (int res);
void fprintf_cpi (int a, int b);
void fprintf_icp (int a, int b);
void fprintf_and (int res, int a, int b);
void fprintf_or (int res, int a, int b);

#endif
