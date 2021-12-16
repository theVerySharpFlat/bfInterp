
all: main.o
	clang main.o -o bfi

main.o: main.c
	clang -c main.c -o main.o