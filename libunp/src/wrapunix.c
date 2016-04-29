//
// Created by Neptune on 4/2/16.
//
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/error.h"

pid_t Fork(void) {
    pid_t pid;

    if ((pid = fork()) == -1)
        err_sys("fork error");

    return pid;
}

ssize_t Read(int fd, void *ptr, size_t nbytes) {
    ssize_t n;

    if ((n = read(fd, ptr, nbytes)) == -1)
        err_sys("read error");

    return n;
}

void Close(int fd) {
    if (close(fd) == -1)
        err_sys("close error");
}

void Write(int fd, void *ptr, size_t nbytes) {
    if (write(fd, ptr, nbytes) != nbytes)
        err_sys("write error");
}

void *Malloc(size_t size) {
    void *ptr;

    if ((ptr = malloc(size)) == NULL)
        err_sys("malloc error");

    return ptr;
}

pid_t Waitpid(pid_t pid, int *iptr, int options) {
    pid_t retpid;

    if ((retpid = waitpid(pid, iptr, options)) == -1)
        err_sys("waitpid error");

    return retpid;
}
