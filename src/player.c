#include "player.h"

void display_player(player_t* p)
{
    printf("%sHP : %d ", KGRN, p->hp);
    printf("%sMANA : %d ", KBLU, p->mana);
    printf("%sPOWER : %d ", KRED, p->power);
    printf("%sMASTERY : %d\n", KYEL, p->mastery);
}

