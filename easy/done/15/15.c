#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* order = "AKQJT98765432";
static char* order2 = "KQJT98765432A";


int card_index (char c)
{
    return strchr (order, c) - order;
}


int card_index2 (char c)
{
    return strchr (order2, c) - order2;
}


int compare (const void* a, const void *b)
{
    const char* aa = (const char*)a;
    const char* bb = (const char*)b;

    return card_index (*aa) - card_index (*bb);
}


int compare2 (const void* a, const void *b)
{
    const char* aa = (const char*)a;
    const char* bb = (const char*)b;

    return card_index2 (*aa) - card_index2 (*bb);
}


int same_suit (char hand[5][2])
{
    return
        hand[0][1] == hand[1][1] &&
        hand[1][1] == hand[2][1] &&
        hand[2][1] == hand[3][1] &&
        hand[3][1] == hand[4][1];
}


int straight (char hand[5][2])
{
    int i, idx, idx2, valid = 1;

    qsort (hand, 5, sizeof (char)*2, compare2);
    idx = card_index2 (hand[0][0]);

    for (i = 1; i < 5 && valid; i++) {
        idx2 = card_index2 (hand[i][0]);
        if (idx2-idx != 1)
            valid = 0;
        idx = idx2;
    }

    qsort (hand, 5, sizeof (char)*2, compare);

    if (valid)
        return 1;

    valid = 1;
    idx = card_index (hand[0][0]);

    for (i = 1; i < 5 && valid; i++) {
        idx2 = card_index (hand[i][0]);
        if (idx2-idx != 1)
            valid = 0;
        idx = idx2;
    }

    return valid;
}


int royal_flush (char hand[5][2])
{
    int val;

    if (!same_suit (hand))
        return 0;

    val =
        hand[0][0] == 'A' &&
        hand[1][0] == 'K' &&
        hand[2][0] == 'Q' &&
        hand[3][0] == 'J' &&
        hand[4][0] == 'T';
    return val;
}


int straight_flush (char hand[5][2])
{
    if (!same_suit (hand))
        return 0;

    return straight (hand);
}


int four (char hand[5][2])
{
    return
        (hand[0][0] == hand[1][0] &&
         hand[1][0] == hand[2][0] &&
         hand[2][0] == hand[3][0]) ||
        (hand[1][0] == hand[2][0] &&
         hand[2][0] == hand[3][0] &&
         hand[3][0] == hand[4][0]);
}


int full_house (char hand[5][2])
{
    return
        (hand[0][0] == hand[1][0] &&
         hand[1][0] == hand[2][0] &&
         hand[3][0] == hand[4][0]) ||
        (hand[0][0] == hand[1][0] &&
         hand[2][0] == hand[3][0] &&
         hand[3][0] == hand[4][0]);
}



int flush (char hand[5][2])
{
    return same_suit (hand);
}


int three (char hand[5][2])
{
    return
        (hand[0][0] == hand[1][0] &&
         hand[1][0] == hand[2][0]) ||
        (hand[1][0] == hand[2][0] &&
         hand[2][0] == hand[3][0]) ||
        (hand[2][0] == hand[3][0] &&
         hand[3][0] == hand[4][0]);
}


int two_pairs (char hand[5][2])
{
    if (hand[0][0] == hand[1][0])
        return
            (hand[2][0] == hand[3][0]) ||
            (hand[3][0] == hand[4][0]);
    else
        return
            (hand[1][0] == hand[2][0]) &&
            (hand[3][0] == hand[4][0]);
}


int pair (char hand[5][2])
{
    return
        hand[0][0] == hand[1][0] ||
        hand[1][0] == hand[2][0] ||
        hand[2][0] == hand[3][0] ||
        hand[3][0] == hand[4][0];
}


const char* solve (char hand[5][2])
{
    qsort (hand, 5, sizeof (char)*2, compare);

    if (royal_flush (hand))
        return "royal flush";

    if (straight_flush (hand))
        return "straight flush";

    if (four (hand))
        return "four of a kind";

    if (full_house (hand))
        return "full house";

    if (flush (hand))
        return "flush";

    if (straight (hand))
        return "straight";

    if (three (hand))
        return "three of a kind";

    if (two_pairs (hand))
        return "two pairs";

    if (pair (hand))
        return "pair";

    return "high card";
}


int main(int argc, char *argv[])
{
    int n, i;
    char hand[5][2];

    scanf ("%d", &n);
    getchar ();

    while (n--) {
        for (i = 0; i < 5; i++) {
            scanf ("%c%c", hand[i], hand[i]+1);
            getchar ();
        }

        puts (solve (hand));
    }

    return 0;
}
