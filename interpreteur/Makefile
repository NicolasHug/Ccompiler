all: interpreteur

interpreteur: langageASM.lex langageASM.y assembleur.o
	yacc -d -v langageASM.y
	lex langageASM.lex
	gcc assembleur.o y.tab.c lex.yy.c -lfl -ly -o interpreteur

assembleur.o: assembleur.h assembleur.c
	gcc -c assembleur.c
clean:
	rm -f *.o asm y.tab.h y.tab.c y.output lex.yy.c interpreteur
