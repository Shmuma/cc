#include <stdio.h>
#include <stdlib.h>


int n;
int *conn;
int filter;

struct node {
    int l_ways, r_ways;
    struct node *left;
    struct node *right;
};


void append (struct node **r, int start)
{
    if (!conn[start*2] && !conn[start*2 + 1])
        return;

    if (!*r)
        *r = calloc (1, sizeof (struct node));
    if (conn[start*2]) {
        (*r)->l_ways++;
        append (&(*r)->left, conn[start*2]);
    }
    if (conn[start*2 + 1]) {
        (*r)->r_ways++;
        append (&(*r)->right, conn[start*2 + 1]);
    }
}


int walk (struct node *n)
{
    int a = 1, b = 1;
    
    if (!n)
        return 1;

    if (n->l_ways >= filter)
        a += walk (n->left);
    if (n->r_ways >= filter)
        b += walk (n->right);

    if (a > b)
        return a;
    else
        return b;
}


void destroy (struct node *n)
{
    if (!n)
        return;

    if (n->left)
        destroy (n->left);
    if (n->right)
        destroy (n->right);
    free (n);
}


int main(int argc, char *argv[])
{
    int t, m, i, j;
    struct node *root;
    int a, b;
    char s;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &m);
        root = NULL;

        for (i = 0; i < m; i++) {
            scanf ("%d", &n);
            conn = calloc (n * 2, sizeof (int));
            
            for (j = 0; j < n-1; j++) {
                scanf ("%d %c %d", &a, &s, &b);
                a--;
                b--;

                if (s == 'L')
                    conn[a*2] = b;
                else
                    conn[a*2 + 1] = b;
            }

            append (&root, 0);
            free (conn);
        }

        for (i = 0; i < m; i++) {
            if (i > 0)
                putchar (' ');
            filter = i+1;
            printf ("%d", walk (root)-1);
        }
        putchar ('\n');
        destroy (root);
    }

    return 0;
}
