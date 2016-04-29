//
// Created by Neptune on 4/2/16.
//

#ifndef UNP_PROJ_WRAPUNIX_H
#define UNP_PROJ_WRAPUNIX_H

pid_t Fork(void);
ssize_t Read(int, void *, size_t);
void Write(int, void *, size_t);
void Close(int);
void *Malloc(size_t);
pid_t Waitpid(pid_t, int *, int);

#endif //UNP_PROJ_WRAPUNIX_H
