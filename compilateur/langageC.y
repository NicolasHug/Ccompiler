%{
#include <stdio.h>
#include "compilateur.h"
#include "exprArithmetiques.h"

void yyerror(char *s);
char messageErreur[100];
int erreurExiste = 0;
extern int yylineno;
%}

%union {
	int integer;
	char * string;
}

%token tInt tConst tMain tFor tWhile tIf tElse  tPrintf tNom tEntier tPrt_Ouv tPrt_Ferm tAcc_Ouv tAcc_Ferm tPlus tMoins tFois tDiv tEgal tEOL tPt_Virgule tVirgule tInf tSup tEgalEgal tEt tCroch_Ouv tCroch_Ferm tInfEgal tSupEgal tOu tPlusPlus tMoinsMoins tReturn tVoid
%start ProgrammeC


%left tEt tOu
%left tEgalEgal tSup tInf tSupEgal tInfEgal
%left tPlus tMoins
%left tFois tDiv

%type<string> tNom
%type<string> Argument
%type<integer> tEntier
%type<integer> Expr_Arithmetique 
%type<integer> Pargs PassageArguments

%error-verbose

%%

ProgrammeC : Fonctions;

Fonctions : Fonction Fonctions;
Fonctions : Fonction;

Fonction : Type tNom {debutFonction($2,1);} tPrt_Ouv Arguments tPrt_Ferm tAcc_Ouv Corps tAcc_Ferm {finFonction();};
Fonction : tVoid tNom {debutFonction($2,0);} tPrt_Ouv Arguments tPrt_Ferm tAcc_Ouv Corps tAcc_Ferm {finFonction();};
Fonction : error;

Type : tInt;
Type : tConst tInt;

Arguments : ;
Arguments : Args;
Args : Argument tVirgule Args;
Args : Argument;
Argument : tInt tNom {definirArg(INT,$2);};
Argument : tInt tFois tNom{definirArg(PT,$3);};
Argument : tInt tConst tNom {definirArg(CONST,$3);};

Corps : Declarations  Instructions | error;


/* DECLARATIONS */
Declarations : ;
/* Declaration entier */
Declarations : tInt  tNom  tPt_Virgule {ajouterSymbole($2,INT,0,0);} Declarations;

/* Declaration entier + affectation */
Declarations : tInt  tNom  {ajouterSymbole($2,INT,1,0);} tEgal Expr_Arithmetique  
               tPt_Virgule  { fprintf_cop(getAdresse($2), $5); cleanTable();} Declarations ; 

/* Declaration constante + affectation */
Declarations : tConst tInt tNom {ajouterSymbole($3,CONST,1,0);} tEgal Expr_Arithmetique 
               tPt_Virgule {fprintf_cop(getAdresse($3), $6); cleanTable();} Declarations;

/* Declaration pointeur */
Declarations : tInt tFois tNom tPt_Virgule {ajouterSymbole($3,PT,0,0);} Declarations;

/* Declaration pointeur + affectation */
Declarations : tInt tFois tNom {ajouterSymbole($3,PT,1,0);} tEgal Expr_Arithmetique 
               tPt_Virgule {fprintf_cop(getAdresse($3) , $6);  }Declarations;

/* Declaration tableau */
Declarations : tInt tNom tCroch_Ouv tEntier tCroch_Ferm 
               {ajouterPlusieursSymboles($2,PT,$4); fprintf_afc(getAdresse($2), getNombreVariablesLocales() - $4);} 
               tPt_Virgule Declarations;
//Declarations : error Declarations;


/* EXPRESSIONS ARITHMETIQUES */
Expr_Arithmetique : tEntier                                           {$$ = exprEntier($1);}
Expr_Arithmetique : tNom                                              {$$ = exprNom($1); };
/* Operateur + */
Expr_Arithmetique : Expr_Arithmetique tPlus Expr_Arithmetique 				{$$ = exprPlus($1,$3);}; 
/* Operateur - (soustraction) */
Expr_Arithmetique : Expr_Arithmetique tMoins Expr_Arithmetique 				{$$ = exprMoins($1,$3);};
/* Operateur - (opposé) */
Expr_Arithmetique : tMoins Expr_Arithmetique 						              {$$ = exprOppose($2);};
/* Operateur * */
Expr_Arithmetique : Expr_Arithmetique tFois Expr_Arithmetique 				{$$ = exprFois($1,$3);};
/* Operateur / */
Expr_Arithmetique : Expr_Arithmetique tDiv Expr_Arithmetique 			  	{$$ = exprDiv ($1,$3);};
/* Operateur == */
Expr_Arithmetique : Expr_Arithmetique tEgalEgal Expr_Arithmetique 		{$$ = exprEqu($1,$3);};
/* Operateur < */
Expr_Arithmetique : Expr_Arithmetique tInf Expr_Arithmetique 		  		{$$ = exprInf ($1,$3);}; 
/* Operateur <= */
Expr_Arithmetique : Expr_Arithmetique tInfEgal Expr_Arithmetique 			{$$ = exprInfEgal($1,$3);}; 
/* Operateur > */
Expr_Arithmetique : Expr_Arithmetique tSup Expr_Arithmetique 			  	{$$ = exprSup ($1,$3);};
/* Operateur >= */
Expr_Arithmetique : Expr_Arithmetique tSupEgal Expr_Arithmetique 			{$$ = exprSupEgal ($1,$3);};
/* Operateur ||  */
Expr_Arithmetique : Expr_Arithmetique tOu tOu Expr_Arithmetique 			{$$ = exprOu ($1,$4);}; 
/* Operateur * (pointeur) */
Expr_Arithmetique : tFois Expr_Arithmetique 					              	{$$ = exprAcces($2);}; 
/* Operateur & */
Expr_Arithmetique : tEt tNom                           								{$$ = exprAdresse($2); cleanTable();};
/* Operateur [] */
Expr_Arithmetique : tNom tCroch_Ouv Expr_Arithmetique tCroch_Ferm 		{$$ = exprCrochet($1,$3);}; 
/* Appel de fonction */
Expr_Arithmetique : tNom {debutAppel($1);} tPrt_Ouv PassageArguments tPrt_Ferm 		{$$ = exprAppel($1,$4);};

Expr_Arithmetique : tPrt_Ouv Expr_Arithmetique tPrt_Ferm 				      {$$ = $2;};


/* INSTRUCTIONS */
Instructions : ;
/* Affectation */
Instructions : Affectation tPt_Virgule Instructions;
/* Printf */
Instructions : tPrintf tPrt_Ouv Expr_Arithmetique tPrt_Ferm tPt_Virgule {fprintf_pri($3); cleanTable();} Instructions ;
/* Bloc if */
Instructions : Structure_If Instructions;
/* Bloc for */
Instructions : Boucle_For Instructions;
/* Bloc while */
Instructions : Boucle_While Instructions;
/* Appel de fonction */
Instructions : Appel tPt_Virgule Instructions;
/* Retour */
Instructions : tReturn Expr_Arithmetique tPt_Virgule {retour($2);} Instructions;
//Instructions : error Instructions;


/* STRUCTURE IF */
Structure_If : tIf tPrt_Ouv Expr_Arithmetique tPrt_Ferm 
               tAcc_Ouv {debutIf(); fprintf_jmf($3);} Instructions 
               tAcc_Ferm {finIf(); fprintf_jmp();};
Structure_If : Structure_If {debutElse();}Structure_Else {finElse();};

Structure_Else : tElse tAcc_Ouv Instructions tAcc_Ferm;


/* STRUCTURE WHILE */
Boucle_While : tWhile tPrt_Ouv {condWhile();} 
               Expr_Arithmetique {debutWhile(); fprintf_jmf($4);} tPrt_Ferm 
	             tAcc_Ouv  Instructions tAcc_Ferm {finWhile(); fprintf_jmp();};

/* STRUCTURE FOR */
Boucle_For : tFor tPrt_Ouv Affectation tPt_Virgule {condFor();} 
             Expr_Arithmetique {fprintf_jmf($6); fprintf_jmp(); debutFor();} tPt_Virgule 
		         Affectation {fprintf_jmp(); milieuFor();} tPrt_Ferm 
	           tAcc_Ouv Instructions {finFor(); fprintf_jmp();} tAcc_Ferm ;


/* AFFECTATIONS */
/* Affectation classique (int) */
Affectation : tNom tEgal Expr_Arithmetique {checkAffectation($1); fprintf_cop(getAdresse($1),$3); setInitialise($1); cleanTable();};

/* Affectation indirecte (opérateur *) */
Affectation : tFois Expr_Arithmetique tEgal Expr_Arithmetique {fprintf_icp($2,$4); cleanTable();};

/* Affectation indirecte (opérateur []) */
Affectation : tNom tCroch_Ouv Expr_Arithmetique tCroch_Ferm tEgal Expr_Arithmetique 
              {checkAffectationInd($1); ajouterSymbole(NULL,TEMP,1,0); fprintf_add(getNombreVariablesLocales() - 1, getAdresse($1),$3); 
              fprintf_icp(getNombreVariablesLocales() - 1, $6); cleanTable();};

/* Affectation ++ */
Affectation : tNom tPlusPlus {checkAffectation($1); ajouterSymbole(NULL,TEMP,1,0); fprintf_afc(getNombreVariablesLocales() - 1, 1); 
              fprintf_add(getAdresse($1), getAdresse($1), getNombreVariablesLocales() - 1); cleanTable();};

/* Affectation -- */
Affectation : tNom tMoinsMoins {checkAffectation($1); ajouterSymbole(NULL,TEMP,1,0); fprintf_afc(getNombreVariablesLocales() - 1, 1); 
              fprintf_sou(getAdresse($1), getAdresse($1), getNombreVariablesLocales() - 1); cleanTable();};

/* Appel de fonction (valeur de retour négligée)*/
Appel : tNom {debutAppel($1);} tPrt_Ouv PassageArguments tPrt_Ferm {appel($1,$4);};

PassageArguments : {$$ = 0;};
PassageArguments : Pargs;
Pargs : tNom {pushParam($1);} tVirgule Pargs {$$=$4+1;};
Pargs : tNom {pushParam($1); $$=1;};


%%

void yyerror(char *s) {
  fprintf(stderr, "ERREUR : %s (line %d)\n", s, yylineno); 
}

int main () {
  initCompilateur();
	yyparse();
  if (!erreurExiste) {
    secondePasse();
  }
  return 0;
}
