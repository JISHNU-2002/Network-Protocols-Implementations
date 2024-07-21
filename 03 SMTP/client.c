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

    char mail_from[100],mail_to[100],mail_body[100];
    printf("enter from address : ");
    gets(mail_from);
    printf("enter to address : ");
    gets(mail_to);
    printf("enter mail body\n");

    char c;
    int t=0;

    while(1){
        c=getchar();
        if(c == '#'){
            mail_body[t] = '\0';
            break;
        }else{
            mail_body[t] = c;
            t++;
        }
    }

    send(sockfd,mail_from,sizeof(mail_from),0);
    send(sockfd,mail_to,sizeof(mail_to),0);
    send(sockfd,mail_body,sizeof(mail_body),0);

    close(sockfd);
    printf("disconnected\n");

    return 0;
}