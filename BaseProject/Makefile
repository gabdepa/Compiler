 # -------------------------------------------------------------------
 #            Arquivo: Makefile
 # -------------------------------------------------------------------
 #              Autor: Bruno Müller Junior
 #               Data: 08/2007
 #      Atualizado em: [09/08/2020, 19h:01m]
 #
 # -------------------------------------------------------------------

$DEPURA=1
CFLAGS = -Wall -lfl -L /usr/lib/x86_64-linux-gnu -ly -lc -g
DEBUG_FLAGS =-DDEBUG

compilador: lex.yy.c compilador.tab.c compilador.o tabela_simb.o simbolo.o pilha_int.o pilha_simb_ptr.o
	gcc lex.yy.c compilador.tab.c compilador.o tabela_simb.o simbolo.o pilha_int.o pilha_simb_ptr.o -o compilador $(CFLAGS)

lex.yy.c: compilador.l compilador.h
	flex compilador.l

compilador.tab.c: compilador.y compilador.h
	bison compilador.y -d -v

tabela_simb.o: utils/tabela_simb/tabela_simb.c utils/tabela_simb/tabela_simb.h
	gcc -c utils/tabela_simb/tabela_simb.c -o tabela_simb.o $(CFLAGS)

simbolo.o: utils/tabela_simb/simbolo.c utils/tabela_simb/simbolo.h
	gcc -c utils/tabela_simb/simbolo.c -o simbolo.o $(CFLAGS)

pilha_int.o: utils/pilha/pilha_int.c utils/pilha/pilha_int.h
	gcc -c utils/pilha/pilha_int.c -o pilha_int.o $(CFLAGS)

pilha_simb_ptr.o: utils/pilha/pilha_simb_ptr.c utils/pilha/pilha_simb_ptr.h
	gcc -c utils/pilha/pilha_simb_ptr.c -o pilha_simb_ptr.o $(CFLAGS)

compilador.o : compilador.h compiladorF.c
	gcc -c compiladorF.c -o compilador.o $(CFLAGS)

debug : CFLAGS += $(DEBUG_FLAGS)
debug : compilador

clean :
	rm -f compilador.tab.* lex.yy.c *.o compilador
