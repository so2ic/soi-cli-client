#include "client.h"

/* TO SEE SOCKET SENDING STEP
 * READ "server.c" ON SERVER REPO
*/
void handler(int sock)
{
    printf("Waiting for other player\n");

    {
        meta_t packet;
        recv(sock, &packet, sizeof(meta_t), 0);
        if(packet.type == 0x01)
           printf("Ennemy found\n");
    }
}
