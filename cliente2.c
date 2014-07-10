/*
	Cliente Ativo
*/
#include<stdio.h> 
#include<string.h> 
#include <stdlib.h>   
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr

int criar_sock()
{
	int sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		perror("Não foi possível criar o socket.");
		exit (EXIT_FAILURE);	
	}

	return sock;	
}

struct sockaddr_in criar_server()
{
	struct sockaddr_in server;
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );
}


void conectar_servidor(int sock, struct sockaddr_in server)
{
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("Erro de conexão.");
		exit (EXIT_FAILURE);	
	}

		puts("Cliente conectado.\n");
}

void enviar_mensagem(char *msg, int sock)
{
	if( send(sock , msg , strlen(msg) , 0) < 0)
	{
		perror("Mensagen não enviada.");
		exit (EXIT_FAILURE);
	}
}

int main(int argc , char *argv[])
{
	int sock = criar_sock();
	struct sockaddr_in server = criar_server();	

	char nickname[10] = "\0";


	conectar_servidor(sock, server);
	
	printf("\n\nInforme seu nick: (10 CARACTERES) ");
	scanf("%s" , nickname);

	
	/*Continuar a cominucacao com o servidor
	while(1)
	{
		printf("Enter message : ");
		scanf("%s" , message);
	
		 
		//Enviar dados
		if( send(sock , message , strlen(message) , 0) < 0)
		{
		    puts("Send failed");
		    return 1;
		}
	   	    
		//Receber resposta do servidor
		if( recv(sock , server_reply , 10 , 0) < 0)
		{
		    puts("recv failed");
		    break;
		}
		 
		puts("\nServer reply :");
		printf("%s\n\n",server_reply);

		//message[10] = "\0";

	}*/

	close(sock);
	return 0;
}
