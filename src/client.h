#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#include "packet.h"

void handler(int sock);

#endif // CLIENT_H
