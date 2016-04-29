//
// Created by Neptune on 4/29/16.
//
#include <unistd.h>
#include <sys/socket.h>
#include "../include/error.h"

ssize_t read_fd(int fd, void *ptr, size_t nbytes, int *recvfd) {
    struct msghdr msg;
    struct iovec iov[1];
    ssize_t n;
    // have the msghdr_msg_control
    union {
        struct cmsghdr cm;
        char control[CMSG_SPACE(sizeof(int))];
    } control_un;
    struct cmsghdr *cmptr;
    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un.control);
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    iov[0].iov_base = ptr;
    iov[0].iov_len = nbytes;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

    if ((n = recvmsg(fd, &msg, 0)) <= 0)
        return (n);

    if ((cmptr = CMSG_FIRSTHDR(&msg)) != NULL &&
            cmptr->cmsg_len == CMSG_LEN(sizeof(int))) {
        if (cmptr->cmsg_level != SOL_SOCKET)
            err_quit("control level != SOL_SOCKET");

        if (cmptr->cmsg_type != SCM_RIGHTS)
            err_quit("control type != SOL_RIGHTS");

        *recvfd = *((int *) CMSG_DATA(cmptr));
    } else
        *recvfd = -1;

    return n;
}

ssize_t Read_fd(int fd, void *ptr, size_t nbytes, int *recvfd) {
    return read_fd(fd, ptr, nbytes, recvfd);
}
