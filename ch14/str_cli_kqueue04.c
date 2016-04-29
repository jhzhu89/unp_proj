//
// Created by ZhuJiahao on 4/16/16.
//
#include "unp.h"

void str_cli(FILE *fp, int sockfd) {
    int kq, i, n, nev, stdineof = 0, isfile;
    char buf[MAXLINE];
    struct kevent kev[2];
    struct timespec ts;
    struct stat st;
    isfile = ((fstat(fileno(fp), &st) == 0) &&
              (st.st_mode & S_IFMT) == S_IFREG);
    printf("isfile: %d\n", isfile);
    EV_SET(&kev[0], fileno(fp), EVFILT_READ, EV_ADD, 0, 0, NULL);
    EV_SET(&kev[1], sockfd, EVFILT_READ, EV_ADD, 0, 0, NULL);
    kq = Kqueue();
    ts.tv_sec = ts.tv_nsec = 0;
    // register events
    Kevent(kq, kev, 2, NULL, 0, &ts);

    for (;;) {
        nev = Kevent(kq, NULL, 0, kev, 2, NULL);

        for (i = 0; i < nev; i++) {
            if (kev[i].ident == sockfd) {
                if ((n = Read(sockfd, buf, MAXLINE)) == 0) {
                    if (stdineof == 1)
                        return; // normal termination
                    else
                        err_quit("str_cli: server termintated prematurely");
                }

                Write(fileno(stdout), buf, n);
            }

            if (kev[i].ident == fileno(fp)) {
                // input is readable
                n = Read(fileno(fp), buf, MAXLINE);

                if (n > 0)
                    Writen(sockfd, buf, n);

                if (n == 0 || (isfile && n == kev[i].data)) {
                    stdineof = 1;
                    Shutdown(sockfd, SHUT_WR);
                    kev[i].flags = EV_DELETE;
                    Kevent(kq, &kev[i], 1, NULL, 0, &ts);
                    continue;
                }
            }
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2)
        err_quit("usage: str_cli_kqueue04 <IPadress>");

    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &serv.sin_addr);
    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    Connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    str_cli(stdin, sockfd);
    return 0;
}
