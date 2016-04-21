//
// Created by Neptune on 4/2/16.
//

#ifndef UNP_PROJ_COMMON_H
#define UNP_PROJ_COMMON_H

/* If anything changes in the following list of #includes, must change
   acsite.m4 also, for configure's tests. */

#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */

#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/un.h>		/* for Unix domain sockets */
#include    <poll.h>
#include    <sys/event.h>   /* for kevent */

//#include    <netinet/sctp.h>
#include    <netinet/in.h>  /* after OSX Lion, IPROTO_SCTP is defined in this header */

#ifndef INFTIM
#define INFTIM (-1)
#endif

#endif //UNP_PROJ_COMMON_H
