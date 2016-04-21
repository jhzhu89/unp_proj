//
// Created by ZhuJiahao on 4/15/16.
//

#include <unp.h>

void str_echo(int sockfd);
void sig_chld(int signo);

int main(int argc, char** argv) {
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if (listenfd < 0) {
        fprintf(stderr, "socket error\n");
        return -1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    if (bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        fprintf(stderr, "bind error\n");
        return -1;
    }

    if (listen(listenfd, LISTENQ) < 0) {
        fprintf(stderr, "listen error\n");
        return -1;
    }

    signal(SIGCHLD, sig_chld);

    for (;;) {
        clilen = sizeof(cliaddr);

        if ((connfd = accept(listenfd, (struct sockaddr*) &cliaddr, &clilen)) < 0) {
            if (errno == EINTR) {
                fprintf(stderr, "receive signal EINTR!\n");
                continue;
            } else {
                fprintf(stderr, "accept error\n");
                return -1;
            }
        }

        childpid = fork();

        if (childpid == 0) { // child process
            close(listenfd);
            str_echo(connfd);
            exit(0);
        } else if (childpid == -1) {
            fprintf(stderr, "fork error\n");
            return -1;
        }

        close(connfd); // parent close the connected socket
    }

    return 0;
}

void str_echo(int sockfd) {
    char line[MAXLINE];
    FILE* fpin, *fpout;
    fpin = fdopen(sockfd, "r");
    fpout = fdopen(sockfd, "w");

    while (Fgets(line, MAXLINE, fpin) != NULL)
        Fputs(line, fpout);
}

void sig_chld(int signo) {
    pid_t pid;
    int stat;

    //pid = wait(&stat);
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        fprintf(stdout, "child %d terminated\n", pid);

    return;
}
