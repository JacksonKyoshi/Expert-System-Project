main : main.o fonc.o
	gcc -o main main.o fonc.o

main.o : main.c
	gcc -g -Wall -c main.c 

fonc.o : fonc.c
	gcc -g -Wall -c fonc.c 

display : display.c
	gcc -o display display.c -lSDL2 -lSDL2_ttf

clean :
	rm main *.o
