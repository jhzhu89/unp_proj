//
// Created by Neptune on 4/2/16.
//

#ifndef UNP_PROJ_WRAPSOCK_H
#define UNP_PROJ_WRAPSOCK_H

#include <sys/socket.h>
#include <sys/time.h>

#define SA struct sockaddr

// prototypes for our socket wrapper functions
int Accept(int, SA *, socklen_t *);
void Bind(int, const SA *, socklen_t);
void Connect(int, const SA *, socklen_t);
void Getpeername(int, SA *, socklen_t *);
void Getsockname(int, SA *, socklen_t *);
void Getsockopt(int, int, int, void *, socklen_t *);
void Listen(int, int);
int Socket(int, int, int);
int Select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
void Shutdown(int, int);
ssize_t Recv(int, void *, size_t, int);
ssize_t Recvfrom(int, void *, size_t, int, struct sockaddr *, socklen_t *);
void Send(int, const void *, size_t , int );
void Sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
void Setsockopt(int, int, int, const void *, socklen_t);
int Kqueue(void);

struct kevent; // forward declaration
int Kevent(int, const struct kevent *, int, struct kevent *, int, const struct timespec *);

#endif //UNP_PROJ_WRAPSOCK_H
