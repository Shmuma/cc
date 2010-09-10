#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

int a[100][100];

int res[10000][3];
int res_cnt;


int main ()
{
    int n, i, j, k;

    while (!feof (stdin)) {
        if (!scanf ("%d", &n))
            break;
        if (feof (stdin))
            break;

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                scanf ("%d", &a[i][j]);

        res_cnt = 0;
        
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                for (k = 0; k < n; k++) {
                    if ((((i > j) && (j > k)) || ((i < j) && (j < k))) && a[i][j] && a[j][k] && a[k][i]) {
                        res[res_cnt][0] = i;
                        res[res_cnt][1] = j;
                        res[res_cnt][2] = k;
                        res_cnt++;
                    }
                        
                    if ((i < j) && (j < k) && !a[i][j] && !a[j][k] && !a[k][i] && !a[j][i] && !a[k][j] && !a[i][k]) {
                        res[res_cnt][0] = i;
                        res[res_cnt][1] = j;
                        res[res_cnt][2] = k;
                        res_cnt++;
                    }
                }

        printf ("%d\n", res_cnt);

        for (i = 0; i < res_cnt; i++)
            printf ("%d %d %d\n", res[i][0]+1, res[i][1]+1, res[i][2]+1);
    }

    return 0;
}
