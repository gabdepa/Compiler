$DEPURA=1
CFLAGS = -lfl -L /usr/lib/x86_64-linux-gnu -ly -lc -g
DEBUG_FLAGS =-DDEBUG

compilador: lex.yy.c compilador.tab.c compilador.o tabela_simb.o pilha_rotulos.o pilha_tipos.o
	gcc lex.yy.c compilador.tab.c compilador.o tabela_simb.o pilha_rotulos.o pilha_tipos.o -o compilador $(CFLAGS)

lex.yy.c: compilador.l compilador.h
	flex compilador.l

compilador.tab.c: compilador.y compilador.h
	bison compilador.y -d -v

tabela_simb.o: utils/tabela_simb.c utils/tabela_simb.h
	gcc -c utils/tabela_simb.c -o tabela_simb.o $(CFLAGS)

pilha_rotulos.o: utils/pilha_rotulos.c utils/pilha_rotulos.h
	gcc -c utils/pilha_rotulos.c -o pilha_rotulos.o $(CFLAGS)

pilha_tipos.o: utils/pilha_tipos.c utils/pilha_tipos.h
	gcc -c utils/pilha_tipos.c -o pilha_tipos.o $(CFLAGS)

compilador.o : compilador.h compiladorF.c
	gcc -c compiladorF.c -o compilador.o $(CFLAGS)

debug : CFLAGS += $(DEBUG_FLAGS)
debug : compilador

clean :
	rm -f compilador.tab.* lex.yy.c *.o compilador

purge: clean
