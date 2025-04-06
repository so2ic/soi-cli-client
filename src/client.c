#include "client.h"

/* TO SEE SOCKET SENDING STEP
 * READ "server.c" ON SERVER REPO
*/
void handler(int sock)
{
    player_t player = (player_t) {.hp = 0, .mana = 0, .power = 0, .mastery = 0};
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
        enable_raw_mode();
        ll_t* hand = ll_init();
        int is_game_running = 1;
        
        do
        {
            meta_t received;
            meta_t callback = (meta_t) {.type = 0xFF, .size = 0};

            interface_handler(&player, hand, 0);

            recv(sock, &received, sizeof(meta_t), 0);

            if(received.type == 0x03)
            {
                send(sock, &callback, sizeof(meta_t), 0);
                receive_card(sock, hand);
                bzero(&received, sizeof(meta_t));
            }
            else if(received.type == 0x02)
            {
                send(sock, &callback, sizeof(meta_t), 0);
                meta_t send_packet = {.type = 0x03, .size = 0};

                return_t* out = interface_handler(&player, hand, 1);
                bzero(&received, sizeof(meta_t));

                if(out->type == (RETURN_TYPE) CARD)
                {
                    card_t* played_card = out->card; 
                    send(sock, &send_packet, sizeof(meta_t), 0);
                    recv(sock, &received, sizeof(meta_t), 0);

                    if(received.type != 0xFF)
                    {
                        // TODO
                        // Handle errors 
                        perror("error while sending card to server");
                        exit(errno);
                    }
                    
                    bzero(&received, sizeof(meta_t));
                    send(sock, &(played_card->id), sizeof(int), 0);
                    recv(sock, &received, sizeof(meta_t), 0);

                    if(received.type != 0xFF)
                    {
                        // TODO
                        // Handle errors
                        perror("error while sending card id to server"); 
                        exit(errno);
                    } 
                }
                else if(out->type == (RETURN_TYPE) MASTERY)
                {
                    send_packet.type = 0x0C;

                    send(sock, &send_packet, sizeof(meta_t), 0);
                    recv(sock, &received, sizeof(meta_t), 0);

                    if(received.type != 0xFF)
                    {
                        perror("error while upgrading mastery");
                        exit(errno);
                    }
                }
                else if(out->type == (RETURN_TYPE) DAMAGE)
                {
                    send_packet.type = 0x0D;
                    send_packet.size = (size_t) out->value;

                    send(sock, &send_packet, sizeof(meta_t), 0);
                    recv(sock, &received, sizeof(meta_t), 0);

                    if(received.type != 0xFF)
                    {
                        perror("error while dealing damage");
                        exit(errno);
                    }
                }
                else
                {
                    send_packet.type = 0x0B;

                    send(sock, &send_packet, sizeof(meta_t), 0);
                    recv(sock, &received, sizeof(meta_t), 0);

                    if(received.type != 0xFF)
                    {
                        perror("error while sending end of turn");
                        exit(errno);
                    }
                }
            }
            else if(received.type == 0x05)
            {
                meta_t callback = {.type = 0xFF, .size = 0};
                player.hp = (int) received.size;
                bzero(&received, sizeof(meta_t));
                send(sock, &callback, sizeof(meta_t), 0);
            }
            else if(received.type == 0x06)
            {
                meta_t callback = {.type = 0xFF, .size = 0};
                player.mana = (int) received.size;
                bzero(&received, sizeof(meta_t));
                send(sock, &callback, sizeof(meta_t), 0);
            }
            else if(received.type == 0x07)
            {
                meta_t callback = {.type = 0xFF, .size = 0};
                player.power = (int) received.size;
                send(sock, &callback, sizeof(meta_t), 0);
                bzero(&received, sizeof(meta_t));
            }
            else if(received.type == 0x08)
            {
                meta_t callback = {.type = 0xFF, .size = 0};
                player.mastery = (int) received.size;
                send(sock, &callback, sizeof(meta_t), 0);
                bzero(&received, sizeof(meta_t));
            }
            // for second player so he can see his hand
            else if(received.type == 0x09)
            {
                
            }
            else if(received.type == 0x0A)
            {
                meta_t callback = {.type = 0xFF, .size = 0};
                int err = ll_remove_at(hand, received.size);
                if(err)
                    callback.type = 0xFE;
                send(sock, &callback, sizeof(meta_t), 0);
                bzero(&received, sizeof(meta_t));
            }
            else
            {
                //printf("SHOULD NOT GO HERE\n");
                //printf("BECAUSE OF : %hhu\n", received.type);
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
*/
void receive_card(int sock, ll_t* deck)
{
    meta_t received;
    meta_t callback = (meta_t) {.type = 0xFF, .size = 0};
    card_t* card = (card_t*) malloc(sizeof(card_t));

    /*
    recv(sock, card, sizeof(card_t), 0);
    send(sock, &callback, sizeof(meta_t), 0);
    */

    recv(sock, &received, sizeof(meta_t), 0);
    if(received.type != 0x09)
        callback.type = 0xFE;
    card->id = (int) received.size;
    send(sock, &callback, sizeof(meta_t), 0);

    recv(sock, &received, sizeof(meta_t), 0);
    if(received.type != 0x04)
        callback.type = 0xFE;
    card->name = malloc(received.size);
    send(sock, &callback, sizeof(meta_t), 0);

    recv(sock, card->name, received.size, 0);
    send(sock, &callback, sizeof(meta_t), 0);

    ll_insert(deck, card);
}
