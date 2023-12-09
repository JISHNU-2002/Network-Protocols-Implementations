#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sockfd;
    struct sockaddr_in server,client;
    char buf[1024];

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        printf("[-]TCP socket error\n");
        exit(0);
    }else{
        printf("[+]TCP socket created\n");
    }

    server.sin_family = AF_INET;
    server.sin_port = 2000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("Client ready...\n");

    int n = sizeof(server);
    int con = connect(sockfd,(struct sockaddr*)&server,n);
    if(con < 0){
        printf("[-]Client connection error\n");
        exit(0);
    }else{
        printf("Client connection successfull\n");
    }

    for(;;){
        printf("\nclient : ");
        gets(buf);
        send(sockfd,buf,sizeof(buf),0);
        if(strcmp(buf,"end")==0){
            break;
        }
        recv(sockfd,buf,sizeof(buf),0);
        if(strcmp(buf,"end")==0)
            break;
        printf("server : %s\n",buf);
    }
    close(sockfd);
    printf("[-]Disconnected from Server...\n");
    return 0;
}