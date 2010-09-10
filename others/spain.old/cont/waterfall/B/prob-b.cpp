#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double parse (char* buf, int* pos);

int main ()
{
    char buf[1024];
    int pos;

    while (1) {
        scanf ("%[^\n]", buf);
        getchar ();

        if (buf[0] == '(' && buf[1] == ')')
            break;
        
        double res = parse (buf, &pos);
        printf ("%.2lf\n", res);
    }

    return 0;
}


double parse (char* buf, int* pos)
{
    double res;

    if (buf[0] == '(') {
        double p, a, b;
        int i, ii;
        char* pp;

        sscanf (buf+1, "%lf", &p);

        pp = strchr (buf+1, ' ')+1;
        a = parse (pp, &ii);
        pp += ii+1;
        b = parse (pp, &ii);
        pp += ii+1;
        res = a-b+2*b*p;
        *pos = pp-buf;
    }
    else {
        sscanf (buf, "%lf", &res);
        if (!strchr (buf, ' '))
            *pos = 0;
        else
            *pos = strchr (buf, ' ')-buf;
    }

    return res;
}
