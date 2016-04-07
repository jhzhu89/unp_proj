//
// Created by ZhuJiahao on 4/6/16.
//

#include <signal.h>
#include "../include/defs.h"
#include "../include/error.h"
#include "../include/signal_wrap.h"

Sigfunc* Signal(int signo, Sigfunc* func) {
    Sigfunc* sigfunc;

    if ((sigfunc = signal(signo, func)) == SIG_ERR)
        err_sys("signal error");

    return sigfunc;
}

