#include <stdio.h>
#include <stdlib.h>


#define GROUP_SIZE 1000

int groups[GROUP_SIZE];


int main(int argc, char *argv[])
{
    FILE* f = fopen (argv[1], "r");
    unsigned long long n, diff;
    int i;

    if (!f)
        return 0;

    diff = 5000000000LLU / GROUP_SIZE;

    while (!feof (f)) {
        if (!fscanf (f, "%llu", &n))
            break;
        groups[n / diff]++;
    }

    fclose (f);

    for (i = 0; i < GROUP_SIZE; i++)
        //        printf ("%010llu..%010llu: %d\n", diff*i, diff*(i+1), groups[i]);
        printf ("%d, ", groups[i]);
    printf ("\n");
    
    return 0;
}
