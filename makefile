all: 	
		clear
		gcc -pthread -o server servidor2.c
		gcc -o clienteativo cliente2.c
		gcc -o clientepassivo cliente1.c
		./server


