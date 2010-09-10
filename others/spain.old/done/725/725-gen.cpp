#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <map>
#include <string>

using namespace std;

int perm[10];
map<int, vector<string> > res;


void permute (int m);


int main ()
{
    int i;

    for (i = 9; i >= 0; i--)
        perm[9-i] = i;

    permute (10);
    
    vector<string>::const_iterator it;

    for (i = 0; i < 80; i++) {
        printf ("{\n");
        it = res[i].begin ();

        while (it != res[i].end ()) {
            printf ("\t\"%s\",\n", it->c_str ());
            it++;
        }
        printf ("},\n");
    }
        

    return 0;
}


void print ()
{
    for (int i = 0; i < 10; i++)
        printf ("%d ", perm[i]);
    printf ("\n");
}


void reverse (int m)
{
    int i = 0, j = m-1;

    while (i < j) {
        int n = perm[i];
        perm[i] = perm[j];
        perm[j] = n;
        i++;
        j--;
    }

}


void process ()
{
    int a, b;

    b = perm[0] + perm[1]*10 + perm[2]*100 + perm[3]*1000 + perm[4]*10000;
    a = perm[5] + perm[6]*10 + perm[7]*100 + perm[8]*1000 + perm[9]*10000;

    if (!(a % b)) {
        char buf[100];

        sprintf (buf, "%05d / %05d = %d", a, b, a/b);
        res[a/b].push_back (buf);
        //        printf ("%s\n", buf);
    }
}


void permute (int m)
{
    int i;

    if (m == 1) 
        process ();
    else {
        for (i = 0; i < m; i++) {
            permute (m-1);
            if (i < m-1) {
                int n = perm[m-1];
                perm[m-1] = perm[i];
                perm[i] = n;

                reverse (m-1);
            }
        }
    }
}
