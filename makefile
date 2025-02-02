corbuStephanieA1: corbuStephanieA1.o corbuStephanieA1Main.o
	gcc corbuStephanieA1.o corbuStephanieA1Main.c -lm -o corbuStephanieA1
corbuStephanieA1.o: corbuStephanieA1.c
	gcc -Wall -std=c99 -c corbuStephanieA1.c
corbuStephanieA1Main.o: corbuStephanieA1Main.c
	gcc -Wall -std=c99 -c corbuStephanieA1Main.c
clean:
	rm *.o corbuStephanieA1
