#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
 
//#define MYPORT  10230
#define BUFFER_SIZE 1024
char* SERVER_IP = "139.196.137.139";
//char* SERVER_IP = "127.0.0.1";
#define MYPORT  30130

char sendbuf[BUFFER_SIZE] = "servertime";
char recvbuf[BUFFER_SIZE] = {0};

int recv_len = 0;
char serv_ip[INET_ADDRSTRLEN] = {0};
 
int main()
{
    ///定义sockfd
    int sock_cli = socket(AF_INET,SOCK_DGRAM, 0);
    
    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);  ///服务器ip
    
    printf("connect %s:%d\n",SERVER_IP,MYPORT);
    ///连接服务器，成功返回0，错误返回-1
    
    if(10 == sendto(sock_cli,sendbuf, 10, 0, (struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
        printf("udp send success!\r\n");
    }

    socklen_t len = sizeof(servaddr);
   
    do{
         recv_len = recvfrom(sock_cli, recvbuf, 20, 0, (struct sockaddr *)&servaddr, &len);
    }while(recv_len == 0);
    printf("recv success!\r\n");
   
    inet_ntop(AF_INET, &servaddr.sin_addr, serv_ip, INET_ADDRSTRLEN);
    printf("server ip = %s ,port = %d\r\n", serv_ip, ntohs(servaddr.sin_port));
    printf("recv data is : %s \r\n",recvbuf);
    

    
    close(sock_cli);
    return 0;
}
