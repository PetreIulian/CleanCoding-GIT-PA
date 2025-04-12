/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

//Definirea structurii unui nod
typedef struct Node {
    int data;
    struct Node *next;
} NODE;

//Definirea structurii pentru graf
typedef struct graph {
    int vertex;
    int *visited; //Vector pentru a marca nodurile vizitate în timpul DFS
    struct Node **adjacency_list; // Listă de adiacență pentru fiecare nod
} GRAPH;

typedef struct stack {
  int top;
  int dimension;
  int *arr; // Vector pentru elementele stivei
} STACK;

// Crearea unui nod nou în listă
NODE *create_node(int value) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = value;
    new_node->next = NULL;

    return new_node;
}

// Adăugarea unei muchii între două noduri
void add_edge(GRAPH *g,int source,int destination) {
    NODE *new_node = create_node(destination);
    new_node->next = g->adjacency_list[source]; //Adaugă destinația la începutul listei de adiacență a sursei
    g->adjacency_list[source] = new_node; //Actualizează lista de adiacență a sursei

    new_node = create_node(source);
    new_node->next = g->adjacency_list[destination]; //Adaugă sursa la începutul listei de adiacență a destinației
    g->adjacency_list[destination] = new_node; //Actualizează lista de adiacență a destinației
}

//Crearea grafului
GRAPH *create_graph(int vertex) {
    int i;
    GRAPH *g = malloc(sizeof(GRAPH));
    g->vertex=vertex;
    g->adjacency_list = malloc(sizeof(NODE *) * vertex);
    g->visited = malloc(sizeof(int) * vertex);

    //Inițializare: niciun nod nu este vizitat și niciun nod nu are vecini
    for (int i = 0; i < vertex; i++) {
        g->adjacency_list[i] = NULL;
        g->visited[i] = 0;
    }

    return g;
}

//Crearea unei stive
STACK *create_stack(int dimension) {
    STACK *s = malloc(sizeof(STACK));
    s->arr = malloc(dimension * sizeof(int));

    s->top = -1;
    s->dimension = dimension;

    return s;
}

//Funcție pentru a adăuga un element în stivă
void push(int value, STACK *s) {
    s->top = s->top + 1;
    s->arr[s->top] = value;
}

//Implementarea DFS
void DFS(GRAPH *graph, STACK *stack, int vertex_number, int target, int *found) {
   if (*found) {
     return;
   }

   NODE *adj_list = graph->adjacency_list[vertex_number]; //Obținem lista de adiacență a nodului curent
   NODE *aux = adj_list;
   graph->visited[vertex_number] = 1; //Marcăm nodul curent ca vizitat

   //Căutăm în lista de vecini dacă există un drum direct către nodul țintă
   while (aux != NULL) {
     if (aux->data == target) {
       *found = 1; //S-a gasit drum direct
       break;
     }
     aux = aux->next;
   }

    //Apelare recursiv DFS pentru vecinii nodului curent
   if (!found) {
     while (adj_list != NULL) {
       if (!graph->visited[adj_list->data]) {
         DFS(graph, stack, adj_list->data, target, found);
       }
       adj_list = adj_list->next;
     }
   }
}


//Funcția pentru a verifica dacă există un drum direct între două noduri
void path_search(GRAPH *g) {
   int vertex_1, vertex_2;

   printf("Verifica existenta drumului direct intre: ");
   scanf("%d %d", &vertex_1, &vertex_2);

   //Resetarea nodurilor vizitate pentru intregul graf
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
      add_edge(g, source, destination); //Adăugăm fiecare muchie în graf
    }

   path_search(g);

   free(g->visited);
   free(g->adjacency_list);
   free(g);

   return 0;
}