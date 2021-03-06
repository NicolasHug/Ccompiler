#include <stdio.h>

#include "utilitaires.h"
#include "tableDesSymboles.h"
#include "compilateur.h"

char * fichierPremierePasse = "./asmPremierePasse";  
char * fichierSecondePasse = "./asm";  

FILE * ouvrirFichier(int first) {
  FILE * fd = NULL;
  if (first) {
    fd = fopen(fichierPremierePasse, "w");
  } else {
    fd = fopen(fichierPremierePasse, "a");
  }
  return fd;
}   

void fprintf_add (int res, int a, int b) {
  FILE * fd = ouvrirFichier(0);
  fprintf(fd, "add %d %d %d\n", res, a ,b);
  fclose(fd);
  cmptInst++;
}

void fprintf_addEBP (int res, int a) {
  FILE * fd = ouvrirFichier(0);
  fprintf(fd, "add %d %d ebp\n", res, a);
  fclose(fd);
  cmptInst++;
}

void fprintf_mul (int res, int a, int b){
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"mul %d %d %d\n", res, a ,b);
  fclose(fd);
  cmptInst++;
}
void fprintf_sou (int res, int a, int b){
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"sou %d %d %d\n", res, a ,b);
  fclose(fd);
  cmptInst++;
}
void fprintf_div (int res, int a, int b){
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"div %d %d %d\n", res, a ,b);
  fclose(fd);
  cmptInst++;
}
void fprintf_cop (int res, int a){
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"cop %d %d\n", res, a);
  fclose(fd);
  cmptInst++;
}
void fprintf_copEIP (int adrRes) {
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"cop %d ert\n", adrRes);
  fclose(fd);
  cmptInst++;
}
void fprintf_afc (int res, int a){
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"afc %d %d\n", res, a);
  fclose(fd);
  cmptInst++;
}
void fprintf_jmp (){
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"jmp @\n"); // @ sera remplacé lors de la seconde passe
  fclose(fd);
  cmptInst++;
}
void fprintf_jmf (int cond){
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"jmf %d @\n", cond);
  fclose(fd);
  cmptInst++;
}
void fprintf_inf (int res, int a, int b){
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"inf %d %d %d\n", res, a ,b);
  fclose(fd);
  cmptInst++;
}
void fprintf_sup (int res, int a, int b){
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"sup %d %d %d\n", res, a ,b);
  fclose(fd);
  cmptInst++;
}
void fprintf_equ (int res, int a, int b){
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"equ %d %d %d\n", res, a ,b);
  fclose(fd);
  cmptInst++;
}
void fprintf_pri (int res){
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"pri %d\n", res);
  fclose(fd);
  cmptInst++;
}

void fprintf_cpi (int a, int b) {
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"cpi %d %d\n", a ,b);
  fclose(fd);
  cmptInst++;
}
void fprintf_icp (int a, int b) {
  FILE * fd = ouvrirFichier(0);
  fprintf(fd,"icp %d %d\n", a ,b);
  fclose(fd);
  cmptInst++;
}
