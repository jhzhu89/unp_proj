//
// Created by ZhuJiahao on 4/6/16.
//
#include "unp.h"

void str_echo(int);

int main(int argc, char **argv) {
    int listenfd, connfd, udpfd, nready, maxfdp1;
    char mesg[MAXLINE];
    pid_t childpid;
    fd_set rset;
    ssize_t n;
    socklen_t len;
    const int on = 1;
    struct sockaddr_in cliaddr, servaddr;
    void sig_chld(int);
    // create listening TCP socket
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    // set this option before binding
    Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    // create the UDP socket
    udpfd = Socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    Bind(udpfd, (SA *) &servaddr, sizeof(servaddr));
    Signal(SIGCHLD, sig_chld); // must call waitpid()
    FD_ZERO(&rset);
    maxfdp1 = max(listenfd, udpfd) + 1;

    for (;;) {
        FD_SET(listenfd, &rset);
        FD_SET(udpfd, &rset);

        if ((nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) {
            if (errno ==  EINTR)
                continue;
            else
                err_sys("select error");
        }

        if (FD_ISSET(listenfd, &rset)) {
            len = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA *)&cliaddr, &len);

            if ((childpid = Fork()) == 0) { // child process
                Close(listenfd);
                str_echo(connfd);
                exit(0);
            }

            Close(connfd);
        }

        if (FD_ISSET(udpfd, &rset)) {
            len = sizeof(cliaddr);
            n = Recvfrom(udpfd, mesg, MAXLINE, 0, (SA *)&cliaddr, &len);
            Sendto(udpfd, mesg, n, 0, (SA *)&cliaddr, len);
        }
    }
}

void str_echo(int sockfd) {
    ssize_t n;
    char buf[MAXLINE];
again:

    while ((n = Read(sockfd, buf, MAXLINE)) > 0) {
        fprintf(stdout, "%s\n", buf);
        Write(sockfd, buf, n);
    }

    if (n < 0 && errno == EINTR) {
        fprintf(stdout, "!!! received EINTR\n");
        goto again;
    } else if (n < 0) {
        fprintf(stderr, "write error\n");
        exit(1);
    }
}

void sig_chld(int signo) {
    pid_t pid;
    int stat;

    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        fprintf(stdout, "child %d terminated\n", pid);

    return;
}
