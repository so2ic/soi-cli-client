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
    if(selected == -1) {printf("\n-> End turn\n");}
    else {printf("\n   End turn\n");}

    if(selected == -2) {printf("-> %sIncrease mastery (1 mana)\n",p->mana == 0 ? KRED : KGRN);}
    else {printf("   %sIncrease mastery (1 mana)\n",p->mana == 0 ? KRED : KGRN);}
    printf("%s", KNRM);

    if(selected == -3) {printf("-> Deal damage\n");}
    else {printf("   Deal damage\n");}
}
 
void damage_picker_menu(player_t* p, int selected)
{
    clear_screen();

    printf("Use 'q' and 'd' to choose how many damage you want to deal\n'Enter' to select\nAnything else to go back.\n\n");

    display_player(p);

    printf("%s< %d > (max %d)\n%s", KRED, selected, p->power, KNRM);
}


void card_info_menu(player_t* p, card_t* card)
{
    clear_screen();
    printf("'Enter' to play card, any key to go back.\n\n");

    display_player(p);

    display_card_info(card);
}

return_t* interface_handler(player_t* player, ll_t* hand, int is_playing)
{
    int selected = 0, damage = 0;
    int is_info = 0, is_damage = 0;
    char c;
    return_t ret;
    
    if(!is_playing)
        card_menu(player, hand, selected);
    else
    {
        while(1)
        {
            if(is_info)
            {
                card_info_menu(player, ll_get_data_at(hand, selected));

                c = getchar();

                if(c == '\n')
                {
                    ret.type = (RETURN_TYPE) CARD;
                    ret.card = ll_get_data_at(hand, selected); 
                    return &ret;
                }
                else
                    is_info = 0;

                continue;
            }
            else if(is_damage)
            {
                damage_picker_menu(player, damage);

                c = getchar();

                if(c == 'q' && damage > 0)
                {
                    damage--;
                    continue; 
                }
                else if(c == 'd' && damage < player->power)
                {
                    damage++;
                    continue; 
                }
                else if(c == '\n')
                {
                    ret.type = (RETURN_TYPE) DAMAGE; 
                    ret.card = NULL;
                    ret.value = damage;
                    return &ret;
                }
                else
                    is_damage = 0;

                continue;
            }
            else
            {
                card_menu(player, hand, selected);
                c = getchar();

                if(c == 's')
                {
                    if(selected < ll_get_size(hand) - 1 && selected >= 0) {++selected;}
                    else if(selected <= -1 && selected > -3) {--selected;}
                    else {selected = -1;}
                }
                if(c == 'z')
                {
                    if(selected < 0) {++selected;}
                    else if(selected > 0) {--selected;}
                    else {selected = ll_get_size(hand) - 1;}
                }
                if(c == '\n')
                {
                    if(selected == -1) 
                    {
                        ret.type = (RETURN_TYPE) END_TURN;
                        ret.card = NULL;
                        return &ret;
                    }
                    else if(selected == -2)
                    {
                        ret.type = (RETURN_TYPE) MASTERY;
                        ret.card = NULL;
                        return &ret;
                    }
                    else if(selected == -3)
                    {
                        is_damage = 1;
                        continue;
                    }
                    else 
                    {
                        is_info = 1;
                        continue;
                    }
                }
            }
        }  
    }
}
