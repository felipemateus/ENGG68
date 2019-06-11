all: servidor cliente1 cliente2 cliente3 cliente4

servidor: servidor.c
	gcc servidor.c -o servidor

cliente1: cliente1.c
	gcc cliente1.c -lpthread -o cliente1

cliente2: cliente2.c
	gcc cliente2.c -lpthread -o cliente2

cliente3: cliente3.c
	gcc cliente3.c -lpthread -o cliente3

cliente4: cliente4.c
	gcc cliente4.c -lpthread -o cliente4


clean:
	rm -rf *.o