#include <stdio.h>
#include <stdlib.h>

int n1, n2, n3;
int *nn1, *nn2, *nn3;
int merged[50000];

int* get_n (int n)
{
    int* res = (int*)malloc (sizeof (int)*n);
    int i;

    for (i = 0; i < n; i++)
        scanf ("%d", res+i);

    return res;
}


int compare (const void *a, const void *b)
{
    const int *aa = a;
    const int *bb = b;

    return *aa - *bb;
}


/*
 * Return id of list with minimum value. If there is no strict minimum
 * (f.e. minimum has two lists), return -1.
 */
int min_index (int i, int j, int k)
{
    int v1 = nn1[i], v2 = nn2[j], v3 = nn3[k];
 
    if (v1 == v2)
        if (v3 < v1)
            return 2;
        else
            return -1;
    else {
        if (v1 == v3)
            if (v2 < v1)
                return 1;
            else
                return -1;
        else
            if (v2 == v3)
                if (v1 < v2)
                    return 0;
                else
                    return -1;
            else {
                if (v1 < v2)
                    if (v3 < v1)
                        return 2;
                    else
                        return 0;
                else
                    if (v2 < v3)
                        return 1;
                    else
                        return 2;
                return -1;
            }
    }
}


int merge_two (int res_index, int* l1, int i1, int max1, int* l2, int i2, int max2)
{
    while (1) {
        if (l1[i1] == l2[i2]) {
            merged[res_index++] = l1[i1];
            i1++;
            i2++;
        }
        else {
            if (l1[i1] < l2[i2])
                i1++;
            else
                i2++;
        }

        if (i1 == max1 || i2 == max2)
            break;
    }

    return res_index;
}


int merge ()
{
    int i = 0, j = 0, k = 0, count = 0;
    int d;

    while (1) {
        d = min_index (i, j, k);

        switch (d) {
        case 0:
            i++;
            break;
        case 1:
            j++;
            break;
        case 2:
            k++;
            break;
        case -1:
            if (nn1[i] == nn2[j]) {
                merged[count++] = nn1[i];
                i++;
                j++;
            } else {
                if (nn1[i] == nn3[k]) {
                    merged[count++] = nn1[i];
                    i++;
                    k++;
                }
                else {
                    if (nn2[j] == nn3[k]) {
                        merged[count++] = nn2[j];
                        j++;
                        k++;
                    }
                }
            }
            break;
        }

        if (i == n1) {
            count = merge_two (count, nn2, j, n2, nn3, k, n3);
            break;
        }

        if (j == n2) {
            count = merge_two (count, nn1, i, n1, nn3, k, n3);
            break;
        }

        if (k == n3) {
            count = merge_two (count, nn1, i, n1, nn2, j, n2);
            break;
        }
    }

    return count;
}


int main(int argc, char *argv[])
{
    int i, n;

    scanf ("%d %d %d", &n1, &n2, &n3);

    nn1 = get_n (n1);
    nn2 = get_n (n2);
    nn3 = get_n (n3);

    n = merge ();
    printf ("%d\n", n);

    for (i = 0; i < n; i++)
        printf ("%d\n", merged[i]);

    return 0;
}
