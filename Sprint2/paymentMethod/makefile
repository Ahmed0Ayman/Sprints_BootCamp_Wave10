
all:	clean auto



test: main server Utilites Terminal

main:
	gcc -c main.c -o  main.o

server:
	gcc -c Server.c -o server.o

Utilites:
	gcc -c Utilites.c -o  Utilites.o

Terminal:
	gcc -c Terminal.c -o Terminal.o



auto:
	gcc -g -std=c99  *.c -lws2_32 -o auto

clean:
	rm -rf *.o *.exe