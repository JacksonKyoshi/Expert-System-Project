main : main.o fonc.o display.c
	gcc -o main main.o fonc.o
	gcc -o display display.c -lSDL2 -lSDL2_ttf

main.o : main.c
	gcc -g -Wall -c main.c 

fonc.o : fonc.c
	gcc -g -Wall -c fonc.c 

clean :
	rm main *.o
