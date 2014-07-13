#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> //for threading , link with lpthread

#define MAX 5
#define RODADAS 3

#define PEDRA 0
#define PAPEL 1
#define TESOURA 2
#define LAGARTO 3
#define SPOCK 4
#define EMPATE 5

static int indice = -1, qtd_v1 = 0, qtd_v2 = 0;
static int partida = 0;
char *lista_usuarios[MAX], *passivo;
int lista_sockets[MAX], sck_passivo = 0;

typedef struct
{
	int vencedor;
	char *msg;
} Winner;

Winner vencedor_rodada(int jogador1, int jogador2)
{	
	Winner r;

		if (jogador1 == jogador2)
		{			
			r.msg = "Empate.";
			return r;
		}
		else
		{
			switch (jogador1)
			{
				case 0:
					if (jogador2 == 3)
					{
						r.vencedor = jogador1;
						qtd_v1++;
						char *m = malloc(1000);
						sprintf(m,"Pedra esmaga lagarto.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
					
					}
						
					if(jogador2 == 2)
					{
						r.vencedor = jogador1;
						qtd_v1++;
						char *m = malloc(1000);
						sprintf(m,"Pedra esmaga tesoura.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
					
					}

					if (jogador2 == 1)
					{
						r.vencedor = jogador2;
						qtd_v2++;	
						char *m = malloc(1000);
						sprintf(m,"Papel cobre pedra.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;	
						
					}

					if( jogador2 == 4)
					{
						r.vencedor = jogador2;
						qtd_v2++;						
						char *m = malloc(1000);
						sprintf(m,"Spock vaporiza pedra.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
					
					}
					return r;
	
				case 1:
					if (jogador2 == 0)
					{
						r.vencedor = jogador1;
						qtd_v1++;						
						char *m = malloc(1000);
						sprintf(m,"Papel cobre pedra.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
								
					}
					if(jogador2 == 4)
					{
						r.vencedor = jogador1;
						qtd_v1++;						
						char *m = malloc(1000);
						sprintf(m,"Papel desqualifica Spock.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
					
					}
					if ( jogador2 == 2)
					{
						r.vencedor = jogador2;
						qtd_v2++;							
						char *m = malloc(1000);
						sprintf(m,"Tesoura corta papel.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
						
					}
					if(jogador2 == 3)
					{
						r.vencedor = jogador2;
						qtd_v2++;						
						char *m = malloc(1000);
						sprintf(m,"Lagarto come papel.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
					
					}
				
					return r;
	
				case 2:
					if ( jogador2 == 1)
					{
						r.vencedor = jogador1;
						qtd_v1++;							
						char *m = malloc(1000);
						sprintf(m,"Tesoura corta papel.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
						
					}
					if(jogador2 == 3)
					{
						r.vencedor = jogador1;
						qtd_v1++;					
						char *m = malloc(1000);
						sprintf(m,"Tesoura decapita lagarto.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
							
					}
					if(jogador2 == 4)
					{
						r.vencedor = jogador2;
						qtd_v2++;						
						char *m = malloc(1000);
						sprintf(m,"Spock dobra tesoura.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
					
					}
					if(jogador2 == 0)
					{
						r.vencedor = jogador2;
						qtd_v2++;						
						char *m = malloc(1000);
						sprintf(m,"Pedra esmaga tesoura.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
					
					}
				
					return r;

				case 3:
					if ( jogador2 == 4)
					{
						r.vencedor = jogador1;
						qtd_v1++;						
						char *m = malloc(1000);
						sprintf(m,"Lagarto envenena Spock.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
					
					}
					if(jogador2 == 1)
					{
						r.vencedor = jogador1;
						qtd_v1++;						
						char *m = malloc(1000);
						sprintf(m,"Lagarto come papel.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
					
					}
					if(jogador2 == 2)
					{
						r.vencedor = jogador2;
						qtd_v2++;							
						char *m = malloc(1000);
						sprintf(m,"Tesoura decapita lagarto.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
							
					}
					if (jogador2 == 0)
					{
						r.vencedor = jogador2;
						qtd_v2++;						
						char *m = malloc(1000);
						sprintf(m,"Pedra esmaga lagarto.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
					
					}

				
					return r;	

				case 4:
					if( jogador2 == 0)
					{
						r.vencedor = jogador1;
						qtd_v1++;						
						char *m = malloc(1000);
						sprintf(m,"Spock vaporiza pedra.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
					
					}
					if(jogador2 == 2)
					{
						r.vencedor = jogador1;
						qtd_v1++;						
						char *m = malloc(1000);
						sprintf(m,"Spock dobra tesoura.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
					
					}
					if(jogador2 == 1)
					{
						r.vencedor = jogador2;
						qtd_v2++;						
						char *m = malloc(1000);
						sprintf(m,"Papel desqualifica Spock.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
				
					}
					if ( jogador2 == 3)
					{
						r.vencedor = jogador2;
						qtd_v2++;						
						char *m = malloc(1000);
						sprintf(m,"Lagarto envenena Spock.\n***PLACAR***\n%s %d X %s %d",lista_usuarios[0],qtd_v1,lista_usuarios[1],qtd_v2);
						r.msg = m;
					
					}
					return r;
		
				default:			
					r.msg = "Jogada Invalida.";
					return r;
				
			}
		}
}


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
	sprintf(msg, "Usuário %s is online.",nickname);
	enviar_mensagem(msg,sock);
}

void lista_usuarios_online()
{
	int i;
	for(i = 0; i <= indice; i++)
		printf("Nickname: %s | Socket: %d\n",lista_usuarios[i], lista_sockets[i]);
}


void notificar_partida_iniciada()
{
	int i;
	char *mensagem = malloc(100);
	sprintf(mensagem,"\n\n\t*** Já existe uma partida iniciada. Espere a próxima. ***\n");

	for(i = 0; i <= indice; i++)
		enviar_mensagem(mensagem,lista_sockets[i]);
}


void *connection_handler(void *socket_desc)
{
	int sock = *(int*)socket_desc, qtd_rodadas = 0, i;
	int read_size;
	char *message = malloc(2000), *nickname = malloc(10);

	nickname = get_msg(sock, 0);
	char *msg = malloc(1000);

	//Iniciar partida?
	message = get_msg(sock, 0);	

	if(indice > 0)
		indice++;
		lista_usuarios[indice] = nickname;
		lista_sockets[indice] = sock;
	

	lista_usuarios_online();

	if(indice == 1)
	{	

		partida = 1;
		int i, p1, p2, n = 1;
		char *mensagem = malloc(100), *mensagem2 = malloc(100), *msg_resultado = malloc(1000);
		Winner winner; 

		for(i = 1; i <= indice; i++)
			enviar_mensagem("\n\n\t*** JOKENPO!. ***\n\n\tPEDRA 0\n\tPAPEL 1\n\tTESOURA 2\n\tLAGARTO 3\n\tSPOCK 4\n\nQual jogada?",lista_sockets[i]);
				


		mensagem = get_msg(lista_sockets[0], 0);
		p1 = atoi(mensagem);

		mensagem2 = get_msg(lista_sockets[1], 0);
		p2 = atoi(mensagem2);

		winner = vencedor_rodada(p1, p2);
		
		//Placar
		for(i = 1; i <= indice; i++)
			enviar_mensagem(winner.msg,lista_sockets[i]);
			
		}

	
//comecar_partida(sock);
	
		//notificar_partida_iniciada();
	//else
	//	enviar_mensagem("\t***Somente um jogador online. ***",lista_sockets[0]);


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

