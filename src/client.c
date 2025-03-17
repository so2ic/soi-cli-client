#include "client.h"

/* TO SEE SOCKET SENDING STEP
 * READ "server.c" ON SERVER REPO
*/
void handler(int sock)
{
    printf("Waiting for other player\n");

    {
        meta_t recv_packet;
        meta_t send_packet = {.type = 0xFF, .size = 0};
        recv(sock, &recv_packet, sizeof(meta_t), 0);
        if(recv_packet.type == 0x01)
           printf("Ennemy found\n");
        send(sock, &send_packet, sizeof(meta_t), 0);
    }
}
