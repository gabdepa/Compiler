$DEPURA=1

compilador: lex.yy.c compilador.tab.c compilador.o ./utilsH/compilador.h
	gcc lex.yy.c compilador.tab.c compilador.o -o compilador -lfl -ly -lc

lex.yy.c: compilador.l ./utilsH/compilador.h
	flex compilador.l

compilador.tab.c: compilador.y ./utilsH/compilador.h
	bison compilador.y -d -v

compilador.o: ./utilsH/compilador.h ./utilsC/compiladorF.c
	gcc -c ./utilsC/compiladorF.c -o compilador.o

clean:
	rm -f compilador.tab.* lex.yy.c compilador.o compilador

purge: clean
	
