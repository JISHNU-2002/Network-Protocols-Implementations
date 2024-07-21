#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sockfd,b,n;
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

    b = bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    if(b < 0){
        printf("[-]UDP bind error\n");
        exit(0);
    }else{
        printf("[+]UDP bind successfull\n");
    }

    printf("[+]Server ready , waiting for Client\n");
    n = sizeof(client);


        recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&client,&n);
     
        printf("\nclient : %s",buf);



    printf("[-]Client disconnected...\n");
    close(sockfd);
    return 0;
}
