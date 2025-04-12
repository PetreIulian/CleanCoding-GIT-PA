/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct graph {
    int vertex;
    int *visited;
    struct Node **adjacency_list;
} GRAPH;

typedef struct s {
  int top;
  int dimension;
  int *arr;
} STACK;

NODE *create_node(int value) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = value;
    new_node->next = NULL;

    return new_node;
}

void add_edge(GRAPH *g,int source,int destination) {
    NODE *new_node = create_node(destination);
    new_node->next = g->adjacency_list[source];
    g->adjacency_list[source] = new_node;

    new_node = create_node(source);
    new_node->next = g->adjacency_list[destination];
    g->adjacency_list[destination] = new_node;
}

GRAPH *create_graph(int vertex) {
    int i;
    GRAPH *g = malloc(sizeof(GRAPH));
    g->vertex=vertex;
    g->adjacency_list = malloc(sizeof(NODE *) * vertex);
    g->visited = malloc(sizeof(int) * vertex);

    for (int i = 0; i < vertex; i++) {
        g->adjacency_list[i] = NULL;
        g->visited[i] = 0;
    }

    return g;
}

STACK *create_stack(int dimension) {
    STACK *s = malloc(sizeof(STACK));
    s->arr = malloc(dimension * sizeof(int));

    s->top = -1;
    s->dimension = dimension;

    return s;
}

void push(int value, STACK *s) {
    s->top = s->top + 1;
    s->arr[s->top] = value;
}

void DFS(GRAPH *graph, STACK *stack, int vertex_number, int target, int *found) {
   if (*found) {
     return;
   }

   NODE *adj_list = graph->adjacency_list[vertex_number];
   NODE *aux = adj_list;
   graph->visited[vertex_number] = 1;

   while (aux != NULL) {
     if (aux->data == target) {
       *found = 1;
       break;
     }
     aux = aux->next;
   }

   if (!found) {
     while (adj_list != NULL) {
       if (!graph->visited[adj_list->data]) {
         DFS(graph, stack, adj_list->data, target, found);
       }
       adj_list = adj_list->next;
     }
   }
}


void path_search(GRAPH *g) {
   int vertex_1, vertex_2;

   printf("Verifica existenta drumului direct intre: ");
   scanf("%d %d", &vertex_1, &vertex_2);

   for (int i = 0; i < g->vertex; i++) {
     g->visited[i] = 0;
   }

   int found = 0;
   STACK *stack = create_stack(g->vertex);

   DFS(g, stack, vertex_1, vertex_2, &found);

   if (found) {
     printf("Exista drum direct intre %d si %d.\n", vertex_1, vertex_2);
   }
   else {
     printf("Nu exista drum direct intre %d si %d.\n", vertex_1, vertex_2);
   }
}

int main(void) {
    int number_of_vertices;
    int number_of_edges;

    printf("Cate noduri are graful?");
    scanf("%d", &number_of_vertices);
    printf("Cate muchii are graful?");
    scanf("%d", &number_of_edges);

    GRAPH *g = create_graph(number_of_vertices);

    printf("Intrdouceti %d muchii (sursa,  destinatie):\n", number_of_edges);

    for (int i = 0; i < number_of_edges; i++) {
      int source, destination;
      scanf("%d %d", &source, &destination);
      add_edge(g, source, destination);
    }

   path_search(g);

   free(g->visited);
   free(g->adjacency_list);
   free(g);

   return 0;
}