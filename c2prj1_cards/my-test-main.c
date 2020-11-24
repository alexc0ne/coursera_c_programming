#include <stdio.h>
#include <stdlib.h>
#include "cards.h"

int main(void)
{   
    print_card(card_from_letters('0', 's'));
    printf("\n");
    print_card(card_from_letters('0', 'h'));
    printf("\n");
    print_card(card_from_letters('0', 'd'));
    printf("\n");
    print_card(card_from_letters('0', 'c'));
    printf("\n");
    
    return EXIT_SUCCESS;
}
