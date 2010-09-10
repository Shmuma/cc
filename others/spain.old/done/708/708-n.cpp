#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


enum token_kind_t {
    t_num,
    t_br_o,
    t_br_c,
};


typedef struct token {
    token_kind_t kind;
    int val;
} token_t;


enum expr_kind_t {
    expr_op,
    expr_br,
    expr_num,
};


typedef struct expr {
    expr_kind_t kind;
    struct expr* left;
    struct expr* right;
    int num;
} expr_t;


int result;

token_t tokens[1000];
int t_count;

int ops[1000];
int ops_max;
expr_t* root;

char ops_table[] = {
    '+', '-', '*'
};


expr_t* parse (int from, int to);
void tokenize (char* l);

void print ();
bool solve (int level);
bool check ();
void do_print (expr_t* p, int& op);
int  do_eval (expr_t* p, int& op);

int main ()
{
    char buf[1000];
    int c = 1;
    char* p, *f;

    while (1) {
        scanf ("%[^\n]", buf);
        getchar ();

        if (!strcmp (buf, "0") || feof (stdin))
            break;

        sscanf (buf, "%d", &result);

        p = strchr (buf, '=');

        if (!p)
            break;
        p++;

        t_count = ops_max = 0;
        tokenize (p);
        root = parse (0, t_count);

        printf ("Equation #%d:\n", c++);
        if (solve (0))
            print ();
        else
            printf ("Impossible.\n");
        printf ("\n");
    }

    return 0;
}


char* skip_spaces (char* p)
{
    while (*p && *p == ' ')
        p++;
    return p;
}


char* skip_numbers (char* p)
{
    while (*p && isdigit (*p))
        p++;
    return p;
}



expr_t* parse (int from, int to)
{
    int i = from;
    expr_t* res = NULL;
    expr_t* cur = NULL;
    
    if (from >= to)
        return NULL;

    while (i < to) {
        switch (tokens[i].kind) {
        case t_num:
            cur = (expr_t*)malloc (sizeof (expr_t));
            cur->kind = expr_num;
            cur->num = tokens[i].val;
            i++;
            break;

        case t_br_o:
            int j = i+1, sum = 1;
            
            while (sum > 0 && j < to) {
                if (tokens[j].kind == t_br_o)
                    sum++;
                if (tokens[j].kind == t_br_c)
                    sum--;
                j++;
            }
            j--;
            
            cur = (expr_t*)malloc (sizeof (expr_t));
            cur->kind = expr_br;
            cur->left = parse (i+1, j);

            i = j+1;
            break;
        }

        if (!res)
            res = cur;
        else {
            expr_t* up = (expr_t*)malloc (sizeof (expr_t));
            up->kind = expr_op;
            up->left = res;
            up->right = cur;
            res = up;
            ops_max++;
        }
    }

    return res;
}


void tokenize (char* l) 
{
    while (*l) {
        l = skip_spaces (l);

        if (isdigit (*l)) {
            int n;
        
            sscanf (l, "%d", &n);
            l = skip_numbers (l);
            tokens[t_count].kind = t_num;
            tokens[t_count++].val = n;
        } else 
            if (*l == '(') {
                tokens[t_count++].kind = t_br_o;
                l++;
            } else 
                if (*l == ')') {
                    tokens[t_count++].kind = t_br_c;
                    l++;
                }
                else
                    l++;
    }
}


void print ()
{
    int op = 0;
    printf ("%d=", result);

    do_print (root, op);
    printf ("\n");
}


bool solve (int level)
{
    if (level == ops_max) {
        return check ();
    }

    ops[level] = 0;
    if (solve (level+1))
        return true;
    ops[level] = 1;
    if (solve (level+1))
        return true;
    ops[level] = 2;
    if (solve (level+1))
        return true;
    return false;
}


bool check ()
{
    int op = 0;
    return do_eval (root, op) == result;
}


void do_print (expr_t* p, int& op)
{
    int op_new;

    switch (p->kind) {
    case expr_op:
        op_new = op+1;
        do_print (p->left, op_new);
        printf ("%c", ops_table[ops[op]]);
        op = op_new;
        do_print (p->right, op);
        break;

    case expr_br:
        printf ("(");
        do_print (p->left, op);
        printf (")");
        break;

    case expr_num:
        printf ("%d", p->num);
    }
}



int do_eval (expr_t* p, int& op)
{
    int op_cur = op;
    int a, b;

    switch (p->kind) {
    case expr_op:
        op++;
        a = do_eval (p->left, op);
        b = do_eval (p->right, op);

        if (ops[op_cur] == 0)
            return a+b;
        else
            if (ops[op_cur] == 1)
                return a-b;
            else
                if (ops[op_cur] == 2)
                    return a*b;
        break;

    case expr_br:
        return do_eval (p->left, op);

    case expr_num:
        return p->num;
    }
}
