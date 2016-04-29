//
// Created by ZhuJiahao on 4/6/16.
//

#ifndef UNP_PROJ_SIGNAL_WRAP_H
#define UNP_PROJ_SIGNAL_WRAP_H

// for Signal(...)
typedef void Sigfunc(int);
Sigfunc *Signal(int signo, Sigfunc *func);

#endif //UNP_PROJ_SIGNAL_WRAP_H
