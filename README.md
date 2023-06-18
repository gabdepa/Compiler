# Compiler

Created a Pascal compiler

- The **`.l`** file is the file that will generate the tokens of identification for the semantic/syntactic analyzer to process. 

- The **`.y`** is the descirbed semantic/syntactic analyzer as mentioned above, where it gets a token and interpret them based on the rules defined by the compiler.


## Regras 
Baseando o compilador nas regras contidas no livro Implementação de Linguagens de Programação de Tomasz Kowaltowski, disponível em: 
https://www.ic.unicamp.br/~tomasz/ilp/ilp.pdf

E nas Aulas da matéria CI1211 - Construção de Compiladores 
Aula 5 : Variáveis e MEPA
 - Implemente um Tipo Abstrato de Dados “Tabela de Símbolos”
Arquivo symbols_table
    Funções básicas:
        __Insere (ident, atributos)__ Insere o identificador indicado na TS,
        assim como seus atributos;
        __Busca(ident)__ Retorna a entrada (os atributos) da TS
        associados ao ident procurado.
        __Retira(n)__ Retira as últimas n entradas da TS.
    - Ela deve funcionar como uma pilha na inserção e na remoção.

aula 6 - (Regras para declarações de variáveis 2,8,9,10)
    Capaz de traduzir programa inicial em pascal com declaração de variáveis, gerando o código MEPA referente

Desafios:

    não for um símbolo ∈ Variável Simples, Parâmetro formal ou Função, deve indicar erro
    Como armazenar o elemento da esquerda para fazer a comparação com o resultado da expressão. Sugestão: variável global l_elem.

aula 7 - expressoes, verificar tipos

    AMEN k
    regras 25 a 29
    CRVL

exp. booleanas (regras 25 e 26)

    testar expressao_simples
        DIVI, SOMA

    testar relacao
        CMIG, CMMA, CMME, CMDG, etc
        CONJ (and)

    ser capaz de detectar erros varGlobaisInvalido.pas

    ser capaz de detectar erros erroTipo.pas

    regra 30

Dica: a regra 30 é a única que acessa a tabela de símbolos. Nas demais, usa-se as construções (como pilha ou $$).
aula 8 e 9

    LEIT

    IMPR

    BUG: aula8 nao escreve variavel k na tabela

    while

    if

    subrotina geradora do proximo rotulo

    pilha de rotulos (padrao Rdd)

    while aninhados, nao confundir rotulos

aula 10

    procedimentos

    funcoes

Flex

    compilador.l - definicoes, regras, subrotinas
    compilador.h - header do lex.yy.c

flex compilador.l gera:

    lex.yy.c - Analisador Lexico gerado (AFD)

Bison

    compilador.y - definicoes, regras, subrotinas

bison compilador.y -d -v gera:

    compilador.tab.c - automato finito a pilha
    compilador.tab.h - header do lex.yy.c
    compilador.output - automato legivel

    compilar o lex.yy.c e compilador.tab.c juntos para gerar o executavel final








