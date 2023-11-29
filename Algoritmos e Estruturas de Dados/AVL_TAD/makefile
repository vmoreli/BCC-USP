all: item.o avl.o main.o
	gcc item.o avl.o main.o -o avl -std=c99 -Wall

item.o:
	gcc -c item.c -o item.o

avl.o:
	gcc -c avl.c -o avl.o
	 
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o avl

run:
	./avl
