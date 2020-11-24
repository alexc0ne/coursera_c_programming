#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"



void assert_card_valid(card_t c)
{
    assert(c.value >= 2 && c.value <= VALUE_ACE);
    assert(c.suit >= SPADES && c.suit <= CLUBS);
}



const char * ranking_to_string(hand_ranking_t r)
{
    switch (r)
    {
        case STRAIGHT_FLUSH:
            return "STRAIGHT_FLUSH";
        case FOUR_OF_A_KIND:
            return "FOUR_OF_A_KIND";
        case FULL_HOUSE:
            return "FULL_HOUSE";
        case FLUSH:
            return "FLUSH";
        case STRAIGHT:
            return "STRAIGHT";
        case THREE_OF_A_KIND:
            return "THREE_OF_A_KIND";
        case TWO_PAIR:
            return "TWO_PAIR";
        case PAIR:
            return "PAIR";
        case NOTHING:
            return "NOTHING";
    }
    return "We'll never reach this line";
}



char value_letter(card_t c)
{
    unsigned value = c.value;

    if (value >= 2 && value <= 9)
        return '0' + value;
    
    if (value == 10)
        return '0';

    switch (value)
    {
        case 11:
            return 'J';
        case 12:
            return 'Q';
        case 13:
            return 'K';
        case 14:
            return 'A';
    }
    return '0';
}



char suit_letter(card_t c)
{
    switch (c.suit)
    {
        case SPADES:
            return 's';
        case HEARTS:
            return 'h';
        case DIAMONDS:
            return 'd';
        case CLUBS:
            return 'c'; 
        case NUM_SUITS:
            return 'n';
    }
    return '0';
}



void print_card(card_t c)
{
    printf("%c%c", value_letter(c), suit_letter(c));
}



card_t card_from_letters(char value_let, char suit_let)
{
    card_t temp;
   
    int check = 0;
    if (suit_let == 's' || suit_let == 'h' || suit_let == 'd' || suit_let == 'c')
        check = 1;

    assert(check);
   
    check = 0;
    if (value_let == '0' || (value_let >= '2' && value_let <= '9') ||
        value_let == 'J' || value_let == 'Q' || value_let == 'K' ||
        value_let == 'A')
        check = 1;

    assert(check);

    //
    if (value_let == '0')
        temp.value = 10;

    if (value_let >= '2' && value_let <= '9')
        temp.value = value_let - '0';
    
    switch (value_let)
    {
        case 'J':
            temp.value = 11;
            break;
        case 'Q':
            temp.value = 12;
            break;
        case 'K':
            temp.value = 13;
            break;
        case 'A':
            temp.value = 14;
    }
    
    //
    switch (suit_let)
    {
        case 's':
            temp.suit = SPADES;
            break;
        case 'h':
            temp.suit = HEARTS;
            break;
        case 'd':
            temp.suit = DIAMONDS;
            break;
        case 'c':
            temp.suit = CLUBS;
    }

    return temp;
}



card_t card_from_num(unsigned c)
{
    assert(c >= 0 && c <= 51);
    card_t temp;
    
    //
    temp.value = c % 13 + 2;
    
    //
    if (c >= 0 && c <= 12)
        temp.suit = SPADES;
    else if (c >= 13 && c <= 25)
        temp.suit = HEARTS;
    else if (c >= 26 && c <= 38)
        temp.suit = DIAMONDS;
    else
        temp.suit = CLUBS;

    return temp;
}
