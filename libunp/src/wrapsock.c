//
// Created by Neptune on 4/2/16.
//
#include <errno.h>
#include <stdlib.h>
#include "../include/wrapsock.h"
#include "../include/error.h"

int Accept(int fd, struct sockaddr* sa, socklen_t* salenptr) {
    int n;
again:

    if ((n = accept(fd, sa, salenptr)) < 0) {
        #ifdef EPROTO

        if (errno == EPROTO || errno == ECONNABORTED)
        #else
        if (errno == ECONNABORTED)
        #endif
            goto again;
        else
            err_sys("accept error");
    }

    return n;
}

void Bind(int fd, const struct sockaddr* sa, socklen_t salen) {
    if (bind(fd, sa, salen) < 0)
        err_sys("bind error");
}

void Connect(int fd, const struct sockaddr* sa, socklen_t salen) {
    if (connect(fd, sa, salen) < 0)
        err_sys("connect error");
}

void Getpeername(int fd, struct sockaddr* sa, socklen_t* salenptr) {
    if (getpeername(fd, sa, salenptr) < 0)
        err_sys("getpeername error");
}

void Getsockname(int fd, struct sockaddr* sa, socklen_t* salenptr) {
    if (getsockname(fd, sa, salenptr) < 0)
        err_sys("getsockname error");
}

void Getsockopt(int fd, int level, int optname, void* optval,
                socklen_t* optlenptr) {
    if (getsockopt(fd, level, optname, optval, optlenptr) < 0)
        err_sys("getsockopt error");
}

void Listen(int fd, int backlog) {
    char* ptr;

    if ((ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);

    if (listen(fd, backlog) < 0)
        err_sys("listen error");
}

int Socket(int family, int type, int protocol) {
    int n;

    if ((n = socket(family, type, protocol)) < 0)
        err_sys("socket error");

    return n;
}

