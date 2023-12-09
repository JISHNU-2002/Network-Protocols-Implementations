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

    int b = bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    if(b < 0){
        printf("bind error\n");
        exit(0);
    }else{
        printf("bind success\n");
    }

    listen(sockfd,1);
    printf("server listening\n");

    int n = sizeof(client);
    int c_sock = accept(sockfd,(struct sockaddr*)&client,&n);
    if(c_sock < 0){
        printf("not accepted\n");
        exit(0);
    }else{
        printf("accepted client\n");
    }

    char mail_from[100],mail_to[100],mail_body[100];
    recv(c_sock,mail_from,sizeof(mail_from),0);
    recv(c_sock,mail_to,sizeof(mail_to),0);
    recv(c_sock,mail_body,sizeof(mail_body),0);

    printf("from address : %s\n",mail_from);
    printf("to address : %s\n",mail_to);
    printf("mail body \n%s\n",mail_body);

    close(sockfd);
    printf("disconnected\n");

    return 0;
}