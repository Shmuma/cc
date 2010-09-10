#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    const char* txt;
    long long val;
} entry_t;

entry_t mul[] = {{"hundred", 100}, {"thousand", 1000}, {"million", 1000000}, {NULL, 0}};
entry_t val[] = {
    {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10},
    {"eleven", 11}, {"twelve", 12}, {"thirteen", 13}, {"fourteen", 14}, {"fifteen", 15}, {"sixteen", 16}, {"seventeen", 17}, {"eighteen", 18}, 
    {"nineteen", 19}, {"twenty", 20}, {"thirty", 30}, {"forty", 40}, {"fifty", 50}, {"sixty", 60}, {"seventy", 70}, {"eighty", 80}, {"ninety", 90},
    {NULL, 0}
};


long long find_val (const char* text, entry_t* arr)
{
    while (arr->txt) {
        if (!strcmp (text, arr->txt))
            return arr->val;
        arr++;
    }

    return -1;
}



int main ()
{
    char buf[1024];
    char word[100];
    long long stack[200];
    long long res, v;
    char *p;
    int ofs, top;
    bool neg;

    while (1) {
        buf[0] = 0;
        scanf ("%[^\n]", buf);
        if (!buf[0])
            break;
        getchar ();

        top = 0;
        neg = false;

        // scan for word
        p = buf;
        while (*p) {
            ofs = 0;
            while (*p && *p != ' ') {
                word[ofs++] = *p;
                p++;
            }
            word[ofs] = 0;
            if (*p)
                p++;

            // match word
            if (!strcmp (word, "negative")) {
                neg = true;
                continue;
            }

            // is this mul?
            v = find_val (word, mul);
            if (v >= 0) {
                if (stack[top-1] < 0)
                    stack[top-1] *= v;
                else
                    stack[top++] = -v;
            }
            else {
                v = find_val (word, val);
                if (!top)
                    stack[top++] = v;
                else
                    if (stack[top-1] > 0)
                        stack[top-1] += v;
                    else
                        stack[top++] = v;
            }
        }

        // upwind stack
        res = 0;

        for (int i = 0; i < top; i+=2) {
            if (top-i == 1) {
                res += stack[i];
                break;
            }
            else if (top-i == 2) {
                res += -stack[i] * stack[i+1];
                break;
            }
            else if (top-i == 3) {
                res += -stack[i] * stack[i+1] + stack[i+2];
                break;
            }
            else {
                if (-stack[i+1] < -stack[i+3]) {
                    res += (-stack[i]*stack[i+1]+stack[i+2])*(-stack[i+3]);
                    i += 2;
                }
                else
                    res += -stack[i]*stack[i+1];
            }
        }

        if (neg)
            printf ("-");
        printf ("%lld\n", res);
    }
}
