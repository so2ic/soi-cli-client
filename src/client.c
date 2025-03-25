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
        ll_t* deck = ll_init();
        int is_game_running = 1;
        do
        {
            meta_t received;
            meta_t callback = (meta_t) {.type = 0xFF, .size = 0};
            system("clear");
            display_player(&player);
            for(int i = 0; i < deck->count; ++i)
            {
                printf("[%d] -> ", i); 
                display_card((card_t*) ll_get_data_at(deck, i));
            }
            recv(sock, &received, sizeof(meta_t), 0);

            if(received.type == 0x03)
            {
                send(sock, &callback, sizeof(meta_t), 0);
                receive_card(sock, deck);
            }
            else if(received.type == 0x02)
            {
                int is_running = 1;
                do
                {
                    int choice;
                    int card_place;
                    printf("You have to play\nDo you wanna :\n1 - Get info on a card\n2 - Play a card\nYour choice : "); 
                    scanf("%d", &choice);
                    printf("Select the card you want to %s\nYour choice : ", (choice == 1) ? "inspect" : "play");
                    scanf("%d", &card_place);
                    if(choice == 1)
                        display_card_info(ll_get_data_at(deck, card_place));
                    else if(choice == 2)
                        is_running = 0;
 
                }
                while(is_running);
            }
            else if(received.type == 0x05)
            {
                meta_t callback = {.type = 0xFF, .size = 0};
                player.hp = (int) received.size;
                send(sock, &callback, sizeof(meta_t), 0);
            }
            else if(received.type == 0x06)
            {
                meta_t callback = {.type = 0xFF, .size = 0};
                player.mana = (int) received.size;
                send(sock, &callback, sizeof(meta_t), 0);
            }
            else if(received.type == 0x07)
            {
                meta_t callback = {.type = 0xFF, .size = 0};
                player.power = (int) received.size;
                send(sock, &callback, sizeof(meta_t), 0);
            }
            else if(received.type == 0x08)
            {
                meta_t callback = {.type = 0xFF, .size = 0};
                player.mastery = (int) received.size;
                send(sock, &callback, sizeof(meta_t), 0);
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
*/
void receive_card(int sock, ll_t* deck)
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

    recv(sock, card->name, received.size, 0);
    send(sock, &callback, sizeof(meta_t), 0);

    ll_insert(deck, card);
}
