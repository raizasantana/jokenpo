/*
	Servidor
*/

#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

int main(int argc , char *argv[])
{
	int socket_desc , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[2000];

	//Criando socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		perror("Falha ao criar o socket.\n\n");
	}
		printf("Socket criado.\n\n");

	//Preparando a struct
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );

	//Vinculando
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("bind failed. Error\n\n");
		return 1;
	}

	printf("Vinculado.\n\n");

	//Ouvindo
	listen(socket_desc , 3);


	//Aceitando e recebendo conexoes
	puts("Esperando por conexoes...\n");

	c = sizeof(struct sockaddr_in);

	//Aceitando conexao de um cliente
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0)
	{
	perror("accept failed");
	return 1;
	}
	puts("Connection accepted\n\n");

	//Receive a message from client
	while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
	{
	//Send the message back to client
	write(client_sock , client_message , strlen(client_message));
	}
	
	if(read_size == 0)
	{	
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}
	

	

	return 0;
}
