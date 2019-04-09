#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>






int main(){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    int valread = 0;
    char buffer[256]  = {0};

    if(sockfd<0){
        printf("error");
    }
    char *hello = "alo do cliente!";
    struct sockaddr_in serv_addr;
    struct hostent *server;
    server = gethostbyname("localhost");
    bzero((char *) &serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(5000);




    if(connect(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        printf("Erro na connexão\n");
    }

    
    //lê mensagem de boas vindas do servidor.
    valread =  read(sockfd,buffer,256);
    printf("%s\n", buffer);
    printf("Digite o codigo da discliplina:\n");

    while(1){
        scanf("%s",buffer);
        write(sockfd,buffer,strlen(buffer));
        valread =  read(sockfd,buffer,256);
        printf("%s\n",buffer);
    } 

    //write(sockfd,hello,strlen(hello));

    close(sockfd);
}