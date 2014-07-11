#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> //for threading , link with lpthread

#define MAX 5

static int indice = -1;
static int partida = 0;
char *lista_usuarios[MAX];
int lista_sockets[MAX];

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
	server->sin_family = AF_INET;
	server->sin_addr.s_addr = INADDR_ANY;
	server->sin_port = htons( 8888 );
}

void binder(int sock, struct sockaddr_in server)
{
	if( bind(sock,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("Erro de BIND.");
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
		printf("Flag mensagem com erro: %d. ",flag);
		perror("Mensagen não recebida.");
		exit (EXIT_FAILURE);
	}

	return server_reply;
}

void add_usuario(char *nickname, int sock)
{	
	char *msg = malloc(10);
	
	indice++;
	lista_usuarios[indice] = nickname;
	lista_sockets[indice] = sock;
	sprintf(msg, "Usuário %s is online.\n",nickname);
	write(sock , msg , strlen(msg));
}

void lista_usuarios_online()
{
	int i;
	for(i = 0; i <= indice; i++)
		printf("Nickname: %s | Socket: %d\n",lista_usuarios[i], lista_sockets[i]);
}


void comecar_partida()
{	
	partida = 1;
	int i;
	char *mensagem = malloc(100);
	sprintf(mensagem,"\n\n*** Partida iniciada. %d jogadores na partida. ***",indice);

	for(i = 0; i <= indice; i++)
	{	printf("STARTS");
		enviar_mensagem(mensagem,lista_sockets[i]);
	}
}

void *connection_handler(void *socket_desc)
{
	int sock = *(int*)socket_desc, qtd_rodadas = 0;
	int read_size;
	char *message = malloc(2000), *nickname = malloc(10);

	nickname = get_msg(sock, 0);
	
	add_usuario(nickname, sock);
	
	//Qtd Rodadas
	message = get_msg(sock, 0);
	qtd_rodadas = atoi(message);

	lista_usuarios_online();

	if(indice >=1) //&& partida == 0)
		comecar_partida();


	/*Receive a message from client
	while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
	{
	//Send the message back to client
	write(sock , client_message , strlen(client_message));
	}

	//Send some messages to the client
	message = "Greetings! I am your connection handler\n";
	write(sock , message , strlen(message));

	message = "Now type something and i shall repeat what you type \n";
	write(sock , message , strlen(message));



	if(read_size == 0)
	{
	puts("Client disconnected");
	fflush(stdout);
	}
	else if(read_size == -1)
	{
	perror("recv failed");
	}
	 */
	//Free the socket pointer
	//free(socket_desc);

	return 0;
}

int main(int argc , char *argv[])
{
	int sock, client_sock , c , read_size, *new_sock;
	struct sockaddr_in server , client;
	char client_message[10] = "\0";
	
	

	sock = criar_sock();
	config_server(&server);
	binder(sock, server);
	listen(sock , 10);

	puts("\n\nSERVIDOR ONLINE\n");

	c = sizeof(struct sockaddr_in);


	while( (client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
		puts("Aceitou uma conexão.");
		 
		pthread_t sniffer_thread;
		new_sock = malloc(1);
		*new_sock = client_sock;
		 
		if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
		{
		    perror("could not create thread");
		    return 1;
		}
		 
		//Now join the thread , so that we dont terminate before the thread
		pthread_join( sniffer_thread , NULL);
		puts("Handler assigned\n");
	}



	/*Aceitando conexao de um cliente
	client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);

	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}

	puts("Connection accepted\n\n");

	//Receive a message from client
	while( (read_size = recv(client_sock , client_message , 10 , 0)) > 0 )
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

	*/


	return 0;
}
