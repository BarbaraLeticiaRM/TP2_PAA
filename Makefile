all: funcoes.o algoritmos.o main.c
	gcc -o main main.c funcoes.o algoritmos.o

funcoes.o: funcoes.c
	gcc -o funcoes.o -c funcoes.c

algoritmos.o: algoritmos.c
	gcc -o algoritmos.o -c algoritmos.c
	
clean:
	rm -f *.o main
		
run:
	./main
