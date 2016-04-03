//
// Created by Neptune on 4/2/16.
//

#ifndef UNP_PROJ_WRAPUNIX_H
#define UNP_PROJ_WRAPUNIX_H

ssize_t Read(int, void *, size_t);
void Write(int, void *, size_t);
void Close(int);

#endif //UNP_PROJ_WRAPUNIX_H
