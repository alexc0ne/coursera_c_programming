#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 - int card_ptr_comp(const void * vp1, const void * vp2) 
    You want to sort the hand by value, so you need
    a comparison function to pass to quicksort.
    Quicksort sorts into ascending order, but you
    want descending order, so you will want to
    return
       something < 0  if card1 > card2
       0              if card1 == card2
       something > 0  if card1 < card2
    If two cards have the same value, compare them by
    suit in the same order as the enum suit_t:
       club < diamond < heart < spade
    Note that vp1 and vp2 are passed as const void *
    because that is the type that qsort demands.
    They will should each be assigned to variables
    of type
     const card_t * const * cp1
    before using them (this is much like sorting
    an array of strings from your readings).
    To learn more about using the C library function qsort,
    we suggest reviewing the course reading
    "Sorting Functions" in the "Function Pointers"
    lesson and consulting "man qsort"
    to read about the comparison function.
*/
int card_ptr_comp(const void * vp1, const void * vp2)
{
    const card_t * const * cp1 = vp1;
    const card_t * const * cp2 = vp2;
    
    const card_t * p1 = *cp1;
    const card_t * p2 = *cp2;

    if (p1->value < p2->value) return 1;
    if (p1->value > p2->value) return -1;
    if (p1->value == p2->value)
    {
        if (p1->suit == p2->suit) return 0;
        else if (p1->suit < p2->suit) return -1;
    }

    return -1; 
}


/*
 - suit_t flush_suit(deck_t * hand);
   This function looks at the hand and determines
   if a flush (at least 5 cards of one suit) exists.
   If so, it returns the suit of the cards comprising
   the flush.  If not, it returns NUM_SUITS.
   For example:
    Given Ks Qs 0s 9h 8s 7s, it would return SPADES.  
    Given Kd Qd 0s 9h 8c 7c, it would return NUM_SUITS.
*/
suit_t flush_suit(deck_t * hand)
{
    size_t n = hand->n_cards;
    card_t ** arr = hand->cards;

    int spades = 0;
    int hearts = 0;
    int diamonds = 0;
    int clubs = 0;

    for (int i = 0; i < n; ++i)
    {
        switch((arr[i]->suit))
        {
            case SPADES:
                ++spades;
                break;

            case HEARTS:
                ++hearts;
                break;

            case DIAMONDS:
                ++diamonds;
                break;

            case CLUBS:
                ++clubs;
                break;
            
            case NUM_SUITS:
                break;
        }
    }

    if (spades >= 5) return SPADES;
    if (hearts >= 5) return HEARTS;
    if (diamonds >= 5) return DIAMONDS;
    if (clubs >= 5) return CLUBS;

    return NUM_SUITS;
}


/*
 - unsigned get_largest_element(unsigned * arr, size_t n);
   This function returns the largest element in an array
   of unsigned integers.  This should be familiar
   from the videos you watched.
   
   In course 4 (after you learn to dynamically allocate
   memory), you will write get_match_counts,
   which will construct an array with one element
   per card in the hand.  That array will
   tell you how many cards in the hand
   have the same value as the corresponding
   card.  You will then use get_largest_element
   to figure out which is the best "N of a kind".
*/
unsigned get_largest_element(unsigned * arr, size_t n)
{
    unsigned max = arr[0];
    for (int i = 0; i < n; ++i)
        if (arr[i] > max)
            max = arr[i];

    return max;
}


/*
 - size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind);
   This function returns the index in the array (match_counts) whose
   value is n_of_akind.  The array has n elements.  The array match_counts
   may have multiple values equal to n_of_akind.  You should return
   the LOWEST index whose value is n_of_akind [which also guarantees
   it corresponds to the largest valued cards, since they will be sorted].
   (Once you figure out the best n_of_akind above,
    you will use this to locate that group of cards
    in the hand).
    Note that it is guaranteed that n_of_akind is in match_counts.
    If not, you should abort as this is evidence of an error.
*/
size_t get_match_index(unsigned * match_counts, size_t n, unsigned n_of_akind)
{
    for (size_t i = 0; i < n; ++i)
        if (match_counts[i] == n_of_akind)
            return i;

    exit(EXIT_FAILURE);
}


/*
 - size_t  find_secondary_pair(deck_t * hand, unsigned * match_counts, size_t match_idx) ;
   When you have a hand with 3 of a kind or a pair,
   you will want to look and see if there is another
   pair to make the hand into a full house or
   or two pairs.  This function takes in
   the hand, the match counts from before, and
   the index where the original match (3 of a kind
   or pair) was found. It should find
   the index of a card meeting the following conditions:
     - Its match count is > 1 [so there is at least a pair of them]
     - The card's value is not the same as the value of the
       card at match_idx (so it is not part of the original
       three of a kind/pair)
     - It is the lowest index meeting the first two conditions
       (which will be the start of that pair, and the highest
        value pair other than the original match).
   If no such index can be found, this function should
   return -1.
*/
size_t find_secondary_pair(deck_t * hand, unsigned * match_counts, size_t match_idx)
{
    size_t n = hand->n_cards;
    card_t ** arr = hand->cards;
    unsigned card_value_at_match_idx = arr[match_idx]->value;

    for (int i = 0; i < n; ++i)
        if (match_counts[i] > 1 && arr[i]->value != card_value_at_match_idx)
            return i;

    return -1;
}


/*
 - int is_straight_at(deck_t * hand, size_t index, suit_t fs)

   This function should determine if there is a straight
   starting at index (and only starting at index) in the
   given hand.  If fs is NUM_SUITS, then it should look
   for any straight.  If fs is some other value, then
   it should look for a straight flush in the specified suit.
    This function should return:
    -1 if an Ace-low straight was found at that index (and that index is the Ace)
     0  if no straight was found at that index
     1  if any other straight was found at that index

   When writing this function, you can assume
   that the hand is sorted by value: the
   values of cards will appear in descending order.
   (A K Q ... 4 3 2).
   
   There are two things that make this function
   tricky (probably the trickiest function in
   this assignment):
     (1) Ace low straights. An Ace low straight
         will appear in the hand with the Ace
	 first, then possibly some other cards,
	 then the 5 4 3 2.  For example, you
	 might have
	   As Ks Qc 5s 4c 3d 2c
     (2) You may have multiple cards with the
         same value, but still have a straight:
	   As Ac Ks Kc Qh Jh 0d
         has a straight even though A K Q
	 do not appear next to each other in
	 our sorted order.
  Hint: I made this easier on myself, by writing
  two helper functions:
  int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n) ;
   and
  int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs);

  The second of these lets me pull out the complexities of an ace
  low straight.  However, in doing so, I realized that there
  would be a lot of duplication of code between the ace low straight
  helper and the original function (for an ace low, you want to find
  a 5, then a straight of length 4: 5, 4, 3, 2).   This realization
  caused me to pull out much of the code into is_n_length_straight_at,
  so that I could call it with n=4 to search for the 5,4,3,2 part
  of an ace low straight.
*/

// ===============================================================
// ACHTUNG! Below is a lot of duplication! Re-do some other day...
// ===============================================================

int is_straight_at(deck_t * hand, size_t index, suit_t fs)
{
    int flush = fs != NUM_SUITS;

    // array of cards and its length
    size_t n = hand->n_cards;
    card_t ** arr = hand->cards;

    // suit and value of the card at index
    unsigned value_at_index = arr[index]->value;
    suit_t suit_at_index = arr[index]->suit;


    // ====  NO flush, NO Ace at index  ====
    if (!flush && value_at_index != 14)
    {
        if (value_at_index <= 5) return 0;

        int cnt = 0;
        --value_at_index;
        for (size_t i = index + 1; i < n; ++i)
        {
            if (arr[i]->value == value_at_index)
            {
                ++cnt;
                --value_at_index;
            }

            if (cnt == 4) return 1;
        }
        return 0;
    }


    // ====  FLUSH, NO Ace at index  ====
    if (flush && value_at_index != 14)
    {
        if (suit_at_index != fs) return 0;
        if (value_at_index <= 5) return 0;

        int cnt = 0;
        --value_at_index;
        for (size_t i = index + 1; i < n; ++i)
        {
            if (arr[i]->value == value_at_index && arr[i]->suit == fs)
            {
                ++cnt;
                --value_at_index;
            }
            
            if (cnt == 4) return 1;
        }
        return 0;
    }


    // ====  NO flush, ACE at index  ====
    if (!flush && value_at_index == 14)
    {
        int cnt = 0;
        --value_at_index; // value to find: King (13)
        for (size_t i = index + 1; i < n; ++i)
        {
            if (value_at_index > arr[i]->value)
            {
                // either NO high-ace-straight
                // OR        low-ace-straight
                int counter = 0;
                unsigned value_to_find = 5;
                
                for (int j = 0; j < n; ++j)
                {
                    if (arr[j]->value == value_to_find)
                    {
                        ++counter;
                        --value_to_find;
                    }
                }
                
                if (counter == 4) return -1;
                return 0;
            }
                
            if (arr[i]->value == value_at_index)
            {
                ++cnt;
                --value_at_index;
            }
            
            if (cnt == 4) return 1;
        }
        return 0;
    }

    // ====  FLUSH, ACE at index  ====
    if (flush && value_at_index == 14)
    {
        if (suit_at_index != fs) return 0;

        int cnt = 0;
        --value_at_index;
        for (size_t i = index + 1; i < n; ++i)
        {
            if (value_at_index > arr[i]->value)
            {
                // either NO high-ace-straight
                // OR        low-ace-straight
                int counter = 0;
                unsigned value_to_find = 5;
                
                for (int j = 0; j < n; ++j)
                {
                    if (arr[j]->value == value_to_find && arr[j]->suit == fs)
                    {
                        ++counter;
                        --value_to_find;
                    }
                }
                
                if (counter == 4) return -1;
                return 0;
            }
                
            if (arr[i]->value == value_at_index && arr[i]->suit == fs)
            {
                ++cnt;
                --value_at_index;
            }
            
            if (cnt == 4) return 1;
        }
        return 0;
    }

    return 0;
}


/*
 - hand_eval_t build_hand_from_match(deck_t * hand, unsigned n, hand_ranking_t what, size_t idx);

   Now you have written a bunch of functions that
   will figure out which ranking a hand has. It
   is time to construct a hand_eval_t (see eval.h) which
   has the ranking and the 5 cards used for it.
   This helper function will handle the
   "n of a kind" case.
   It should make hand_eval_t and set its
   ranking to the passed in "what" value.
   Then it should copy "n" cards from
   the hand, starting at "idx" into
   the first "n" elements of the hand_eval_t's 
   "cards" array.  The cards field in
   hand_eval_t is declared as:
         card_t * cards[5]
   This is an array of pointers, each to a card_t.
   Draw a picture to be sure you know how to name
   each card_t "box" before you start writing code.

   Your function should then fill the remainder
   of the "cards" array with the highest-value
   cards from the hand which were not in
   the "n of a kind".

   For example, given this hand:
     As Kc Kh Kd Qc 8s 5d
   The hand has 3 kings, and the As and Qc will break ties.
   Note that here  n = 3, what= THREE_OF_A_KIND, idx= 1.
   So the cards array in the hand_eval_t should have

     Kc Kh Kd As Qc

   Note that what may also be FULL_HOUSE or TWO_PAIR,
   since this function will get used for the first
   part of preparing those evaluations (then other code
   will later fix the rest of the hand with the other pair).
*/
hand_eval_t build_hand_from_match(deck_t * hand, unsigned n, hand_ranking_t what, size_t idx)
{
    hand_eval_t ans;
    ans.ranking = what;

    size_t len = hand->n_cards;
    card_t ** arr = hand->cards;

    if (what == NOTHING)
    {
        for (int i = 0; i < 5; ++i)
            ans.cards[i] = arr[i];

        return ans;
    }

    for (int i = 0; i < n; ++i)
        ans.cards[i] = arr[idx + i];

    size_t r_incl = idx + n - 1;
    size_t idx_to_copy = n;
    int elements_to_copy = 5 - n;
    
    for (int i = 0; i < len; ++i)
    {
        if (elements_to_copy == 0) break;

        if (i < idx || i > r_incl)
        {
            ans.cards[idx_to_copy] = arr[i];
            ++idx_to_copy;
            --elements_to_copy;
        }
    }

    return ans;
}



/*
 - int compare_hands(deck_t * hand1, deck_t * hand2)

   This is the goal of the whole thing: given two hands,
   figure out which wins (or if it is a tie).
   Everything you wrote goes together to make this work!
 

   We're providing you with
     hand_eval_t evaluate_hand(deck_t * hand) ;
   since it involves some things you won't learn until
   Course 4.   It's also not super interesting:
   it mostly make a bunch of calls to the functions
   you wrote above, and has a lot of if-statements
   to handle the rules of poker.

   The important part of evaluate_hand is that
   (a) assumes the cards in the passed in hand are
   sorted and (b) it returns a hand_eval_t for the passed in hand.
   
   That means that to implement compare_hands, you should

 (a) sort each hand using qsort on the hand's cards
     and your card_ptr_comp [from earlier]
 (b) Call evaluate_hand on each hand, which gives you a hand_eval_t
     for each hand.
 (c) Check if the rankings in the hand_eval_t are the same
     or different.  If they are different, you can just use
     the ranking to determine the winner.
 (d) If they are the same, then you need to look
     at the values in the cards array of each hand_eval_t
     to break the tie. The way that we constructed
     the hand_eval_t's cards array means that
     the cards are already ordered from most significant (at index 0)
     to least significant (at index 4).  You can just
     do a lexicographic comparison on the values in the arrays.
     (Its like comparing strings, but you are comparing values
      of cards---if element 0 is the different, use that difference
      to determine your answer.  If element 0 is the same,
      look at element 1, and so on).
Note that compare hands should return a positive number
if hand 1 is better, 0 if the hands tie, and a negative number
if hand 2 is better.

You will also notice some functions at the bottom of eval.c that
we provided.  You don't need to do anything to these---we wrote
them for you to keep the amount of code manageable.
*/
int compare_hands(deck_t * hand1, deck_t * hand2)
{
    qsort(hand1->cards, hand1->n_cards, sizeof(hand1->cards[0]), card_ptr_comp);
    qsort(hand2->cards, hand2->n_cards, sizeof(hand2->cards[0]), card_ptr_comp);

    hand_eval_t left = evaluate_hand(hand1);
    hand_eval_t right = evaluate_hand(hand2);
    
    if (left.ranking < right.ranking) return 1;
    if (left.ranking > right.ranking) return -1;

    for (int i = 0; i < 5; ++i)
    {
        if (left.cards[i]->value > right.cards[i]->value) return 1;
        if (left.cards[i]->value < right.cards[i]->value) return -1;
    }

    return 0;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) ;

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
