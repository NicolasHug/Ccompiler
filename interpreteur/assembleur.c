#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "assembleur.h"

int pc;  // <=> eip
int esp; // registre haut de la pile
int ebp; // registre base de la pile
int ert; // registre de valeur de retour de fonction
int nbInstructions; // nombre d'instructions du programme

int ram[TAILLE_RAM]; // zone d'execution du programme : pile vers le haut
uneInstruction rom [TAILLE_ROM]; // Stoque le programme

// mode debug de l'interpreteur
int debug;

void initInterpreteur (int blopDebug) {
  pc = 0;
  esp = 0;
  ebp = 0;
  ert = 0;
  nbInstructions = 0;
  debug = blopDebug;
  memset(ram,0,TAILLE_RAM * sizeof(int));
  memset(rom,0,TAILLE_ROM * sizeof(uneInstruction));
}

void ajouterIns (void (* pf_ins) (int, int, int), ...) {
  va_list ap;
  va_start(ap,pf_ins);
  int arg1 = va_arg(ap,int);
  int arg2 = va_arg(ap,int);
  int arg3 = va_arg(ap,int);

  // Creation et ajout d'une nouvelle instruction
  uneInstruction newIns = {pf_ins,arg1,arg2,arg3};
  rom[nbInstructions++] = newIns;
  va_end(ap);
}

// On effectue les instructions contenues dans la rom tant qu'on n'est pas à la
// fin...
void execute () {
  while (pc < nbInstructions) {
    rom[pc].ins(rom[pc].arg1, rom[pc].arg2, rom[pc].arg3);
    pc++;
  } 
}

void printDebug () {
  int i = 0;
  int j = 0;
  int nbEspaces = 3;
  int tailleRamAffichee = 30;
  for (i = 0; i< ebp; i++) {
    for (j = 0; j< nbEspaces; j++) {
      printf(" ");
    }
  }
  printf("ebp\n");

  for (i = 0; i< esp; i++) {
    for (j = 0; j< nbEspaces; j++) {
      printf(" ");
    }
  }
  printf("esp\n");

  for (i=0; i < tailleRamAffichee; i++) {
    printf("%2d|", i);
  }
  printf("\n");
  for (i=0; i < tailleRamAffichee; i++) {
    printf("%2d|", ram[i]);
  }
  printf("\nebp = %d, esp = %d, pc = %d, ert = %d\n",ebp,esp,pc,ert);
  printf("----------------------------------\n");
}

void asm_add (int adrRes, int adrOp1, int adrOp2) {
  ram[ebp + adrRes] = ram[ebp + adrOp1] + ram[ebp + adrOp2];
  if (debug) {
    printf("add %d %d %d\n",adrRes, adrOp1, adrOp2);
    printDebug();
  }
}

void asm_addEBP (int adrRes, int adrOp1, int blop) {
  ram[ebp + adrRes] = ram[ebp + adrOp1] + ebp;
  if (debug) {
    printf("add %d %d ebp\n",adrRes, adrOp1);
    printDebug();
  }
}

void asm_sou (int adrRes, int adrOp1, int adrOp2) {
  ram[ebp + adrRes] = ram[ebp + adrOp1] - ram[ebp + adrOp2];
  if (debug) {
    printf("sou %d %d %d\n",adrRes, adrOp1, adrOp2);
    printDebug();
  }
}

void asm_mul (int adrRes, int adrOp1, int adrOp2) {
  ram[ebp + adrRes] = ram[ebp + adrOp1] * ram[ebp + adrOp2];
  if (debug) {
    printf("mul %d %d %d\n",adrRes, adrOp1, adrOp2);
    printDebug();
  }
}

void asm_div (int adrRes, int adrOp1, int adrOp2) {
  ram[ebp + adrRes] = ram[ebp + adrOp1] / ram[ebp + adrOp2];
  if (debug) {
    printf("div %d %d %d\n",adrRes, adrOp1, adrOp2);
    printDebug();
  }
}

void asm_afc(int adrRes, int val,int blop) {
  ram[ebp + adrRes] = val;
  if (debug) {
    printf("afc %d %d\n",adrRes, val);
    printDebug();
  }
}

void asm_cop(int adrDestination, int adrOrigine, int blop) {
  ram[ebp + adrDestination] = ram[ebp + adrOrigine];
  if (debug) {
    printf("cop %d %d\n",adrDestination, adrOrigine);
    printDebug();
  }
}

// Copie ert dans à l'adresse désirée
void asm_copERT (int adrDestination, int blop1, int osef2) {
  ram[ebp + adrDestination] = ert;
  if (debug) {
    printf("copERT %d\n",adrDestination);
    printDebug();
  }
}

void asm_pri(int adr, int blop, int osef2) {
  printf("%d\n",ram[ebp + adr]);
  if (debug) {
    printf("pri %d\n",adr);
    printDebug();
  }
}

void asm_jmp(int ins, int blop, int osef2) {
  pc = ins;
  pc--; // Pour éviter le pc++ de execute()
  if (debug) {
    printf("jmp %d\n",ins);
    printDebug();
  }
}

void asm_jmf(int adrCond, int ins, int blop) {
  if (!ram[ebp + adrCond]) {
    pc = ins;
    pc--; // Pour éviter le pc++ de execute()
  }
  if (debug) {
    printf("jmf %d %d\n",adrCond, ins);
    printDebug();
  }
}

void asm_sup (int adrRes, int adrOp1, int adrOp2) {
  ram[ebp + adrRes] = (ram[ebp + adrOp1] > ram[ebp + adrOp2]);
  if (debug) {
    printf("sup %d %d %d\n",adrRes, adrOp1, adrOp2);
    printDebug();
  }
}

void asm_inf (int adrRes, int adrOp1, int adrOp2) {
  ram[ebp + adrRes] = (ram[ebp + adrOp1] < ram[ebp + adrOp2]);
  if (debug) {
    printf("inf %d %d %d\n",adrRes, adrOp1, adrOp2);
    printDebug();
  }
}

void asm_equ (int adrRes, int adrOp1, int adrOp2) {
  ram[ebp + adrRes] = (ram[ebp + adrOp1] == ram[ebp + adrOp2]);
  if (debug) {
    printf("equ %d %d %d\n",adrRes, adrOp1, adrOp2);
    printDebug();
  }
}

// Equivalent à un a = *b
void asm_cpi (int adrRes, int adrOp1, int blop) {
  ram[ebp + adrRes] = ram[ram[ebp + adrOp1]];
  if (debug) {
    printf("cpi %d %d\n",adrRes, adrOp1);
    printDebug();
  }
}

// Equivalent à un *a = b
void asm_icp (int adrRes, int adrOp1, int blop) {
  ram[ram[ebp + adrRes]] = ram[ebp + adrOp1];
  if (debug) {
    printf("icp %d %d\n",adrRes, adrOp1);
    printDebug();
  }
}

void asm_and (int adrRes, int adrOp1, int adrOp2){
  ram[ebp + adrRes] = ram[ebp + adrOp1] && ram[ebp + adrOp2];
  if (debug) {
    printf("and %d %d %d\n",adrRes, adrOp1, adrOp2);
    printDebug();
  }
}

void asm_or (int adrRes, int adrOp1, int adrOp2) {
  ram[ebp + adrRes] = ram[ebp + adrOp1] || ram[ebp + adrOp2];
  if (debug) {
    printf("or %d %d %d\n",adrRes, adrOp1, adrOp2);
    printDebug();
  }
}

void asm_call (int adr, int blop1, int osef2) {
  // push pc ( pas pc + 1 car l'incrémentation sera faite par execute)
  ram[esp++] = pc ;
  pc = adr; 
  pc--; // Pour éviter le pc++ de execute
  if (debug) {
    printf("call %d\n",adr);
    printDebug();
  }
}

// On décrémente esp du nombre d'arguments pushés après avoir remis PC à sa
// bonne valeur
void asm_ret (int decrementESP, int blop2, int osef3) {
  pc = ram[--esp];
  esp -= decrementESP; 
  if (debug) {
    printf("ret %d\n",decrementESP);
    printDebug();
  }
}

void asm_pushEBP (int blop, int osef1, int osef2) {
  ram[esp++] = ebp;
  if (debug) {
    printf("pushEBP\n");
    printDebug();
  }
}
void asm_pushVar (int adrVar, int blop1, int osef2) {
  ram[esp++] = ram[ebp + adrVar];
  if (debug) {
    printf("pushVar %d\n",adrVar);
    printDebug();
  }
}

// affecte ebp à la valeur contenue au sommet de la pile
void asm_pop (int adr, int blop1, int osef2) {
  ebp = ram[--esp];
  if (debug) {
    printf("pop\n");
    printDebug();
  }
}

void asm_movEBPESP (int blop1, int osef2, int osef3) {
  ebp = esp;
  if (debug) {
    printf("mov ebp esp\n");
    printDebug();
  }
}

void asm_movESPEBP (int blop1, int osef2, int osef3) {
  esp = ebp;
  if (debug) {
    printf("mov esp ebp\n");
    printDebug();
  }
}

// Incrémente ESP de la valeur indiqué
// Utilisé avant les appels de fonctions pour mettre à jour sa valeur
void asm_incEsp(int inc, int blop1, int osef2) {
  esp += inc;
  if (debug) {
    printf("incESP %d\n", inc);
    printDebug();
  }
}

// Copie la ert dans la variable souhaitée
void asm_ert (int adr, int blop1, int osef2) {
  ert = ram[ebp + adr];
  if (debug) {
    printf("ert %d\n", adr);
    printDebug();
  }
}
