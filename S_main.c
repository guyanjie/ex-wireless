/*
 * File:   main.c
 * Author: GY
 *
 * Created on 2012年5月13日, 上午9:33
 */

#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
//#include <winsock2.h>

#define port 4321
#define buf_size 1024
#define max_que_conn_nm  5

int main(int argc, char** argv) {
    struct sockaddr_in server_sockaddr, client_sockaddr;
    int sin_size, recvbytes;
    int sockfd, client_fd;
    char buf[buf_size];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    printf("sockfd id = %d\n", sockfd);

    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(port);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_sockaddr.sin_zero), 8);
    int i = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof (i));

    if (bind(sockfd, (struct sockaddr *) &server_sockaddr, sizeof (struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }
    printf("bind success!\n");

    if (listen(sockfd, max_que_conn_nm) == -1){
        perror("listen");
        exit(1);
    }
    printf("listening...\n");

    if((client_fd = accept(sockfd,(struct sockaddr *)&client_sockaddr,&sin_size))==-1){
        perror("accept");
        exit(1);
    }

    memset(buf,0,sizeof(buf));
    if((recvbytes = recv(client_fd,buf,buf_size,0))== -1){
        perror("recv");
        exit(1);

    }
    printf("receive a message :%s\n",buf);
    close(sockfd);
    exit(0);
        return (EXIT_SUCCESS);
}

