#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sockfd,client_sock,n,num,fact;
    char buf[1024];
    struct sockaddr_in server,client;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd < 0){
        printf("[-]UDP socket error\n");
        exit(0);
    }else{
        printf("[+]UDP socket created\n");
    }

    server.sin_family = AF_INET;
    server.sin_port = 4000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

  
    printf("[+]Client ready\n");
    n = sizeof(server);

          printf("\nclient : ");
        gets(buf);
        sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&server,n);
      
    close(sockfd);
    printf("[-]Disconnected from Server...\n");
    return 0;
}
