#include <stdio.h>
#include <stdlib.h>

struct node {
    int op;
    char val;
    struct node *left;
    struct node *right;
};


struct node *parse (char *s, char **p);


/* Parse one arg (non-greedy) */
struct node *parse_arg (char *s, char **p)
{
    struct node *n = (struct node *)calloc (1, sizeof (struct node));

    if (*s == '(') {
        struct node *nn = parse (s+1, p);
        s = *p;
        /* *s must be ')' */
        s++;
        *p = s;
        free (n);
        n = nn;
    }
    else {
        n->val = *s;
        *p = s+1;
    }

    return n;
}


struct node *parse (char *s, char **p)
{
    struct node *n, *nn;

    n = parse_arg (s, p);

    if (**p) {
        nn = (struct node *)calloc (1, sizeof (struct node));
        nn->left = n;
        nn->op = 1;
        nn->val = **p;
        s = *p;
        s++;
        nn->right = parse_arg (s, p);
        n = nn;
    }

    return n;
}


void show (struct node *n)
{
    if (!n)
        return;

    if (n->op) {
        show (n->left);
        show (n->right);
        putchar (n->val);
    }
    else
        putchar (n->val);
}


void destroy_node (struct node *n)
{
    if (n->left)
        destroy_node (n->left);
    if (n->right)
        destroy_node (n->right);
    free (n);
}


void process (char *str)
{
    struct node *n;
    char *pp;

    n = parse (str, &pp);
    show (n);
    putchar ('\n');
    destroy_node (n);
}



int main(int argc, char *argv[])
{
    int n;
    char buf[500];

    scanf ("%d", &n);
    while (n--) {
        buf[0] = 0;
        scanf ("%s", buf);
        getchar ();
        process (buf);
    }

    return 0;
}
