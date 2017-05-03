#!/bin/bash
lex lex.l
yacc yacc.y
gcc main.c -o example
./example tests/sample2.mka tests/sample2.bab