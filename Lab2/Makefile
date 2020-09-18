main: main.o matrix.o
	mpicc -o main main.o matrix.o -g
main.o: main.c matrix.h
	mpicc -c main.c -g
matrix.o: matrix.c matrix.h
	mpicc -c matrix.c -g -lm
clean:
	rm -f *.o main
