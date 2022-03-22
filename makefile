main: main.o fileprocess.o lineprocess.o symbollist.o instructionsregister.o dataregister.o symbol.o output.o
	gcc -g -ansi  -Wall main.o fileprocess.o lineprocess.o symbollist.o instructionsregister.o dataregister.o symbol.o output.o -o main
fileprocess.o: fileprocess.c fileprocess.h lineprocess.h
	gcc -c -ansi -pedantic -Wall fileprocess.c -o fileprocess.o
lineprocess.o: lineprocess.c lineprocess.h symbollist.h
	gcc -c -ansi -pedantic -Wall lineprocess.c -o lineprocess.o
symbollist.o: symbollist.c symbollist.h
	gcc -c -ansi -pedantic -Wall symbollist.c -o symbollist.o
instructionsregister.o: instructionsregister.c instructionsregister.h output.h
	gcc -c -ansi -pedantic -Wall instructionsregister.c -o instructionsregister.o
dataregister.o: dataregister.c output.h
	gcc -c -ansi -pedantic -Wall dataregister.c -o dataregister.o
symbol.o: symbol.c symbol.h symbollist.h instructionsregister.h dataregister.h
	gcc -c -ansi -pedantic -Wall symbol.c -o symbol.o
output.o: output.c
	gcc -c -ansi -pedantic -Wall output.c -o output.o
main.o: main.c fileprocess.h
	gcc -c -ansi -pedantic -Wall main.c -o main.o
