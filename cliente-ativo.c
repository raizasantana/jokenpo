#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PEDRA 0
#define PAPEL 1
#define TESOURA 2
#define LAGARTO 3
#define SPOCK 4

#define PORTA_SERVIDOR 10
#define BUFFSIZE 32


void buscar_usuario_servidor()
{
}

void add_usuario_servidor(char nickname)
{


}


int main()
{

	struct sockaddr_in cliAddr, remoteServAddr;
  	struct hostent *h;

	char nickname[10] = "\0";
	int qtdJogadas;

	printf("\n\n/* Jokenpo BBT */\n\n\nEscolha um nick:");
	scanf("%s",nickname);
	


}













