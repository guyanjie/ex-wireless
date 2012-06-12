/*
 * File:   main.c
 * Author: GY
 *
 * Created on 2012年5月13日, 上午10:02
 */

#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
//#include <winsock2.h>

#define port 4321
#define buf_size 1024

int main(int argc, char** argv) {
    int sockfd, sendbytes;
    char buf[buf_size];
    struct hostent *host;
    struct sockaddr_in serv_addr;

    if (argc < 3) {
        fprintf(stderr, "usage: ./client hostname(or ip address) Text\n ");
        exit(1);
   }
    if ((host = gethostbyname(argv[1])) == NULL) {
        perror("gethostbynemae");
        exit(1);
    }

    memset(buf, 0, sizeof (buf));
    sprintf(buf, "%s", argv[2]);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr = *((struct in_addr *) host->h_addr_list);
    bzero(&(serv_addr.sin_zero), 8);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof (struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    }
    if ((sendbytes = send(sockfd, buf, strlen(buf), 0)) == -1) {
        perror("seng");
        exit(1);
    }
    close(sockfd);
    exit(0);
    return (EXIT_SUCCESS);
}

