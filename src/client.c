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

    // game loop
    {
        int is_game_running = 1;
        do
        {
            meta_t received;
            meta_t callback = (meta_t) {.type = 0xFF, .size = 0};
            printf("waiting for packet\n");
            recv(sock, &received, sizeof(meta_t), 0);

            if(received.type == 0x03)
            {
                send(sock, &callback, sizeof(meta_t), 0);
                receive_card(sock);
            }
            else
            {
                callback.type = 0xFE;
                send(sock, &callback, sizeof(meta_t), 0);
            }
        }
        while(is_game_running);
    }
}

/*
 * CARD RECEPTION PROCESS
 * receive the card
 * receive card name size
 * allocate the card name size
 * receive the card name
 * receive card 
*/
void receive_card(int sock)
{
    meta_t received;
    meta_t callback = (meta_t) {.type = 0xFF, .size = 0};
    card_t* card = (card_t*) malloc(sizeof(card_t));

    recv(sock, card, sizeof(card_t), 0);
    send(sock, &callback, sizeof(meta_t), 0);

    recv(sock, &received, sizeof(meta_t), 0);
    if(received.type != 0x04)
        callback.type = 0xFE;
    send(sock, &callback, sizeof(meta_t), 0);

    printf("%zu\n", received.size);
    char* buf = malloc(received.size);
    recv(sock, buf, received.size, 0);
    send(sock, &callback, sizeof(meta_t), 0);

    printf("CARD RECEIVED : %s\n", buf);
}
