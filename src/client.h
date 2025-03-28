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
#include <stdlib.h>

#include "packet.h"
#include "card.h"
#include "data_structures/ll.h"
#include "player.h"
#include "interface.h"

void handler(int sock);
void receive_card(int sock, ll_t* deck);

#endif // CLIENT_H
