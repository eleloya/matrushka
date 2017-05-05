# "make install" compiles the code and moves the executables to this folder
# "make test" run the tests files on our matrushka 

install:
	lex src/lex.l
	mv lex.yy.c src/
	yacc src/yacc.y
	mv y.tab.c src/
	gcc src/main.c -o mcc
	cp src/mvm.py ./mvm.py
	
test:
	./mcc tests/debitcard.mka debitcard.bab
	./mcc tests/functions.mka functions.bab
	./mcc tests/factorial.mka factorial.bab
	./mcc tests/fibonnaci.mka fibonnaci.bab
	./mcc tests/maximo_vector.mka maximo_vector.bab
	./mcc tests/arreglos_multi.mka arreglos_multi.bab
	
clean:
	rm -f *.bab &> /dev/null
	rm -f *.out &> /dev/null
	rm -f mvm.py &> /dev/null
	rm -f mcc &> /dev/null