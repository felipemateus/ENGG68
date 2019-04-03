#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>


int main(){
    int sockfd = 0;
    int newsockfd = 0;
    int valread = 0;
    char buffer[256] = {0};
    //Cria o socket, AF_INET:familiaipv4, SOCK_STREAM:protocolo TCP,
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        printf("error/n");
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;
    //htons é responsavel pelo ordenamento dos bytes.
    serv_addr.sin_port = htons(5000);
    //o metodo bind faz a associação a uma porta especifica
    if(bind(sockfd, (struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0){
        printf("error/n");
    }
    //5 é o numero maximo de conexões simultâneas
    listen(sockfd,5);

    socklen_t  clilen;
    struct sockaddr_in cli_addr;

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,&clilen);

    if(newsockfd<0){
        printf("Erro na aceitação");
    }
    //mensagem do cliente
    valread =  read(newsockfd,buffer,256);

    printf("%s\n",buffer);


    printf("hello\n");
}