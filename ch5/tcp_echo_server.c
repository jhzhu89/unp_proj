#include <unp.h>

void str_echo(int sockfd);
void sig_chld(int signo);

int main(int argc, char **argv) {
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

    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
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

        if ((connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0) {
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

#if 1
void str_echo(int sockfd) {
    ssize_t n;
    char buf[MAXLINE];
again:

    while ((n = read(sockfd, buf, MAXLINE)) > 0) {
        fprintf(stdout, "%s\n", buf);

        if (write(sockfd, buf, n) != n) {
            fprintf(stderr, "write error\n");
            exit(1);
        }
    }

    if (n < 0 && errno == EINTR) {
        fprintf(stdout, "!!! received EINTR\n");
        goto again;
    } else if (n < 0) {
        fprintf(stderr, "write error\n");
        exit(1);
    }
}
#else
void str_echo(int sockfd) {
    long arg1, arg2;
    ssize_t n;
    char line[MAXLINE];

    for (;;) {
        bzero(line, MAXLINE);

        if ((n = read(sockfd, line, MAXLINE)) == 0)
            return;

        if (sscanf(line, "%ld%ld", &arg1, &arg2) == 2)
            snprintf(line, sizeof(line), "%ld\n", arg1 + arg2);
        else
            snprintf(line, sizeof(line), "input error\n");

        n = strlen(line);
        write(sockfd, line, n);
    }
}
#endif

void sig_chld(int signo) {
    pid_t pid;
    int stat;

    //pid = wait(&stat);
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        fprintf(stdout, "child %d terminated\n", pid);

    return;
}
