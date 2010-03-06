#include <stdio.h>
#include <stdlib.h>

int notes_count;
int notes[50];
int used[50];


int solve (int amount)
{
    int i = notes_count-1;

    if (!amount)
        return 1;
    if (amount < 0)
        return 0;

    while (i >= 0) {
        if (!used[i] && amount >= notes[i]) {
            used[i] = 1;
            if (solve (amount - notes[i]))
                return 1;
            used[i] = 0;
        }
        i--;
    }

    return 0;
}


int compare (const void *a, const void *b)
{
    return *(const int*)a - *(const int*)b;
}


int main(int argc, char *argv[])
{
    int n, i, ask;

    scanf ("%d", &n);
    while (n--) {
        scanf ("%d %d", &notes_count, &ask);
        for (i = 0; i < notes_count; i++) {
            scanf ("%d", &notes[i]);
            used[i] = 0;
        }
    
        qsort (notes, notes_count, sizeof (notes[0]), compare);
        if (solve (ask))
            puts ("Yes");
        else
            puts ("No");
    }

    return 0;
}
