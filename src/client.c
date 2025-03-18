#include "client.h"

/* TO SEE SOCKET SENDING STEP
 * READ "server.c" ON SERVER REPO
*/
void handler(int sock)
{
    printf("Waiting for other player\n");

    // we receive connection
    {
        meta_t recv_packet;
        meta_t send_packet = {.type = 0xFF, .size = 0};
        recv(sock, &recv_packet, sizeof(meta_t), 0);
        if(recv_packet.type == 0x01)
           printf("Ennemy found\n");
        send(sock, &send_packet, sizeof(meta_t), 0);
    }


    // we receive our base decks cards
    {
        meta_t size_info;
        meta_t callback = (meta_t) {.type = 0xFF};
        recv(sock, &size_info, sizeof(meta_t), 0);
        send(sock, &callback, sizeof(meta_t), 0);

        for(size_t i = 0; i < size_info.size; ++i)
        {
            card_t* card = (card_t*) malloc(sizeof(card_t));
            recv(sock, card, sizeof(card_t), 0);
            printf("CARD RECEIVED : %d\n", card->rarity);
            send(sock, &callback, sizeof(meta_t), 0);
        }
    }
}
