// Bench:
// 1. 0:19.66
// 2. 0:16.99 (compare) 
// 3. 0:14.21 (output)
// 4. 0:00.73 (inplace)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

#define BUF_SIZE 102400

int m, cur, top, t, res;

char a[BUF_SIZE];
char b[BUF_SIZE];
char c[BUF_SIZE];
char s[BUF_SIZE];

void gen (int count);
bool check ();

int main ()
{
    while (1) {
        if (feof (stdin))
            break;
        memset (a, 0, sizeof (a));
        memset (b, 0, sizeof (b));
        memset (c, ' ', sizeof (c));
        memset (s, 0, sizeof (b));

        if (!scanf ("%s %s", a, b))
            break;
        
        if (!strlen (a))
            break;

        m = strlen (a);
        cur = 0;
        top = t = res = 0;
        c[m*4] = 0;

        printf ("[\n");
        gen (0);
        printf ("]\n");
    }

    return 0;
}



void gen (int count)
{
    char chr;
    if (count == m*2) {
        if (cur == 0)
            puts (c);
        return;
    }

    if (cur < m) {
        cur++;
        c[count << 1] = 'i';
        s[top++] = a[t++];
        gen (count+1);
        top--;
        t--;
        cur--;
    }
    
    if (cur > 0) {
        cur--;
        c[count << 1] = 'o';
        if (b[res++] == (chr = s[--top])) 
            gen (count+1);
        s[top++] = chr;
        res--;
        cur++;
    }
}



bool check ()
{
    int top = 0, t = 0, i = 0, res = 0;
    

    while (c[i]) {
        if (c[i] == 'i')
            s[top++] = a[t++];
        else {
            if (b[res++] != s[--top])
                return false;
        }
        i += 2;
    }

    return true;
}
