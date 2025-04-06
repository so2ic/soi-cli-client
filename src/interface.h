#ifndef INTERFACE_H
#define INTERFACE_H

#include <termios.h>
#include <stdio.h>
#include <unistd.h>

#include "card.h"
#include "player.h"
#include "data_structures/ll.h"

void enable_raw_mode();
void disable_raw_mode();
void clear_screen();
void card_menu(player_t* p, ll_t* hand, int selected);
void card_info_menu(player_t* p, card_t* card);
card_t* interface_handler(player_t* player, ll_t* hand, int is_playing);

#endif // INTERFACE_H
