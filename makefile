myset: set.o manageInput.o myset.o
	gcc -Wall -ansi -pedantic myset.o manageInput.o set.o -o myset
myset.o: myset.c set.h
	gcc -c -Wall -ansi -pedantic myset.c -o myset.o
manageInput.o: manageInput.c set.h
	gcc -c -Wall -ansi -pedantic manageInput.c -o manageInput.o
set.o: set.c set.h
	gcc -c -Wall -ansi -pedantic set.c -o set.o
