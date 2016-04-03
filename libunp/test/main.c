#include <stdio.h>
#include "../include/error.h"
#include <unp.h>

//
// Created by Neptune on 4/2/16.
//
int main() {
    printf("this is a test\n");
    err_msg("this is another test\n");
    char buf[MAXLINE];
    bzero(buf, MAXLINE);
    int n = Read(fileno(stdin), buf, MAXLINE);
    printf("%s\n", buf);
}
