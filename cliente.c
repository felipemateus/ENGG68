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
    if(sockfd<0){
        printf("error");
    }
    char buffer[256];
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

    printf("hello\n");
}