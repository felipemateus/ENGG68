#include <stdio.h>
#include <time.h>
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
    clock_t  start_t = 0;
    clock_t end_t 	= 0; 

    if(sockfd<0){
        printf("error");
    }
    char *hello = "alo do cliente!";
    struct sockaddr_in serv_addr;
    struct hostent *server;
    //endereco ip do servidor
    //server = gethostbyname("10.131.16.167");
    server = gethostbyname("localhost");

    bzero((char *) &serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(5000);

    start_t = clock();

    
    if(connect(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        printf("Erro na connexão\n");
    }

    
    //lê mensagem de boas vindas do servidor.
    valread =  read(sockfd,buffer,256);
    printf("%s\n",buffer);
    

    
    //envia mensagem para o servidor
    write(sockfd,hello,strlen(hello));

    close(sockfd);

    end_t = clock();

    printf("tempo____: %f \n", ((float)(end_t - start_t)/CLOCKS_PER_SEC)*1000);

    
}
