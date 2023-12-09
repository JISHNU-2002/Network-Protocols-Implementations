#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<math.h>

int main(){
    struct sockaddr_in server,client;
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

    int b = bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    if(b < 0){
        printf("[-]TCP bind error\n");
        exit(0);
    }else{
        printf("[+]TCP bind success\n");
    }

    listen(sockfd,1);
    printf("[+]SERVER Listening\n");
    int n = sizeof(client);
    int c_sock = accept(sockfd,(struct sockaddr*)&client,&n);
 
    int m;
    recv(c_sock,&m,sizeof(m),0);
    printf("no of frames to be received = %d\n",m);

    int gbn;
    recv(c_sock,&gbn,sizeof(gbn),0);
    printf("value of gbn = %d\n",gbn);

    int frame,ack;
    int temp = rand()%m;

    while(1){
        recv(c_sock,&frame,sizeof(frame),0);
        ack = frame;
        
        if(frame == temp){
            printf("timeout || resend current frame\n");
            sleep(5);
            ack = -1;
            temp = -1;
        }else{
            printf("frame[%d] received\n",frame);
            printf("ack[%d] send\n",ack);
        }
        send(c_sock,&ack,sizeof(ack),0);

        if(ack == m-1){
            break;
        }
    }

    close(sockfd);
    return 0;
}