%{
#include <stdio.h>
#include "assembleur.h"

void yyerror(const char *s);
int yylex();
%}

%token tAdd tMul tSou tDiv tCop tAfc tJmp tJmf tInf tSup tEqu tPri tEntier tIcp tCpi tOr tAnd tCall tRet tPush tPop tEsp tEbp tMov tErt
%start ProgrammeASM

%%

ProgrammeASM: Instruction;
ProgrammeASM: Instruction ProgrammeASM;

Instruction: tAdd tEntier tEntier tEntier 	{ajouterIns(asm_add,$2,$3,$4);};
Instruction: tAdd tEntier tEntier tEbp 	    {ajouterIns(asm_addEBP,$2,$3);};
Instruction: tMul tEntier tEntier tEntier 	{ajouterIns(asm_mul,$2,$3,$4);}
Instruction: tSou tEntier tEntier tEntier 	{ajouterIns(asm_sou,$2,$3,$4);};
Instruction: tDiv tEntier tEntier tEntier 	{ajouterIns(asm_div,$2,$3,$4);};
Instruction: tCop tEntier tEntier 		{ajouterIns(asm_cop,$2,$3);};
Instruction: tCop tEntier tErt 		{ajouterIns(asm_copERT,$2);};
Instruction: tAfc tEntier tEntier 		{ajouterIns(asm_afc,$2,$3);};
Instruction: tJmp tEntier 			{ajouterIns(asm_jmp,$2);};
Instruction: tJmf tEntier tEntier 		{ajouterIns(asm_jmf,$2,$3);};
Instruction: tInf tEntier tEntier tEntier 	{ajouterIns(asm_inf,$2,$3,$4);};
Instruction: tSup tEntier tEntier tEntier 	{ajouterIns(asm_sup,$2,$3,$4);};
Instruction: tEqu tEntier tEntier tEntier 	{ajouterIns(asm_equ,$2,$3,$4);};
Instruction: tPri tEntier       		{ajouterIns(asm_pri,$2);};
Instruction: tCpi tEntier tEntier		{ajouterIns(asm_cpi,$2,$3);};
Instruction: tIcp tEntier tEntier		{ajouterIns(asm_icp,$2,$3);};
Instruction: tOr tEntier tEntier tEntier 	{ajouterIns(asm_or,$2,$3,$4);};
Instruction: tAnd tEntier tEntier tEntier 	{ajouterIns(asm_and,$2,$3,$4);};
Instruction: tPop tEbp {ajouterIns(asm_pop);};
Instruction: tPush tEbp {ajouterIns(asm_pushEBP);};
Instruction: tPush tEntier {ajouterIns(asm_pushVar, $2);};
Instruction: tMov tEbp tEsp {ajouterIns(asm_movEBPESP);};
Instruction: tMov tEsp tEbp {ajouterIns(asm_movESPEBP);};
Instruction: tRet tEntier {ajouterIns(asm_ret, $2);};
Instruction: tCall tEntier {ajouterIns(asm_call,$2);};
Instruction: tEsp tEntier {ajouterIns(asm_incEsp,$2);};
Instruction: tErt tEntier {ajouterIns(asm_ert,$2);};

%%
int main (int argc, char ** argv) {
  if (argc > 1) {
  	initInterpreteur(1);
  } else {
  	initInterpreteur(0);
  }
	yyparse();
	execute();
}
