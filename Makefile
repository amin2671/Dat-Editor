assign7.o: assign7.c
	gcc -g -c assign7.c -o assign7.o

assign7: assign7.o
	gcc -g -o assign7 assign7.o

clean:
	rm -f assign7.o
