main : main.o fonc.o
	gcc -o main main.o fonc.o

main.o : main.c
	gcc -g -Wall -c main.c 

fonc.o : fonc.c
	gcc -g -Wall -c fonc.c 

clean :
	rm main *.o
