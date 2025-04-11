#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int v;
    int *vis;
    NODE **alst;
} GPH;

typedef struct Stack {
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(v * sizeof(int));

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }

    return g;
}

STK *create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}


void push(int pshd, STK *s) {
    s->arr[++(s->t)] = pshd;
}

void DFS(GPH *g, STK *s, int v_nr) {
    NODE *aux = g->alst[v_nr];
    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);
    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0) {
            DFS(g, s, con_ver);
        }
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv) {
    int src, dest;
    printf("Adauga %d muchii (de la 0 la %d):\n", edg_nr, nrv - 1);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        if (src >= 0 && src < nrv && dest >= 0 && dest < nrv) {
            add_edge(g, src, dest);
        } else {
            printf("Muchie invalida: %d %d\n", src, dest);
            i--;
        }
    }
}

void wipe(GPH *g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}

void canbe(GPH *g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        for (int j = 0; j < nrv; j++) {
            if (i == j) continue;

            STK *s1 = create_s(nrv);
            STK *s2 = create_s(nrv);

            wipe(g, nrv);
            DFS(g, s1, i);

            wipe(g, nrv);
            DFS(g, s2, j);

            int found_i_in_s2 = 0, found_j_in_s1 = 0;
            for (int k = 0; k <= s1->t; k++) {
                if (s1->arr[k] == j) found_j_in_s1 = 1;
            }
            for (int k = 0; k <= s2->t; k++) {
                if (s2->arr[k] == i) found_i_in_s2 = 1;
            }

            if (found_i_in_s2 && found_j_in_s1) {
                printf("Nodurile %d si %d sunt interconectate.\n", i, j);
            }

            free(s1->arr);
            free(s1);
            free(s2->arr);
            free(s2);
        }
    }
}

int main() {
    int nrv, edg_nr;
    printf("Cate noduri are graful? ");
    scanf("%d", &nrv);

    printf("Cate muchii are graful? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);

    insert_edges(g, edg_nr, nrv);

    canbe(g, nrv);

    for (int i = 0; i < g->v; i++) {
        NODE *curr = g->alst[i];
        while (curr) {
            NODE *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(g->alst);
    free(g->vis);
    free(g);

    return 0;
}