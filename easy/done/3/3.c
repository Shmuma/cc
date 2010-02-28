#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int attempt;
    float balance;

    scanf ("%d %f", &attempt, &balance);

    /* not a factor of 5 */
    if (attempt % 5)
        printf ("%.2f\n", balance);
    else
        if (balance-0.5-attempt < -0.0000000001)
            printf ("%.2f\n", balance);
        else
            printf ("%.2f\n", balance - 0.5 - attempt);

    return 0;
}
