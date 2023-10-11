all: item.o pilha.o main.o
	gcc item.o fila.o main.o -g -o pilha -std=c99 -Wall

item.o:
	gcc -c item.c -o item.o

pilha.o:
	gcc -c pilha.c -o fila.o
	 
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o pilha

run:
	./pilha