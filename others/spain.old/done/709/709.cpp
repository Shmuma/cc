#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <string>
#include <vector>

using namespace std;

char buf[10240];
vector<string> words;
int width;

// lengths of words
int lengths[10000];
int cache[10000][80];
int sol[10000][80];

char* spaces[] = {
    "",
    " ",
    "  ",
    "   ",
    "    ",
    "     ",
    "      ",
    "       ",
    "        ",
    "         ",
    "          ",
    "           ",
    "            ",
    "             ",
    "              ",
    "               ",
    "                ",
    "                 ",
    "                  ",
    "                   ",
    "                    ",
    "                     ",
    "                      ",
    "                       ",
    "                        ",
    "                         ",
    "                          ",
    "                           ",
    "                            ",
    "                             ",
    "                              ",
    "                               ",
    "                                ",
    "                                 ",
    "                                  ",
    "                                   ",
    "                                    ",
    "                                     ",
    "                                      ",
    "                                       ",
    "                                        ",
    "                                         ",
    "                                          ",
    "                                           ",
    "                                            ",
    "                                             ",
    "                                              ",
    "                                               ",
    "                                                ",
    "                                                 ",
    "                                                  ",
    "                                                   ",
    "                                                    ",
    "                                                     ",
    "                                                      ",
    "                                                       ",
    "                                                        ",
    "                                                         ",
    "                                                          ",
    "                                                           ",
    "                                                            ",
    "                                                             ",
    "                                                              ",
    "                                                               ",
    "                                                                ",
    "                                                                 ",
    "                                                                  ",
    "                                                                   ",
    "                                                                    ",
    "                                                                     ",
    "                                                                      ",
    "                                                                       ",
    "                                                                        ",
    "                                                                         ",
    "                                                                          ",
    "                                                                           ",
    "                                                                            ",
    "                                                                             ",
    "                                                                              ",
    "                                                                               ",
};


void append_words (vector<string>& w, char* buf);

int solve (int word, int ofs);



int main ()
{
    string text;
    int i, j;

    while (1) {
        scanf ("%d", &width);
        getchar ();

        if (!width)
            break;

        words.clear ();

        while (1) {
            buf[0] = 0;
            scanf ("%[^\n]", buf);
            getchar ();
            if (buf[0] == 0)
                break;
            append_words (words, buf);
        }

        for (i = 0; i < width; i++)
            for (j = 0; j < words.size (); j++)
                cache[j][i] = -2;

        int s = solve (0, 0);
        int ofs = 0;

        for (i = 0; i < words.size (); i++) {
            printf (words[i].c_str ());
            if (sol[i][ofs] < 0) {
                printf ("\n");
                ofs = 0;
            } else {
                printf (spaces[sol[i][ofs]]);
                ofs += words[i].length () + sol[i][ofs];
            }
        }
        printf ("\n");
    }

    return 0;
}



void append_words (vector<string>& w, char* buf)
{
    char word[85], *p = buf, *pp;

    while (*p) {
        while (isspace (*p))
            p++;

        pp = strchr (p, ' ');
        if (pp) {
            strncpy (word, p, pp-p);
            word[pp-p] = 0;
            p = pp;
        }
        else {
            strcpy (word, p);
            p += strlen (p);
        }

        lengths[w.size ()] = strlen (word);
        w.push_back (string (word));
    }
}



int solve (int word, int ofs)
{
    int ofs_orig = ofs;

    if (word == words.size ())
        return 0;

    if (cache[word][ofs_orig] >= -1) {
        //        printf ("H[%d][%d] = %d\n", word, ofs_orig, cache[word][ofs_orig]);
        return cache[word][ofs_orig];
    }

    bool first = ofs == 0;

    ofs += lengths[word];

    if (ofs > width)
        return cache[word][ofs_orig] = -1;

    if (ofs == width) {
        sol[word][ofs_orig] = -1;
        return cache[word][ofs_orig] = solve (word+1, 0);
    }

    if (word == words.size ()-1)
        if (first) {
            sol[word][ofs_orig] = -1;
            return cache[word][ofs_orig] = 500;
        }
        else
            return cache[word][ofs_orig] = -1;

    int best = -1, m, max, best_i = 0;

    max = width - ofs - lengths[word+1];

    for (int i = 1; i <= max; i++) {
        m = solve (word+1, ofs+i);

        if (m >= 0)
            if (best < 0 || best > m + (i-1)*(i-1)) {
                best = m + (i-1)*(i-1);
                best_i = i;
            }
    }

    if (first) {
        m = solve (word+1, 0);

        if (best < 0 || (m + 500) < best) {
            sol[word][ofs_orig] = -1;
            return cache[word][ofs_orig] = m+500;
        }
    }

    if (best >= 0) {
        sol[word][ofs_orig] = best_i;
        return cache[word][ofs_orig] = best;
    }
    else
        return cache[word][ofs_orig] = -1;
}
