// performance tuning log:
// 1. 0:21.31 (-O0)
// 2. 0:10.04 (-O2)
// 3. 0:09.32 (undo)
// 4. 0:26.02 (depth 10)
// 5. 0:17.86 (depth 6)
// 6. 0:16.55 (depth 4)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map>
#include <deque>

using namespace std;


char conf[24];
char fin[24] = {
    0,3,4,3,0,5,6,5,0,1,2,1,0,7,8,7,0,9,10,9,0,1,2,1,
};

typedef struct hash {
    unsigned long long first, second;

    const bool operator < (struct hash b) const 
    {
        if (first < b.first)
            return true;
        if (first == b.first)
            return second < b.second;
        else
            return false;
    }

    const bool operator == (struct hash b) const
    {
        return first == b.first && second == b.second;
    }
} hash_t;


typedef struct {
    hash_t state;
    unsigned long long path;
    char prev;
} var_t;


hash_t final;


map<hash_t, unsigned long long> hash;


int ops[16];
int ops_top;


hash_t pos2hash (char* buf);


// reverse rotations, used to rollback state
int rev[] = {
    0,
    3, 4, 1, 2,
};

unsigned long long do_solve (hash_t state);
void turn (int op, hash_t* from, hash_t* to);
void print (hash_t v);
void show ();
void prehash (hash_t state, int depth, int prev, unsigned long long hist);
hash_t pos2hash (char* buf);
unsigned long long lookup (hash_t key);
void decode (unsigned long long sol);
void decode_rev (unsigned long long sol);
int res_len (unsigned long long sol);


int main ()
{
    int n, i, t;

    final = pos2hash (fin);

    prehash (final, 8, 0, 0);

    scanf ("%d", &n);

    while (n--) {
        for (i = 0; i < 24; i++) {
            scanf ("%d", &t);
            conf[i] = t;
        }
        
        hash_t config = pos2hash (conf);
        
        ops_top = 0;
        if (config == final)
            printf ("PUZZLE ALREADY SOLVED\n");
        else {
            unsigned long long res = do_solve (config);

            if (res) {
                decode (res);
                show ();
            }
            else
                printf ("NO SOLUTION WAS FOUND IN 16 STEPS\n");
        }
    }

    return 0;
}



unsigned long long do_solve (hash_t state)
{
    deque<var_t> s;
    deque<var_t> new_s;
    int level = 0, vars = 0;
    var_t cur, t;
    
    cur.state = state;
    cur.path  = 0;
    cur.prev = -1;

    s.push_back (cur);

    while (level <= 8) {
        cur = s.front ();
        s.pop_front ();

        if (cur.state == final)
            return cur.path;

        unsigned long long v = lookup (cur.state);

        if (v) {
            decode_rev (cur.path);
            return v;
        }

        for (int i = 1; i <= 4; i++) {
            if (i != rev[cur.prev]) {
                turn (i, &cur.state, &t.state);
                t.prev = i;
                t.path = cur.path;
                t.path <<= 4;
                t.path |= rev[i];
                new_s.push_back (t);
            }
        }

        vars++;
        
        if (!s.size ()) {
            s = new_s;
            vars = 0;
            new_s.clear ();
            level++;
        }
    }

    return 0;
}



//void turn (int op, char* from, char* to)
void turn (int op, hash_t* from, hash_t* to)
{
    unsigned int tmp;
    unsigned long long aa, bb;

    aa = from->first;
    bb = from->second;

    switch (op) {
    case 1:
        tmp = aa & 0xFF;
        aa >>= 8;
        aa |= (unsigned long long)tmp << 40;
        break;
    case 2:
        tmp = (bb >> 40) & 0xFF;
        bb <<= 8;
        bb &= 0xFFFFFFFFFFFFULL;
        bb |= (unsigned long long)tmp;
        break;
    case 3:
        tmp = (aa >> 40) & 0xFF;
        aa <<= 8;
        aa &= 0xFFFFFFFFFFFFULL;
        aa |= (unsigned long long)tmp;
        break;
    case 4:
        tmp = bb & 0xFF;
        bb >>= 8;
        bb |= (unsigned long long)tmp << 40;
        break;
    }

    if (op % 2) {
        bb &= ~0xFFF;
        bb |= aa & 0xFFF;
    }
    else {
        aa &= ~0xFFF;
        aa |= bb & 0xFFF;
    }
    
    to->first = aa;
    to->second = bb;
}


void print (hash_t v)
{
    int i;

    for (i = 0; i < 12; i++) {
        printf ("%d ", v.first & 0xF);
        v.first >>= 4;
    }

    printf ("| ");

    for (i = 0; i < 12; i++) {
        printf ("%d ", v.second & 0xF);
        v.second >>= 4;
    }
    printf ("\n");
}


void show ()
{
    for (int i = 0; i < ops_top; i++)
        printf ("%d", ops[i]);
    printf ("\n");
}


hash_t pos2hash (char* buf)
{
    unsigned long long a = 0, b = 0;

    for (int i = 0; i < 12; i++) {
        a <<= 4;
        a |= buf[i];
    }

    for (int i = 12; i < 24; i++) {
        b <<= 4;
        b |= buf[i];
    }

    hash_t res;

    res.first = a;
    res.second = b;

    return res;
}



void prehash (hash_t state, int depth, int prev, unsigned long long hist)
{
    hash_t new_state;
    unsigned long long v = lookup (state);

    if (!v || hist < v) {
        hash[state] = hist;
        //        printf ("H: (%llx, %llx) -> %llx\n", state.first, state.second, hist);
    }

    if (!depth)
        return;

    for (int i = 1; i <= 4; i++)
        if (i != rev[prev]) {
            turn (i, &state, &new_state);
            prehash (new_state, depth-1, i, (hist << 4) | i);
        }
}


unsigned long long lookup (hash_t key)
{
    map<hash_t, unsigned long long>::const_iterator it = hash.find (key);

    if (it == hash.end ())
        return 0;
    else
        return it->second;
}


void decode (unsigned long long sol)
{
    int val;

    while (sol) {
        val = sol & 0xf;
        sol >>= 4;
        ops[ops_top++] = rev[val];
    }
}



int res_len (unsigned long long sol)
{
    int res = 0;

    while (sol) {
        sol >>= 4;
        res++;
    }

    return res;
}


void decode_rev (unsigned long long sol)
{
    int val;
    unsigned long long res = 0;

    while (sol) {
        val = sol & 0xf;
        sol >>= 4;
        res <<= 4;
        res |= val;
    }

    decode (res);
}



