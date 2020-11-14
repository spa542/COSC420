writematrix: writematrix.o citetree.o
	gcc writematrix.o citetree.o -o writematrix -g
writematrix.o: writematrix.c citetree.h
	gcc -c writematrix.c -g
citetree.o: citetree.h citetree.c
	gcc -c citetree.c -g
clean:
	rm -f *.o writematrix
