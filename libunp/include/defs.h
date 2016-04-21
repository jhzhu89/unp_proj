//
// Created by Neptune on 4/2/16.
//

#ifndef UNP_PROJ_DEFS_H
#define UNP_PROJ_DEFS_H

#define MAXLINE 4096 // max text line length
#define BUFFSIZE 8192 //buffer size for reads and writes

#define SERV_PORT 9877
#define LISTENQ 1024

#define max(a, b) ((a > b) ? a : b)

#define UNIXSTR_PATH  "/tmp/unix.str" // Unix domain stream
#define UNIXDG_PATH  "/tmp/unix.dg"  // Unix domain datagram

#endif //UNP_PROJ_DEFS_H
