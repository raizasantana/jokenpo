/*
    Cliente Ativo
*/
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
 
int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[10] = "\0", server_reply[10] = "\0";

    int m = 0;
     
    //Criando socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Nao foi possivel criar o socket\n");
    }
    puts("Socket criado.\n");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Conectar com servidor remoto
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("ERROR. Conexao falhou.");
        return 1;
    }
     
    puts("Conectado.\n");
     
    //Continuar a cominucacao com o servidor
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
	
	}
     
    close(sock);
    return 0;
}
