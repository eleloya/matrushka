cc lex.yy.c y.tab.c -o matrushka
yacc -d --verbose grammar.y
lex syntax.l
