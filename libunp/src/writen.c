//
// Created by ZhuJiahao on 4/2/16.
//

#include <errno.h>
#include <sys/types.h>
#include "../include/error.h"

ssize_t writen(int fd, const void* vptr, size_t n) {
    size_t nleft = n;
    ssize_t nwritten;
    const char* ptr = vptr;

    while (nleft > 0) {
        if ((nwritten = writen(fd, ptr, nleft)) <= 0) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0; // call write() again
            else
                return -1; // error
        }

        nleft -= nwritten;
        ptr   += nwritten;
    }

    return n;
}

void Writen(int fd, void* ptr, size_t nbytes) {
    if (writen(fd, ptr, nbytes) != nbytes)
        err_sys("writen error");
}

