%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

add	return tAdd;
mul	return tMul;
sou	return tSou;
div	return tDiv;
cop	return tCop;
afc	return tAfc;
jmp	return tJmp;
jmf	return tJmf;
inf	return tInf;
sup	return tSup;
equ	return tEqu;
pri	return tPri;
cpi	return tCpi;
icp	return tIcp;
or_ return tOr;
and return tAnd;
psh return tPush;
pop return tPop;
ret return tRet;
cal return tCall;
esp return tEsp;
ebp return tEbp;
mov return tMov;
ert return tErt;


-?[0-9]+([Ee][+-]?[0-9]+)? {yylval = atoi(yytext); return  tEntier;};
[\t \n] {}
