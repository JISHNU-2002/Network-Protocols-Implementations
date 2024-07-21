#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sockfd,client_sock,b,n;
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

    b = bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    if(bind < 0){
        printf("[-]TCP bind error\n");
        exit(0);
    }else{
        printf("[+]TCP bind successfull\n");
    }

    listen(sockfd,1);
    printf("Server listening waiting for CLIENT...\n");
    n = sizeof(client);
    client_sock = accept(sockfd,(struct sockaddr*)&client,&n);
    if(client_sock < 0){
        printf("[-]Client connection error\n");
        exit(0);
    }else{
        printf("[+]Client connection accepted\n");
    }

    for(;;){
        recv(client_sock,buf,sizeof(buf),0);
        if(strcmp(buf,"end")==0){
            break;
        }
        printf("\nclient : %s",buf);
        printf("\nserver : ");
        gets(buf);
        send(client_sock,buf,sizeof(buf),0);
        if(strcmp(buf,"end")==0){
            break;
        }
    }
    close(client_sock);
    printf("[-]Client disconnected...\n");
    close(sockfd);
    return 0;
}