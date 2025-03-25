#ifndef PLAYER_H
#define PLAYER_H

#ifndef KNRM  
#define KNRM  "\x1B[0m"
#endif
#ifndef KRED  
#define KRED  "\x1B[31m"
#endif
#ifndef KGRN  
#define KGRN  "\x1B[32m"
#endif
#ifndef KYEL  
#define KYEL  "\x1B[33m"
#endif
#ifndef KBLU  
#define KBLU  "\x1B[34m"
#endif
#ifndef KMAG  
#define KMAG  "\x1B[35m"
#endif
#ifndef KCYN  
#define KCYN  "\x1B[36m"
#endif
#ifndef KWHT  
#define KWHT  "\x1B[37m"
#endif

#include <stdio.h>

typedef struct
{
    int hp, mana, power, mastery;
} player_t;

void display_player(player_t *p);

#endif // PLAYER_H
