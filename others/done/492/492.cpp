#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void put_word (const char* word, int cnt)
{
    for (int i = 0; i < cnt; i++)
        putchar (word[i]);
}


void handle_word (char* word, int cnt)
{
    if (strchr ("aeiouAEIOU", word[0]))
        put_word (word, cnt);
    else {
        put_word (word+1, cnt-1);
        putchar (word[0]);
    }
    put_word ("ay", 2);
}


int main ()
{
    int c, cnt = 0;
    char word[1024];

    while ((c = getchar ()) != -1) {
        if (!isalpha (c)) {
            if (cnt) {
                handle_word (word, cnt);
                cnt = 0;
            }
            putchar (c);
            continue;
        }
        else
            word[cnt++] = c;
    }

    return 0;
}
