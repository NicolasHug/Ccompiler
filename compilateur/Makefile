default: all
all: compilo

compilo : langageC.lex langageC.y tableDesSymboles.o exprArithmetiques.o fonctions.o utilitaires.o compilateur.o
	yacc -d -v langageC.y
	lex langageC.lex
	gcc tableDesSymboles.o exprArithmetiques.o fonctions.o utilitaires.o compilateur.o lex.yy.c y.tab.c -lfl -ly -o compilo

tableDesSymboles.o : tableDesSymboles.c tableDesSymboles.h
	gcc -c -Wall tableDesSymboles.c

exprArithmetiques.o : exprArithmetiques.c exprArithmetiques.h
	gcc -c -Wall exprArithmetiques.c

fonctions.o : fonctions.c fonctions.h
	gcc -c -Wall fonctions.c

utilitaires.o : utilitaires.c utilitaires.h
	gcc -c -Wall utilitaires.c

compilateur.o : compilateur.c compilateur.h
	gcc -c -Wall compilateur.c
clean:
	rm -f *.o asm asmPremierePasse y.output lex.yy.c y.tab.c y.tab.h compilo
