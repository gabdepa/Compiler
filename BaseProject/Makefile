$DEPURA=1

compilador: lex.yy.c compilador.tab.c compilador.o symbols_table.o stack.o
	gcc lex.yy.c compilador.tab.c compilador.o symbols_table.o stack.o -o compilador -lfl -L /usr/lib/x86_64-linux-gnu -ly -lc -g

compilador.o: utilsH/compilador.h utilsC/compiladorF.c
	gcc -c utilsC/compiladorF.c -o compilador.o

lex.yy.c: compilador.l ./utilsH/compilador.h
	flex compilador.l

compilador.tab.c: compilador.y utilsH/compilador.h
	bison compilador.y -d -v

symbols_table.o: utilsC/symbols_table.c utilsH/symbols_table.h
	gcc -c utilsC/symbols_table.c -o symbols_table.o

stack.o: utilsC/stack.c utilsH/stack.h
	gcc -c utilsC/stack.c -o stack.o

clean:
	rm -f compilador.tab.* lex.yy.c compilador.o compilador symbols_table.o stack.o

purge: clean
	
