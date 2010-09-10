#include <stdio.h>
#include <stdlib.h>


int main ()
{
    int n, i, m, trail;
    char n1[300], n2[300];

    scanf ("%d", &n);

    while (n--) {
        scanf ("%s %s", n1, n2);

        trail = m = i = 0; 

        while (n1[i] && n2[i]) {
            m += (n1[i] - '0') + (n2[i] - '0');
            if (trail || m % 10) {
                printf ("%c", (m % 10) + '0');
                trail = 1;
            }
            m /= 10;
            i++;
        }

        if (!n1[i])
            while (n2[i]) {
                m += n2[i] - '0';
                if (trail || m % 10) {
                    printf ("%c", (m % 10) + '0');
                    trail = 1;
                }
                m /= 10;
                i++;
            }
        else
            if (!n2[i])
                while (n1[i]) {
                    m += n1[i] - '0';
                    if (trail || m % 10) {
                        printf ("%c", (m % 10) + '0');
                        trail = 1;
                    }
                    m /= 10;
                    i++;
                }

        if (m)
            printf ("%c", m+'0');

        printf ("\n");
    }

    return 0;
}
