#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
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
    server.sin_port = 3000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    int n = sizeof(server);
    int con = connect(sockfd,(struct sockaddr*)&server,n);
    if(con < 0){
        printf("not connected\n");
        exit(0);
    }else{
        printf("connectied\n");
    }

    char buf[1024];
    FILE *fp;

    fp = fopen("jishnu.txt","r");
  
    while(fgets(buf,sizeof(buf),fp) != NULL){
        send(sockfd,buf,sizeof(buf),0);
    }
    printf("file transfer completed\n");

    close(sockfd);
    printf("disconnected\n");

    return 0;
}