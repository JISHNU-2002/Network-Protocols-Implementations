#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
    struct sockaddr_in server,client;
    int n = sizeof(client);
    char buf[100];

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

    int b = bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    if(b < 0){
        printf("bind error\n");
        exit(0);
    }else{
        printf("bind success\n");
    }

    printf("server ready\n");

    recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&client,&n);
    printf("%s\n",buf);


    close(sockfd);
    printf("disconnected\n");

    return 0;
}