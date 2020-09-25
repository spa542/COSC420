main: main.o stack.o
	mpicc -o main main.o stack.o -g -lm
main.o: main.c stack.c
	mpicc -c main.c -g
stack.o: stack.c stack.h
	mpicc -c stack.c -g
clean:
	rm -f *.o main
