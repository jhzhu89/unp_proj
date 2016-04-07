//
// Created by ZhuJiahao on 4/6/16.
//
#include "unp.h"

#define NDG     2000 // datagrams to send
#define DGLEN   1400 // length of each datagram

void dg_cli(FILE* fp, int sockfd, const SA* pservaddr, socklen_t servlen) {
    char sendline[DGLEN];

    for (int i = 0; i < NDG; ++i)
        Sendto(sockfd, sendline, DGLEN, 0, pservaddr, servlen);
}

int main(int argc, char** argv) {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t servlen = sizeof(servaddr);

    if (argc < 2)
        err_quit("please specify server address");

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = SERV_PORT;
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    dg_cli(stdin, sockfd, (SA*) &servaddr, servlen);
}
