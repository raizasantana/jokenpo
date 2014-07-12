#include <stdio.h>
#include <stdlib.h>
#include<string.h> 
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr


#define RODADAS 3

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

void  config_server(struct sockaddr_in *server)
{	
	server->sin_addr.s_addr = inet_addr("127.0.0.1");
	server->sin_family = AF_INET;
	server->sin_port = htons( 8888 );
}


void conectar_servidor(int sock, struct sockaddr_in server)
{
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("Erro de conexão.");
		exit (EXIT_FAILURE);	
	}
}

void enviar_mensagem(char *msg, int sock)
{
	if( send(sock , msg , strlen(msg) , 0) < 0)
	{
		perror("Mensagen não enviada.");
		exit (EXIT_FAILURE);
	}
}

char *get_msg(int sock, int flag)
{
	char *server_reply = malloc(2000);
	if( recv(sock , server_reply , 2000 , flag) < 0)
	{
		perror("Mensagen não recebida.");
		exit (EXIT_FAILURE);
	}

	return server_reply;
}

int main(int argc , char *argv[])
{
	int sock, qtd_rodadas, jogada;
	char nickname[10] = "\0", *resposta, *mensagem = malloc(100), *iniciar = malloc(1);
	struct sockaddr_in server;

	sock = criar_sock();	
	config_server(&server);		
	conectar_servidor(sock, server);

	printf("\n\n\n\t[ Jokenpo - BBT ]\n\n");
	
	//Nick	
	printf("\n\nInforme seu nick: (10 CARACTERES) ");
	scanf("%s" , nickname);
	enviar_mensagem(nickname, sock);

	//Retorno
	resposta = get_msg(sock,0);
	printf("\n\n\t*** %s ***\n\n",resposta);
	
	printf("Deseja iniciar partida? [S/N] ");
	scanf("%s",iniciar);

	if(strcmp(iniciar, "S") == 0)
	{
		enviar_mensagem(iniciar, sock);	

		resposta = get_msg(sock,0);
		printf("%s\n\n",resposta);

		qtd_rodadas = 0;	

		fflush(stdin);
		scanf("%d",&jogada);
		sprintf(mensagem,"%d",jogada);
		enviar_mensagem(mensagem, sock);

		resposta = get_msg(sock,0);
		printf("\n\n%s\n",resposta);
		qtd_rodadas++;
		

		
	}
	else
		close(sock);
	
	
	return 0;
}
