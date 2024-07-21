#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    struct sockaddr_in server,client;
    int n = sizeof(server);

    int sockfd = socket(AF_INET,SOCK_STREAM,0);    
    if(sockfd < 0){
        printf("[-]TCP server socket error\n");
        exit(0);
    }else{
        printf("[+]TCP server socket created\n");
    }
    server.sin_family = AF_INET;
    server.sin_port = 5000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("[+]CLIENT Ready\n");
    int con = connect(sockfd,(struct sockaddr*)&server,sizeof(server));
    if(con < 0){
        printf("[-]CLIENT connection error\n");
        exit(0);
    }else{
        printf("[+]CLIENT connection successfull\n");
    }

    int frame[10],ack,i,m;
    printf("enter no of frames = ");
    scanf("%d",&m);
    send(sockfd,&m,sizeof(m),0);

    int gbn;
    printf("enter the value of gbn = ");
    scanf("%d",&gbn);
    send(sockfd,&gbn,sizeof(gbn),0);

    for(i=0;i<m;i++){
        frame[i] = i;
    }
    i=0;

    while(1){
        send(sockfd,&frame[i],sizeof(frame[i]),0);
        printf("frame[%d] send\n",frame[i]);

        recv(sockfd,&ack,sizeof(ack),0);
        if(ack == frame[i]){
            printf("ack[%d] received\n",ack);
            i++;
        }else{
            printf("timeout || resending frame[%d]\n",frame[i]);
            i = i-gbn+1;
        }

        if(ack == m-1){
            break;
        }
    }

    close(sockfd);
    return 0;
}