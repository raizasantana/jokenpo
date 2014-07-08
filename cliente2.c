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
    char message[1000] , server_reply[2000];
     
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
	//printf("%s",message);
         
        //Enviar dados
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
         
        //Receber resposta do servidor
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
         
        puts("Server reply :");
        printf("%s",server_reply);
    }
     
    close(sock);
    return 0;
}
