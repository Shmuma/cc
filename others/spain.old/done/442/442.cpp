#include <stdio.h>
#include <stdlib.h>

#include <vector>


int matr[30][2];


void dump (std::vector< std::pair<int, int> >& v)
{
    std::vector< std::pair<int, int> >::iterator it = v.begin ();

    while (it != v.end ()) {
        printf ("(%d %d) ", it->first, it->second);
        it++;
    }

    printf ("\n");
}


int main ()
{
    int n, i, a, b;
    char c;
    std::vector < std::pair <int, int> > s;
    bool err;
    long long res;

    scanf ("%d", &n);
    getchar ();

    while (n--) {
        scanf ("%c %d %d", &c, &a, &b);
        getchar ();
        matr[c-'A'][0] = a;
        matr[c-'A'][1] = b;
    }

    while (!feof (stdin)) {
        s.clear ();
        s.push_back (std::pair<int,int> (-1, -1));

        err = false;
        res = 0;

        while (1) {
            c = getchar ();

            if (feof (stdin))
                break;

            if (c == ' ')
                continue;

            if (c == '\n')
                break;

            if (err)
                continue;

            //            printf ("Got: %c\n", c);
            //            dump (s);

            if (c == '(') {
                s.push_back (std::pair<int,int> (-1, -1));
            } 
            else 
                if (c == ')') {
                    // trying to walk back to nearest -1,-1
                    a = b = -1;
                    while (s.back ().first != -1) {
                        if (a == -1) {
                            a = s.back ().first;
                            b = s.back ().second;
                        } else {
                            if (s.back ().second != a)
                                err = true;
                            else {
                                res += a*b*s.back ().first;
                                a = s.back ().first;
                            }
                        }
                        
                        s.pop_back ();
                    }

                    s.pop_back ();
                    s.push_back (std::pair<int, int> (a, b));
                }
                else
                    s.push_back (std::pair<int,int> (matr[c-'A'][0], matr[c-'A'][1]));
            //            dump (s);
            //            printf ("\n");
        }

        if (feof (stdin))
            break;

        a = b = -1;
        while (s.back ().first != -1) {
            if (a == -1) {
                a = s.back ().first;
                b = s.back ().second;
            } else {
                if (s.back ().second != a)
                    err = true;
                else {
                    res += a+b;
                    a = s.back ().first;
                }
            }
                        
            s.pop_back ();
        }

        if (err) 
            printf ("error\n");
        else 
            printf ("%lld\n", res);
    }

    return 0;
}
