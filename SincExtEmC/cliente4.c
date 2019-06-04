#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

struct tm* current_time;


//Timer com delay
void *iniciaTimer(void *args){
    printf("Thread criada com sucesso!\n");
    int t = 0;
    while(1){
        sleep(1.02);
        current_time->tm_sec++;
        t++;
        //correção do tempo
        if(current_time->tm_sec >59){
            current_time->tm_sec = 0;
            current_time->tm_min++;
        }
        if(current_time->tm_min >59){
            current_time->tm_min= 0;
            current_time->tm_hour++;
        }
        //ficou faltando as outras correções
            
        if(t == 5){
            t=0;
            printf("\ntempo: min = %d, sec = %d\n",current_time->tm_min,current_time->tm_sec); 
        }
            
    }

    pthread_exit(NULL);

    
}

int main(){
    //configura o relógio
    struct tm* server_time;
    time_t s;
    s = time(NULL);
    current_time = localtime(&s);
    
    
    //Inicia Thread que conta o tempo errado
    pthread_t thread;
    pthread_create(&thread, NULL,iniciaTimer,NULL);
    
    
    //configura conexão
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    int valread = 0;
    char buffer[256]  = {0};
    clock_t  start_t = 0;
    clock_t end_t 	= 0; 

    if(sockfd<0){
        printf("error");
    }
    char *hello = "alo do cliente 1!";
    struct sockaddr_in serv_addr;
    socklen_t fromlen = sizeof(struct sockaddr_in);
    struct hostent *server;
    //endereco ip do servidor
    server = gethostbyname("localhost");
    bzero((char *) &serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(5555);

    start_t = clock();

    while(1){
        printf("Cliente  1  \n");

        sleep(5);

        valread =  sendto(sockfd,hello,256,0, (struct sockaddr *)&serv_addr,fromlen);
        if(valread < 0){
        printf("Erro na connexão\n");
        }
        valread =  recvfrom(sockfd,(struct tm *)server_time,(int) sizeof(server_time),0,(struct sockaddr *)&serv_addr,&fromlen);
    
        printf("tempo em min:%d\n",server_time->tm_min);


    }
    close(sockfd);

    end_t = clock();

    printf("tempo____: %f /n", ((float)(end_t - start_t)/CLOCKS_PER_SEC)*1000);


}   

