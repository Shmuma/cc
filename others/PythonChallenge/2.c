#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main (int argc, char *argv[])
{
    int c;

    while ((c = getchar ()) > 0) {
        if (isalpha (c)) {
            c += 2;
            if (c > 'z')
                c -= 'z'-'a'+1;
        }
        putchar (c);
    }
    return 0;
}
