//
// Created by Neptune on 4/9/16.
//

#ifndef UNP_PROJ_HOST_SERV_H
#define UNP_PROJ_HOST_SERV_H

struct addrinfo *host_serv(const char *hostname, const char *service, int family, int socktype);

#endif //UNP_PROJ_HOST_SERV_H
