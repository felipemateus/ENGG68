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
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    int valread = 0;
    char buffer[256]  = {0};
    clock_t  start_t = 0;
    clock_t end_t 	= 0; 

    if(sockfd<0){
        printf("error");
    }
    char *hello = "alo do cliente!";
    struct sockaddr_in serv_addr;
    socklen_t fromlen = sizeof(struct sockaddr_in);
    struct hostent *server;
    //endereco ip do servidor
    server = gethostbyname("localhost");
    bzero((char *) &serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(5000);

    start_t = clock();

    valread =  sendto(sockfd,hello,256,0, (struct sockaddr *)&serv_addr,fromlen);
    if(valread < 0){
        printf("Erro na connexão\n");
    }

    valread =  recvfrom(sockfd,buffer,256,0,(struct sockaddr *)&serv_addr,&fromlen);
    
    printf("%s\n",buffer);
    
    

    close(sockfd);

    end_t = clock();

    printf("tempo____: %f /n", ((float)(end_t - start_t)/CLOCKS_PER_SEC)*1000);

    
}
