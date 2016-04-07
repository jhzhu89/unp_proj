//
// Created by ZhuJiahao on 4/6/16.
//
#include "unp.h"

static void recvfrom_int(int);
void dg_echo(int, SA*, socklen_t);

static int count;

int main(int argc, char** argv) {
    struct sockaddr_in servaddr, cliaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    Bind(sockfd, (SA*)&servaddr, sizeof(servaddr));
    dg_echo(sockfd, (SA*)&cliaddr, sizeof(cliaddr));
}

void dg_echo(int sockfd, SA* pcliaddr, socklen_t clilen) {
    socklen_t len;
    char mesg[MAXLINE];
    //Signal();
    signal(SIGINT, recvfrom_int);

    for (;;) {
        len = clilen;
        Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
        count++;
    }
}

static void recvfrom_int(int signo) {
    printf("\nreceived %d datagrams\n", count);
    exit(0);
}
