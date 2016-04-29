//
// Created by Neptune on 4/2/16.
//

#include <stdarg.h>
#include <syslog.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "../include/error.h"
#include "../include/defs.h"

int daemon_proc; /* set nonzero by daemon_init() */

// Nonfatal error related to system call
// Print mesage and return

static void err_doit(int errnoflag, int level, const char *fmt, va_list ap);

void err_ret(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, LOG_INFO, fmt, ap);
    va_end(ap);
    return;
}

// Fatal error related to system call
// Print message and terminate

void err_sys(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);
}

// Fatal error related to system call
// Print message, dump core, and terminate

void err_dump(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    abort();     // dump core and terminate
    exit(1);     // shouldn't get here
}

// Nonfatal error unrelated to system call
// Print message and return

void err_msg(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, LOG_INFO, fmt, ap);
    va_end(ap);
    return;
}

// Fatal error unrelated to system call
// Print mesasge and terminate

void err_quit(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);
}

// Print mesage and return to caller
// Caller specifies "errnoflag" and "level"

void static err_doit(int errnoflag, int level, const char *fmt, va_list ap) {
    char buf[MAXLINE + 1];
    int errno_save = errno;  // value caller might want printed
    #ifdef HAVE_VSNPRINTF
    vsnprintf(buf, MAXLINE, fmt, ap);  // safe
    #else
    vsprintf(buf, fmt, ap);  // not safe
    #endif
    int n = strlen(buf);

    if (errnoflag)
        snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));

    strcat(buf, "\n");

    if (daemon_proc)
        syslog(level, buf);
    else {
        fflush(stdout); // in case stdout and stderr are the same
        fputs(buf, stderr);
        fflush(stderr);
    }

    return;
}
