// Bench:
// 1. 0:19.66
// 2. 0:16.99 (compare) 
// 3. 0:14.21 (output)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

#define BUF_SIZE 1024

int m, cur;

char a[BUF_SIZE];
char b[BUF_SIZE];
char c[BUF_SIZE];


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

        if (!scanf ("%s %s", a, b))
            break;
        
        if (!strlen (a))
            break;

        m = strlen (a);
        cur = 0;
        c[m*4] = 0;

        printf ("[\n");
        gen (0);
        printf ("]\n");
    }

    return 0;
}



void gen (int count)
{
    if (count == m*2) {
        if (cur == 0)
            if (check ())
                puts (c);
//             else
//                 printf ("f: %s\n", c);
        return;
    }

    if (cur < m) {
        cur++;
        c[count << 1] = 'i';
        gen (count+1);
        cur--;
    }
    
    if (cur > 0) {
        cur--;
        c[count << 1] = 'o';
        gen (count+1);
        cur++;
    }
}



bool check ()
{
    static char s[BUF_SIZE];
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
