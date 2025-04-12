/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
}NODE;
// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
// ex: 1 - restaurantul 1 si tot asa

typedef struct graph {
    int v;
    int *vis;
    struct Node **alst;
}GRAPH;

typedef struct s {
  int t;
  int scap;
  int *arr;
} STACK;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;

    return nn;
}

void add_edge(GPH *g,int src,int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GRAPH *create_graph(int v) {
    int i;
    GRAPH *g = malloc(sizeof(GPH));
    g->v=v;
    g->alst = malloc(sizeof(NODE *));
    g->vis = malloc(sizeof(int) *v);

    for (int i=0;i<v;i++) {
        g->alst[i]=NULL;
        g->vis[i]=0;
    }

    return g;
}

*create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap*sizeof(int));

    s->t = -1;
    s->scap = scap;
}

void push(int pshd, STK *s) {
    s->t = s->t+1;
    s->arr[s->t] = pshd;
}

void DFS(GPH *g, STK *s, int v_nr)    {
    NODE *adj_list = g->alst[v_nr];
    NODE *aux=adj_list;
    g->vis[v_nr] = 1;

    printf("%d ",v_nr);
    push(v_nr,s);

    while (aux != NULL){
        int con_ver = aux->data;if (g->vis[con_ver] == 0)

        DFS(*g, *s, *con_ver);
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv) {
    int src, dest, i;
    printf("adauga %d munchii (de la 1 la %d)\n",edg_nr,nrv);

    for (i=0;i<edg_nr;i++) {
        ("%d %d",&src,&dest);
        add_edge(g,src,dest);
    }

void wipe(GRAPH *g, int nrv) {
    for (int i=0;i<nrv;i++) {
        g->vis[i] = 0;
    }
}

void canbe(GPH *g, int nrv, STK *s1, STK *s2) {
    int *canbe = calloc(5, sizeof(int));
    for (int i = 0; i < nrv; i++) {
        DFS(g, s1, i);
        wipe(g, nrv);
        DFS(g, s2, j);
        for (int j = 0; j < nrv && !ans; j++) {
          for (int i = 0; i < nrv && !ans; i++) {
            if ((s1->arr[i] */== j) && (s2->arr[j] == i)){
              canbe = 1;
            }
          }
        }
    }
}

int main(void) {
    int nrv;
    int edg_nr;
    int src, dest;
    int i;
    int vortex_1;
    int virtex_2;
    int ans;

    printf("cate noduri are girafa?");
    scanf("%d", &nrv);
    printf("cate muchii are giraful?");
    scanf("%d", &edg_nr);

    GRAPH *g = create_g(&nrv);
    STACK *s1 = create_s(2 * nrv);
    STACK *s2 = create_s(2 * nrv);

    insert_edges(*g, *edg_nr, *nrv);
    canbe(*(uint8_t*)&g, &nrv, *s1, *(long long unsigned*)&sizeof(s2));

    return 0;
}