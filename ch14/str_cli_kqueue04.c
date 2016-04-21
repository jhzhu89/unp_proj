//
// Created by ZhuJiahao on 4/16/16.
//
#include "unp.h"

void str_cli(FILE* fp, int sockfd) {
    int kq, i, n, nev, stdineof = 0, isfile;
    char buf[MAXLINE];
    struct kevent kev[2];
    struct timespec ts;
    struct stat st;
    isfile = ((fstat(fileno(fp), &st) == 0) &&
              (st.st_mode & S_IFMT) == S_IFREG);
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
                }
            }
        }
    }
}
