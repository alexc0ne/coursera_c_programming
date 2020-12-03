#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
#include <time.h>

int equals(card_t a, card_t b)
{ 
    char a_value = value_letter(a);
    char a_suit = suit_letter(a);

    char b_value = value_letter(b);
    char b_suit = suit_letter(b);
    
    if (a_value == b_value && a_suit == b_suit) return 1;
    return 0;
}

/*
 - void print_hand(deck_t * hand); 
   This should print out the contents of a hand.
   It should print each card (recall that
   you wrote print_card in Course 2), and
   a space after each card.  Do not put
   a newline after the hand, as this
   function gets called to print a hand
   in the middle of a line of output.
*/

void print_hand(deck_t * hand)
{   
    size_t n = hand->n_cards;
    if (n == 0) return;

    card_t ** arr = hand->cards;
    int i = 0;
    for ( ; i + 1 < n; ++i)
    {
        print_card(*arr[i]);
        printf(" ");
    }

    print_card(*arr[i]);
}

/*
 - int deck_contains(deck_t * d, card_t c);
   This function should check if a deck
   contains a particular card or not.  If
   the deck does contain the card, this
   function should return 1.  Otherwise,
   it should return 0.
   (You will use this later to
   build the deck of remaining cards
   which are not in any player's hand).
*/
int deck_contains(deck_t * d, card_t c)
{
    size_t n = d->n_cards;
    if (n == 0) return 0;

    card_t ** arr = d->cards;
    card_t arr_i;
    for (int i = 0; i < n; ++i)
    {
        arr_i = *arr[i];
        if (equals(arr_i, c)) return 1;
    }

    return 0;
}

/*
 - void shuffle(deck_t * d);
   This function takes in a deck an shuffles
   it, randomly permuting the order of the cards.
   There are MANY valid ways to shuffle a deck
   of cards---we'll leave the specifics
   of the algorithm design up to you.  However,
   you will want to use random() to generate
   pseudo-random numbers.  (Pseudo-random
   numbers are quite sufficient here,
   since they are not used for security
   purposes). Note that you should not need to
   use the 'srand' function.

   We will note that in trying to devise
   this algorithm, you should not
   try to shuffle a deck of cards "normally".
   Instead, you should take a small number
   of cards, and think about ways
   to shuffle them that involve using
   random numbers to swap their order,
   or pick positions for them, or
   similar principles.
*/
void shuffle(deck_t * d)
{
    // generating a new array of random numbers
    size_t n = d->n_cards;
    card_t ** arr = d->cards;
    
    int guide[n];
    int r;
    for (int i = 0; i < n; ++i)
    {
        r = random();
        guide[i] = r % 53;
    }

    card_t tmp;
    for (int i = 0; i + 1 < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (guide[i] > guide[j])
            {
                tmp = *arr[i];
                *arr[i] = *arr[j];
                *arr[j] = tmp;
            }
}

/*
- void assert_full_deck(deck_t * d);
  This function should check that
  the passed in deck contains ever
  valid card exactly once.  If
  the deck has any problems, this function
  should fail an assert.  This will
  be used to help you test your deck
  shuffling: we will shuffle
  a full deck, then call assert_full_deck,
  so that you can identfiy problems with
  the deck.  You can print
  any error messages you want
  if there is a problem.
  Hint: you already wrote deck_contains.
*/
void assert_full_deck(deck_t * d)
{
    size_t n = d->n_cards;
    if (n == 0 || n == 1) return;

    card_t ** arr = d->cards;
    for (int i = 0; i + 1 < n; ++i)
        for (int j = i + 1; j < n; ++j)
            assert(!equals(*arr[i], *arr[j]));
}

