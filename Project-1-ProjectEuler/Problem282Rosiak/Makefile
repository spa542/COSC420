main: main.o stack.o BigIntegerSingleFile.o
	./mpipp -o main main.o stack.o BigIntegerSingleFile.o -g -lm
main.o: main.c stack.h
	mpicc -c main.c -g
BigIntegerSingleFile.o: BigIntegerSingleFile.cpp
	g++ -c BigIntegerSingleFile.cpp -g
stack.o: stack.c stack.h
	mpicc -c stack.c -g
clean:
	rm -f *.o main
