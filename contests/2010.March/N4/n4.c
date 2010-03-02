#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned char buf[13];
unsigned short hash[8000];

typedef struct _node {
    int val;
    struct _node *rotate[3][2];
    struct _node *parent;
} node_t;


/* number we are looking for */
const int target = 600;

#define QUEUE_SIZE 40000

node_t *queue[QUEUE_SIZE];
int queue_beg, queue_end;

int sol[1000][2];
int sol_size;


int buf2int ()
{
    int i, val = 0;
    
    for (i = 0; i < 13; i++)
        val = (val << 1) + buf[i];

    return val;
}


void int2buf (int val)
{
    int i = 0;

    memset (buf, 0, sizeof (buf));

    while (val) {
        if (val % 2)
            buf[12-i] = 1;
        else
            buf[12-i] = 0;
        val >>= 1;
        i++;
    }
}


void show_buf ()
{
    int i;

    for (i = 0; i < 13; i++)
        if (buf[i])
            putchar ('1');
        else
            putchar ('0');
}


int rotate (int val, int disk, int dir)
{
    unsigned char t;
    int res;

    int2buf (val);

    /* printf ("rotate (%d, %d): ", disk, dir); */
    /* show_buf (); */
    /* printf (" -> "); */

    switch (disk) {
    case 0:
        if (dir) {
            t = buf[0];
            buf[0] = buf[2];
            buf[2] = buf[5];
            buf[5] = buf[8];
            buf[8] = buf[6];
            buf[6] = buf[3];
            buf[3] = t;
        }
        else {
            t = buf[0];
            buf[0] = buf[3];
            buf[3] = buf[6];
            buf[6] = buf[8];
            buf[8] = buf[5];
            buf[5] = buf[2];
            buf[2] = t;
        }
        break;
    case 1:
        if (dir) {
            t = buf[1];
            buf[1] = buf[3];
            buf[3] = buf[6];
            buf[6] = buf[9];
            buf[9] = buf[7];
            buf[7] = buf[4];
            buf[4] = t;
        }
        else {
            t = buf[1];
            buf[1] = buf[4];
            buf[4] = buf[7];
            buf[7] = buf[9];
            buf[9] = buf[6];
            buf[6] = buf[3];
            buf[3] = t;
        }
        break;
    case 2:
        if (dir) {
            t = buf[6];
            buf[6] = buf[8];
            buf[8] = buf[10];
            buf[10] = buf[12];
            buf[12] = buf[11];
            buf[11] = buf[9];
            buf[9] = t;
        }
        else {
            t = buf[6];
            buf[6] = buf[9];
            buf[9] = buf[11];
            buf[11] = buf[12];
            buf[12] = buf[10];
            buf[10] = buf[8];
            buf[8] = t;
        }
        break;
    }

    res = buf2int ();
    /* show_buf (); */
    /* printf (" -> %d\n", res); */
    return res;
}


node_t* process (node_t *node)
{
    int i, j;
    node_t *n;
    int val;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 2; j++) {
            val = rotate (node->val, i, j);

            if (hash[val])
                continue;

            n = (node_t*)calloc (1, sizeof (node_t));
            node->rotate[i][j] = n;
            n->val = val;
            n->parent = node;

            if (val == target)
                return n;

            if (queue_end == QUEUE_SIZE) {
                memmove (queue, queue+queue_beg, (queue_end-queue_beg) * sizeof (queue[0]));
                queue_end = queue_end-queue_beg;
                queue_beg = 0;
            }
            queue[queue_end++] = n;
            hash[val] = 1;
        }

    return NULL;
}


void solve (int start)
{
    node_t *node;
    int i, j;

    if (start == target) {
        sol_size = 0;
        return;
    }

    memset (hash, 0, sizeof (hash));

    node = (node_t*)calloc (1, sizeof (node_t));

    node->val = start;
    hash[start] = 1;
    
    queue_beg = 0;
    queue_end = 0;
    queue[queue_end++] = node;

    while (1) {
        node = queue[queue_beg++];
        
        node = process (node);
        if (node) {
            int found;
            /* solution found, traverse node pointers */
            sol_size = 0;
            while (node->parent) {
                found = 0;
                for (i = 0; i < 3 && !found; i++)
                    for (j = 0; j < 2 && !found; j++)
                        if (node->parent->rotate[i][j] == node) {
                            sol[sol_size][0] = i;
                            sol[sol_size][1] = j;
                            sol_size++;
                            found = 1;
                        }
                node = node->parent;
            }
            return;
        }
    }
}


int main(int argc, char *argv[])
{
    int n, i;

    scanf ("%d", &n);
    getchar ();
    while (n--) {
        for (i = 0; i < 13; i++)
            if (getchar () == '0')
                buf[i] = 0;
            else
                buf[i] = 1;
        getchar ();
        memset (hash, 0, sizeof (hash));
        solve (buf2int ());
        printf ("%d\n", sol_size);
        for (i = sol_size-1; i >= 0; i--)
            printf ("%d %d\n", sol[i][0], sol[i][1]);
    }

    return 0;
}
