# Makefile HT.c - Tekijä: Juhani Manninen - Pvm: 1.3.2022
HT: HTPerustaso.o HTPerusKirjasto.o
	gcc HTPerustaso.o HTPerusKirjasto.o -o HT
HTPerustaso.o: HTPerustaso.c HTPerusKirjasto.h
	gcc HTPerustaso.c -c -std=c99 -pedantic -Wall
HTPerusKirjasto.o: HTPerusKirjasto.c HTPerusKirjasto.h
	gcc HTPerusKirjasto.c -c -std=c99 -pedantic -Wall
          
