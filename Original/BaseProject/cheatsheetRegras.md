1. <programa> ::=
program <identificador> (<lista de identificadores>);      
    <bloco>.
2. <bloco> ::=
    [<parte de declarações de rótulos>] 
    [<parte de definições de tipos>]
    [<parte de declarações de variáveis>]
    [<parte de declarações de sub-rotinas>] 
    <comando composto>

3. <parte de declarações de rótulos> ::=
    label <número> {, <número>}; 

4. <parte de definições de tipos> ::=
    type <definição de tipo> {; <definição de tipo>};

5. <definição de tipo> ::=
    <identificador> = <tipo>

6. <tipo> ::=
    <identificador>|
    array [<índice> {, <índice>}] of <tipo>

7. <índice> ::= <número>.. <número>

8. <parte de declarações de variáveis> ::= 
    var <declaração de variáveis>
        {; <declaração de variáveis>};

9. <declaração de variáveis> ::=
    <lista de identificadores> : <tipo>

10. <lista de identificadores> ::=
    <identificador> {, <identificador>} 

11. <parte de declarações de sub-rotinas> ::=
    {<declaração de procedimento>; |
    <declaração de função> ;}

12. <declaração de procedimento> ::=
    procedure <identificador>
        [<parâmetros formais>]: <bloco>

13. <declaração de função> ::=
    function <identificador>
        [<parâmetros formais>]: <identificador> ;
         <bloco>

14. <parâmetros formais> ::=
    (<seção de parâmetros formais> 
    {: <seção de parâmetros formais>})

15. <seção de parâmetros formais> ::=
    [var] <lista de identificadores>:<identificador>
   | function <lista de identificadores>:<identificador
   | procedure <lista de identificadores>

16. <comando composto> ::=
    begin <comando>{;<comando>} end 

17. <comando> ::=
    [<número>:]<comando sem rótulo>

18. <comando sem rótulo> ::=
    <atribuição>
    |<chamada de procedimento>
    |<desvio>
    |<comando composto>
    |<comando condicional>
    |<comando repetitivo>

19. <atribuição> ::=
    <variável>:= <expressão>

20. <chamada de procedimento> ::= 
    <identificador> [(<lista de expressões>)]

21. <desvios> ::= goto <número>

22. <comando condicional> ::=
    if <expressão> then <comando sem rótulo>
        [else <comando sem rótulo>]

23. <comando repetitivo> ::=
    while <expressão> do <comando sem rótulo>

24. <lista de expressões> ::= 
    <expressão> {, <expressão>}

25. <expressão> ::=
    <expressão simples>[<relação><expressão simples>]

26. <relação> ::= =|<>|<|<=|>=|>

27. <expressão simples> ::=
    [+|-] <termo>{(+|-|or) <termo>}

28. <termo> ::=
    <fator> {(*|div|and) <fator>}

29. <fator>::=
    <variável>
    |<número>
    |<chamada de função>
    |(<expressão>)
    |not <fator>

30. <variável> ::=
    <identificador>
    |<identificador> [<lista de expressões>]

31. <chamada de função> ::=
    <identificador> [(<lista de expressões>)]

32. <número> ::=
    <dígito>{<dígito>}



/// regras que nao fizemos : desnecessarias ?
33. <dígito> ::=
    0|1|2|3|4|5|6|7|8|9

34. <identificador> ::= 
    <letra> { <letra> | <dígito>}

35. <letra> ::=
    a| b| c| d| e| f| g| h|i|j | k|l | m| 
    n| o|p| q| r| s| t| u| v| w| x| y| z