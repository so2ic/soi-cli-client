#ifndef CARD_H
#define CARD_H

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

typedef enum CARD_TYPE
{
    ALLIES,
    MERCENARIES,
    CHAMPION,
} CARD_TYPE;

typedef enum CARD_CLASS
{
    BASE_DECK, // for base decks
    ORDER,
    WRAETHE,
    UNDERGROWTH,
    HOMODEUS,
} CARD_CLASS;

typedef struct card_t 
{
    char* name;
    int id, mana, power, draw, rarity;
    CARD_TYPE type;
    CARD_CLASS class;
} card_t;

char* get_card_color(CARD_CLASS class);
char* get_card_type_string(CARD_TYPE type);
char* get_card_class_string(CARD_CLASS class);
void display_card_info(card_t* card);
void display_card(card_t* card);

#endif // CARD_H
