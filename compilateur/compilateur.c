#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compilateur.h"

#define TAILLE_MAX_PILE_JUMPS 1000
#define NOMBRE_MAX_FOR 100


int cmptInst ;

unJump jumps[NOMBRE_MAX_JUMPS];
int nbJumps;
// pileJumps contient les indices des sauts dans le tableau jumps (pour while
// if et for)
int pileJumps [TAILLE_MAX_PILE_JUMPS];
int spJumps; // Pointeur sur PileJumps

// Tableau des boucles for rempli au fur et à mesure
jumpFor fors[NOMBRE_MAX_FOR];
int nbFors; // nombre courant de for écrits



void pushPileJump (int indice) {
  pileJumps[spJumps++] = indice;
}

int popPileJumps() {
  return pileJumps[--spJumps];
}


/* Fonctions liés aux while */
void condWhile() {
  unJump jmf = {-1,cmptInst,-1};
  jumps[nbJumps] = jmf;
  pushPileJump(nbJumps);
}

void debutWhile() {
  jumps[nbJumps++].ligneIns = cmptInst;
}

void finWhile() {
  int indiceJMP = nbJumps++;
  int indiceJMF = popPileJumps();
  jumps[indiceJMP].ligneIns = cmptInst;

  jumps[indiceJMP].ligneSaut = jumps[indiceJMF].ligneAvantCond ;
  // +1 car il y le JMP à éviter
  jumps[indiceJMF].ligneSaut = jumps[indiceJMP].ligneIns + 1;
}


/* Fonctions liés aux if */
void debutIf() {
  unJump jmf = {cmptInst,-1, -1};
  jumps[nbJumps] = jmf;
  pushPileJump(nbJumps++);
}

void finIf() {
  int indiceJMP = nbJumps++;
  int indiceJMF = popPileJumps();
  jumps[indiceJMP].ligneIns = cmptInst;
  // Par défaut s'il n'y a pas de else, on jmp juste a la ligne suivante (pas
  // d'effet)
  jumps[indiceJMP].ligneSaut = cmptInst + 1;
  // On ajoute un JMP dans la pileJumps mais on ne le prend pas en compte par
  // défaut s'il n'y a pas de else (spJumps --) Pour ne pas encombrer la
  // pileJumps
  pushPileJump(indiceJMP);
  spJumps --;
  // +1 car il faut éviter le JMP
  jumps[indiceJMF].ligneSaut = cmptInst + 1;
}

void debutElse() {
  // Il y a un else, on rétablit le JMP ajouté au finIf()
  spJumps++;
}

void finElse () {
  int indiceJMP = popPileJumps();
  jumps[indiceJMP].ligneSaut = cmptInst;
}


/* Fonctions liés aux for */
void condFor() {
  fors[nbFors++].ligneCond = cmptInst;
}

void debutFor() {
  fors[nbFors-1].ligneAffect = cmptInst;
  fors[nbFors-1].ligneJmf = cmptInst - 2;
}

void milieuFor() {
  fors[nbFors-1].ligneInstr = cmptInst;
}

void finFor() {
  fors[nbFors-1].ligneFin = cmptInst;
  jumpFor monFor = fors[--nbFors];

  unJump monjump1 = {monFor.ligneJmf, -1, monFor.ligneFin + 1};
  jumps[nbJumps++] = monjump1;

  unJump monjump2 = {monFor.ligneJmf + 1, -1, monFor.ligneInstr};
  jumps[nbJumps++] = monjump2;

  unJump monjump3 = {monFor.ligneInstr - 1, -1, monFor.ligneCond};
  jumps[nbJumps++] = monjump3;

  unJump monjump4 = {monFor.ligneFin, -1, monFor.ligneAffect};
  jumps[nbJumps++] = monjump4;
}


// Renvoi la ligne de saut d'un jmp ou jmf situé à ligneIns
int  getLigneSaut (int ligneIns) {
  int i = 0;
  int trouve = 0;
  int ligneSaut = 0;
  while (!trouve && i < nbJumps) {
    if (jumps[i].ligneIns == ligneIns) {
      trouve = 1;
      ligneSaut = jumps[i].ligneSaut;
    }
      i++;
  }
  return ligneSaut;
}


// initialisation du compilateur
void initCompilateur() {
	FILE * fd = ouvrirFichier(1);
  fprintf(fd, "jmp @\n");
	fclose(fd);

  cmptInst = 1; // 1 car on a le jmp du tout début
  spJumps = 0;
  nbJumps = 0;
  nbFors = 0;
  nbFonctions = 0;

  memset(jumps,0,NOMBRE_MAX_JUMPS * sizeof(unJump));
  memset(pileJumps,0,TAILLE_MAX_PILE_JUMPS * sizeof(int));
  memset(fors,0,NOMBRE_MAX_FOR * sizeof(jumpFor));
}

void secondePasse() {
  int ligne = 0;
  char c = 0;
  FILE * fd = fopen(fichierPremierePasse,"r+");
  FILE * fdsp = fopen(fichierSecondePasse,"w"); // seconde passe

  afficherTableFonctions();
  while ((c = fgetc(fd)) && c != EOF) {
       if (c == '@') {
         fprintf(fdsp,"%d",getLigneSaut(ligne));
       }
       else {
	 if (c == '\n') {
	   ligne++;
	 }
	 fprintf(fdsp,"%c",c);
       }
  }
}
