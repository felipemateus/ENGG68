#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>


int main(){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        printf("error");
    }
    printf("hello\n");
}