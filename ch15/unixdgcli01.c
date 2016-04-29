//
// Created by Neptune on 4/24/16.
//

#include "unp.h"

void dg_cli(FILE *, int, const SA *, socklen_t);

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_un cliaddr, servaddr;
    sockfd = Socket(AF_LOCAL, SOCK_DGRAM, 0);
    bzero(&cliaddr, sizeof(cliaddr)); // bind an address for us
    cliaddr.sun_family = AF_LOCAL;
    //strcpy(cliaddr.sun_path, tmpnam(NULL));
    char *s = "/tmp/unix.dgtmp";
    unlink(s);
    strcpy(cliaddr.sun_path, "/tmp/unix.dgtmp");
    Bind(sockfd, (SA *)&cliaddr, sizeof(cliaddr));
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXDG_PATH);
    dg_cli(stdin, sockfd, (SA *)&servaddr, sizeof(servaddr));
}

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen) {
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    socklen_t len;
    //Connect(sockfd, (SA*)pservaddr, servlen);

    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        //Write(sockfd, sendline, MAXLINE);
        //n = Read(sockfd, recvline, MAXLINE);
        //recvline[n] = 0; // null terminate
        //Fputs(recvline, stdout);
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        len = servlen;
        n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        recvline[n] = 0; // null terminate
        Fputs(recvline, stdout);
    }
}
