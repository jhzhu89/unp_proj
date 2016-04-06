//
// Created by ZhuJiahao on 4/5/16.
//

#ifndef UNP_PROJ_WRAPSTDIO_H
#define UNP_PROJ_WRAPSTDIO_H

FILE * Fopen(const char*, const char*);
void Fclose(FILE *);
char * Fgets(char *, int, FILE*);
void Fputs(const char *ptr, FILE *stream);
FILE * fdopen(int fd, const char* type);

#endif //UNP_PROJ_WRAPSTDIO_H
