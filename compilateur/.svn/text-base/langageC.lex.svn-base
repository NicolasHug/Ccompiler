%{
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

%}
%option yylineno
%x com
%%

int 					 return  tInt;
const 					 return  tConst;
for 					 return  tFor;
while 					 return  tWhile;
if 					 return  tIf;
else 					 return  tElse;
return          return tReturn;
void        return tVoid;
[\t \n]* 			       	{}
printf 					 return  tPrintf;
[a-zA-Z][a-zA-Z0-9_]*			 {yylval.string = strdup(yytext); return  tNom;};
[0-9]+([Ee][+-]?[0-9]+)? 		 {yylval.integer = atoi(yytext); return  tEntier;};
"(" 					 return  tPrt_Ouv;
")" 					 return  tPrt_Ferm;
"{" 					 return  tAcc_Ouv;
"}" 					 return  tAcc_Ferm;
"++"					 return	 tPlusPlus;
"--"					 return	 tMoinsMoins;
"+" 					 return  tPlus;
"-" 					 return  tMoins;
"*" 					 return  tFois;
"/" 					 return  tDiv;
"=="                                     return tEgalEgal;
"&"                                      return tEt;
"|"           return tOu;
"=" 					 return  tEgal;
"<="          return tInfEgal;
">="          return tSupEgal;
"<"                                      return tInf;
">"                                      return tSup;
";" 					 return  tPt_Virgule;
"," 					 return  tVirgule;
"["                                      return tCroch_Ouv;
"]"                                      return tCroch_Ferm;
"//"[^\n]*$				{}
%[^%]*%           {}
"/""*"    {BEGIN com;}
<com>[^*]* {}
<com>"*"+[^*/\n]* {}
<com>"*""/" {BEGIN INITIAL;}  
