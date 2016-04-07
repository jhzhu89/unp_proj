//
// Created by ZhuJiahao on 4/5/16.
//
#include <unp.h>

void dg_cli(FILE*, int, const SA*, socklen_t);

int main(int argc, char** argv) {
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2)
        err_quit("usage: udpcli <IPAdress>");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_len = sizeof(servaddr);
    //servaddr.sin_port = htons(7); // port of standard echo server
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    dg_cli(stdin, sockfd, (SA*)&servaddr, sizeof(servaddr));
    exit(0);
}

void dg_cli(FILE* fp, int sockfd, const SA* pservaddr, socklen_t servlen) {
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    socklen_t len;
    struct sockaddr* preply_addr = Malloc(servlen);

    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        len = servlen;
        n = Recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);

        if (len != servlen)
            printf("!\n");

        if (len != servlen || memcmp(pservaddr, preply_addr, len) != 0) {
            fprintf(stdout, "reply from %s (ignored)\n", Sock_ntop(preply_addr, len));
            fprintf(stdout, "pservaddr->len %d, preply_addr->len %d\n", pservaddr->sa_len,
                    preply_addr->sa_len);
            continue;
        }

        recvline[n] = 0; // null terminate
        Fputs(recvline, stdout);
    }
}
