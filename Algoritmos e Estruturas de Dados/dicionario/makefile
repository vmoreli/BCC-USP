all: verbete.o skiplist.o main.o
	gcc verbete.o skiplist.o main.o -o dicionario -Wall -std=c99
verbete.o:
	gcc -c verbete.c -o verbete.o
skiplist.o:
	gcc -c skiplist.c -o skiplist.o
main.o:
	gcc -c main.c -o main.o
run:
	./dicionario
clean:
	rm *.o dicionario