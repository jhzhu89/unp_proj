#include <unp.h>

#define max(a, b) ((a > b) ? a : b)

void str_cli(FILE* fp, int sockfd);

int main(int argc, char** argv) {
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2) {
        fprintf(stderr, "usage: tcpcli <IPaddress>");
        exit(1);
    }

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    Connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);
    return 0;
}

void str_cli(FILE* fp, int sockfd) {
    int maxfdp1;
    fd_set rset;
    char sendline[MAXLINE], recvline[MAXLINE];
    int stdineof = 0;
    FD_ZERO(&rset);

    for (; ;) {
        FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(sockfd, &rset)) {
            bzero(recvline, sizeof(sendline));

            if (read(sockfd, recvline, MAXLINE) == 0) {
                if (stdineof == 1)
                    return; // normal termination, client shutdown the connection, server sent FIN
                else {
                    fprintf(stderr, "server terminated prematurely\n");
                    exit(1);
                }
            }

            fputs(recvline, stdout);
        }

        if (FD_ISSET(fileno(fp), &rset)) {
            /*bzero(sendline, sizeof(sendline));
            if (fgets(sendline, MAXLINE, fp) == NULL)
                return;
            write(sockfd, sendline, strlen(sendline));*/
            bzero(sendline, sizeof(sendline));

            if (read(fileno(fp), sendline, MAXLINE) == 0) {
                stdineof = 1;

                if (shutdown(sockfd, SHUT_WR) < 0) {
                    fprintf(stderr, "shutdown error\n");
                    exit(1);
                }

                FD_CLR(fileno(fp), &rset);
                continue;
            }

            if (write(sockfd, sendline, strlen(sendline)) < 0) {
                fprintf(stderr, "write error\n");
                exit(1);
            }
        }
    }
}
