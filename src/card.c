#include "card.h"

char* get_card_color(CARD_CLASS class)
{
    if(class == (CARD_CLASS) BASE_DECK)
        return KNRM;
    if(class == (CARD_CLASS) ORDER)
        return KCYN;
    if(class == (CARD_CLASS) WRAETHE)
        return KMAG;
    if(class == (CARD_CLASS) UNDERGROWTH)
        return KGRN;
    if(class == (CARD_CLASS) HOMODEUS)
        return KYEL;

    return KNRM;
}

char* display_card(card_t* card)
{
    char* out = malloc(strlen(get_card_color(card->class)) + strlen(card->name)); 
    strcpy(out, get_card_color(card->class));
    strcat(out, card->name);
    return out;
}

void display_card_info(card_t* card)
{
    char* color = get_card_color(card->class);
    printf("\n==========CARD==========\n");
    printf("%sNAME : %s\nID : %d\n", color, card->name, 1);
    /*
    if(card->mana != 0)
        printf("%sMANA : %d\n", color, card->mana);
    if(card->power != 0)
        printf("%sPOWER : %d\n", color, card->power);
    if(card->draw != 0)
        printf("%sDRAW : %d\n", color, card->draw);
    if(card->rarity != 0)
        printf("%sRARITY : %d\n", color, card->rarity);
    printf("%sCARD_TYPE : %s\n", color, get_card_type_string(card->type));
    printf("%sCARD_CLASS: %s\n", color, get_card_class_string(card->class));
    */
    printf("=========================\n\n");
}

char* get_card_type_string(CARD_TYPE type)
{
    if(type == (CARD_TYPE) ALLIES)
        return "ALLIES";
    if(type == (CARD_TYPE) MERCENARIES)
        return "MERCENARIES";
    if(type == (CARD_TYPE) CHAMPION)
        return "CHAMPION";

    return "UNKNOWN";
}

char* get_card_class_string(CARD_CLASS class)
{
    if(class == (CARD_CLASS) BASE_DECK)
        return "BASE_DECK";
    if(class == (CARD_CLASS) ORDER)
        return "ORDER";
    if(class == (CARD_CLASS) WRAETHE)
        return "WRAETHE";
    if(class == (CARD_CLASS) UNDERGROWTH)
        return "UNDERGROWTH";
    if(class == (CARD_CLASS) HOMODEUS)
        return "HOMODEUS";

    return "UNKNOWN";
}
