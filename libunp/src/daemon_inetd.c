//
// Created by ZhuJiahao on 4/14/16.
//
#include <syslog.h>

extern int daemon_proc; // defined in error.c

void daemon_inetd(const char *pname, int facility) {
    daemon_proc = 1;
    openlog(pname, LOG_PID, facility);
}


