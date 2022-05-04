myShell : myShell.o setOne.o rshFunctions.h setTwo.o
	gcc -std=gnu99 -Wpedantic -o myShell myShell.o setOne.o setTwo.o
myShell.o : myShell.c setOne.c rshFunctions.h setTwo.c
	gcc  -std=gnu99 -Wpedantic -c myShell.c setOne.c setTwo.c

clean : 
	rm *.o myShell