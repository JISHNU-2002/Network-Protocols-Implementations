#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
    struct sockaddr_in server,client;
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        printf("socket error\n");
        exit(0);
    }else{
        printf("socket created\n");
    }

    server.sin_family = AF_INET;
    server.sin_port = 5000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    int n = sizeof(server);
    printf("client ready\n");

    char buf[100];
    printf("enter a string : ");
    gets(buf);
    sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&server,n);

    
    printf("disconnected\n");
    close(sockfd);

    return 0;
}