main : main.o fonc.o display.o
	gcc -o main main.o fonc.o
	gcc -o display display.o fonc.o -lSDL2 -lSDL2_ttf

main.o : main.c
	gcc -g -Wall -c main.c 

fonc.o : fonc.c
	gcc -g -Wall -c fonc.c
display.o : display.c
	gcc -g -Wall -c display.c 

clean :
	rm main *.o
