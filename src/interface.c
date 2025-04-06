#include "interface.h"

void enable_raw_mode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Disable line buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void disable_raw_mode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void clear_screen() {
    printf("\033[2J\033[H");
}

void card_menu(player_t* p, ll_t* hand, int selected) {
    clear_screen();
    printf("Use 'z' and 's' to navigate, 'Enter' to select.\n\n");

    display_player(p);

    for (int i = 0; i < ll_get_size(hand); i++) {
        if (i == selected) 
            printf("-> %s\n", display_card(ll_get_data_at(hand, i)));
        else 
            printf("   %s\n", display_card(ll_get_data_at(hand, i)));
    }
}
 
void card_info_menu(player_t* p, card_t* card)
{
    clear_screen();
    printf("'Enter' to play card, any key to go back.\n\n");

    display_player(p);

    display_card_info(card);
}

card_t* interface_handler(player_t* player, ll_t* hand, int is_playing)
{
    int selected = 0;
    int is_info = 0;
    char c;
    
    if(!is_playing)
        card_menu(player, hand, selected);
    else
    {
        while(1)
        {
            if(!is_info)
            {
                card_menu(player, hand, selected);
                c = getchar();

                if(c == 's')
                    if(selected < ll_get_size(hand) - 1)
                        ++selected;
                if(c == 'z')
                    if(selected > 0)
                        --selected;
                if(c == '\n')
                    is_info = 1;
            }
            else
            {
                card_info_menu(player, ll_get_data_at(hand, selected));

                c = getchar();

                if(c == '\n')
                    return ll_get_data_at(hand, selected);
                else
                    is_info = 0;
            }
        }  
    }
}
