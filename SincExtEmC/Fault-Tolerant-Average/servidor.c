#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>


#define QTD 4

struct tm* cliente1 ;
struct tm* cliente2 ;
struct tm* cliente3 ;
struct tm* cliente4 ;


void imprimeTimeCliente(struct tm* tempo, int id){
     printf("Tempo do cliente%d em min: %d    -    sec: %d \n", id,tempo->tm_min,tempo->tm_sec);
 }


//void concatenaTempos()



int main(){
    //configuração do time
    time_t s;
    struct tm* current_time;
    cliente1 = malloc(sizeof(struct tm));
    cliente2 = malloc(sizeof(struct tm));
    cliente3 = malloc(sizeof(struct tm));
    cliente4 = malloc(sizeof(struct tm));




    //s = time(NULL);
    
    //configração da conexão udp
    int sockfd_cliente1 = 0;
    int sockfd_cliente2 = 0;
    int sockfd_cliente3 = 0;
    int sockfd_cliente4 = 0;

    int newsockfd = 0;
    int valread = 0;
    char buffer[256] = {0};
    
    //Cria o socket, AF_INET:familiaipv4, SOCK_STREAM:protocolo TCP,
    sockfd_cliente1 = socket(AF_INET,SOCK_DGRAM,0);
    sockfd_cliente2 = socket(AF_INET,SOCK_DGRAM,0);
    sockfd_cliente3 = socket(AF_INET,SOCK_DGRAM,0);
    sockfd_cliente4 = socket(AF_INET,SOCK_DGRAM,0);
    
    
    if(sockfd_cliente1<0){
        printf("error/n");
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;
    //htons é responsavel pelo ordenamento dos bytes.
    
    serv_addr.sin_port = htons(5550);
    //O metodo bind faz a associação a uma porta especifica
    if(bind(sockfd_cliente1, (struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0){
        printf("error/n");
    }
    serv_addr.sin_port = htons(5551);

     if(bind(sockfd_cliente2, (struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0){
        printf("error/n");
    }
    serv_addr.sin_port = htons(5552);

     if(bind(sockfd_cliente3, (struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0){
        printf("error/n");
    }
    serv_addr.sin_port = htons(5553);

     if(bind(sockfd_cliente4, (struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0){
        printf("error/n");
    }
    


    //5 é o numero maximo de conexões simultâneas
    listen(sockfd_cliente1,5);
    listen(sockfd_cliente2,5);
    listen(sockfd_cliente3,5);
    listen(sockfd_cliente4,5);


    socklen_t  clilen;
    struct sockaddr_in from;

    socklen_t fromlen = sizeof(struct sockaddr_in);

    while(1){
        s = time(NULL);
        current_time = localtime(&s);


        //agora eu vou receber os tempos dos clientes

        newsockfd = recvfrom(sockfd_cliente1,(struct tm *)cliente1,(int) sizeof(cliente1),0, (struct sockaddr *) &from, &fromlen);
        printf("Pacote cliente %d \n",cliente1->tm_min);
        //imprimeTimeCliente(cliente1,1);
        newsockfd = recvfrom(sockfd_cliente2,(struct tm *)cliente2,(int) sizeof(struct tm),0, (struct sockaddr *) &from, &fromlen);
        newsockfd = recvfrom(sockfd_cliente3,(struct tm *)cliente3,(int) sizeof(struct tm),0, (struct sockaddr *) &from, &fromlen);
        newsockfd = recvfrom(sockfd_cliente4,(struct tm *)cliente4,(int) sizeof(struct tm),0, (struct sockaddr *) &from, &fromlen);


        //agora enviar o relogio de todos para cada cliente
        for(int i = 1; i<5; i++){
            sendto(sockfd_cliente1,(struct tm *)current_time, (int) sizeof(current_time),0,(struct sockaddr *) &from, fromlen );
            sendto(sockfd_cliente2,(struct tm *)current_time, (int) sizeof(current_time),0,(struct sockaddr *) &from, fromlen );
            sendto(sockfd_cliente3,(struct tm *)current_time, (int) sizeof(current_time),0,(struct sockaddr *) &from, fromlen );
            sendto(sockfd_cliente4,(struct tm *)current_time, (int) sizeof(current_time),0,(struct sockaddr *) &from, fromlen );

        }        
        
        
        printf("%s\n",buffer);
        //current_time = time(NULL);

        if(newsockfd<0){
            printf("Erro na aceitação");
            return 0;
        }else{
            //sendto(sockfd,"Seja bem vindo",54,0,(struct sockaddr *) &from, fromlen );

            printf("Tempo do servidor em min: %d    -    sec: %d \n", current_time->tm_min,current_time->tm_sec);
            //sendto(sockfd,(struct tm *)current_time, (int) sizeof(current_time),0,(struct sockaddr *) &from, fromlen );
        
        }

        //valread =  recvfrom(sockfd,buffer,256,0,(struct sockaddr *) &from, &fromlen);
    }



    close(sockfd_cliente1);
    close(sockfd_cliente2);
    close(sockfd_cliente3);
    close(sockfd_cliente4);


}
