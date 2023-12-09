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

    char buf[100];
    recv(sockfd,buf,sizeof(buf),0);
    printf("%s\n",buf);

    char buf2[100];
    printf("enter a string : ");
    gets(buf2);
    send(sockfd,buf2,sizeof(buf2),0);

    int num;
    printf("enter a number = ");
    scanf("%d",&num);
    send(sockfd,&num,sizeof(num),0);

    close(sockfd);
    printf("disconnected\n");

    return 0;
}