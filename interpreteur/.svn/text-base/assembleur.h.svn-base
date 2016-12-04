#define TAILLE_RAM 1000
#define TAILLE_ROM 1000

struct uneInstruction {
  void (* ins) (int, int, int);
  int arg1;
  int arg2;
  int arg3;
};
typedef struct uneInstruction uneInstruction;


// initialise la ram, la rom, et les registres
void initInterpreteur (int debug);

// Ajoute une instruction dans la rom
void ajouterIns (void (* pf_ins) (int, int, int), ...) ;

// Execute les instructions contenues dans la rom jusqu'à la fin du programme
void execute();

// Fonctions ASM
// Argument blop <=> non utilisé
void asm_add        (int adrRes, int adrOp1, int adrOp2);
void asm_addEBP     (int adrRes, int adrOp1, int blop);
void asm_sou        (int adrRes, int adrOp1, int adrOp2);
void asm_mul        (int adrRes, int adrOp1, int adrOp2);
void asm_div        (int adrRes, int adrOp1, int adrOp2);
void asm_afc        (int adrRes, int val, int blop);
void asm_cop        (int adrDestination, int adrOrigine, int blop);
void asm_copERT     (int adrDestination, int blop1, int blop2);
void asm_pri        (int adr, int blop, int blop2);
void asm_jmp        (int ins, int blop, int blop2);
void asm_jmf        (int adrCond, int ins, int blop);
void asm_sup        (int adrRes, int adrOp1, int adrOp2);
void asm_inf        (int adrRes, int adrOp1, int adrOp2);
void asm_equ        (int adrRes, int adrOp1, int adrOp2);
void asm_cpi        (int adrRes, int adrOp1, int blop);
void asm_icp        (int adrRes, int adrOp1, int blop);
void asm_and        (int adrRes, int adrOp1, int adrOp2);
void asm_or         (int adrRes, int adrOp1, int adrOp2);
void asm_call       (int ligneFonction, int blop1, int blop2);
void asm_ret        (int decrementESP, int blop2, int blop3);
void asm_pushEBP    (int blop, int blop1, int blop2);
void asm_pushVar    (int adrVar, int blop1, int blop2);
void asm_pop        (int blop1, int blop2, int blop3);
void asm_movEBPESP  (int blop1, int blop2, int blop3) ;
void asm_movESPEBP  (int blop1, int blop2, int blop3) ;
void asm_incEsp     (int inc, int blop1, int blop2); // incrémentation de esp
void asm_ert        (int adr, int blop1, int blop2);
