#include <stdio.h>
#include <stdlib.h>

typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} adj_list_node;

typedef struct AdjList {
    adj_list_node* head;
} adj_list;

typedef struct GraphList {
    int num_verts;
    adj_list* adj_list;
} graph_list;

graph_list* input_graph();
void display_graph(graph_list*);
void free_graph(graph_list*);
adj_list_node* create_node(int dest, int weight);

int main() {
    graph_list* G = input_graph();
    if (!G) return -1;

    display_graph(G);
    free_graph(G);
    return 0;
}

adj_list_node* create_node(int dest, int weight) {
    adj_list_node* newNode = (adj_list_node*)malloc(sizeof(adj_list_node));
    if (!newNode) return NULL;
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

graph_list* input_graph() {
    int N, E;
    printf("Enter number of nodes: ");
    scanf("%d", &N);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    graph_list* G = (graph_list*)malloc(sizeof(graph_list));
    if (!G) return NULL;

    G->num_verts = N;
    G->adj_list = (adj_list*)malloc(N * sizeof(adj_list));
    if (!G->adj_list) {
        free(G);
        return NULL;
    }

    // Initialize each adjacency list as empty
    for (int i = 0; i < N; i++) {
        G->adj_list[i].head = NULL;
    }

    printf("Enter edges (from to weight):\n");
    for (int i = 0; i < E; i++) {
        int from, to, weight;
        printf("Edge %d: ", i);
        scanf("%d %d %d", &from, &to, &weight);

        if (from < 0 || from >= N || to < 0 || to >= N) {
            printf("Invalid vertex! Please enter vertices between 0 and %d\n",
                   N - 1);
            i--;
            continue;
        }

        // Add edge from->to with weight (directed weighted graph)
        adj_list_node* newNode = create_node(to, weight);
        if (!newNode) {
            free_graph(G);
            return NULL;
        }

        // Insert at beginning of adjacency list
        newNode->next = G->adj_list[from].head;
        G->adj_list[from].head = newNode;
    }

    return G;
}

void display_graph(graph_list* G) {
    int N = G->num_verts;

    printf("\nAdjacency List:\n");
    for (int i = 0; i < N; i++) {
        printf("Vertex %d: ", i);
        adj_list_node* current = G->adj_list[i].head;
        while (current) {
            printf("-> %d(w:%d) ", current->dest, current->weight);
            current = current->next;
        }
        printf("-> NULL\n");
    }
}

void free_graph(graph_list* G) {
    if (!G) return;

    if (G->adj_list) {
        for (int i = 0; i < G->num_verts; i++) {
            adj_list_node* current = G->adj_list[i].head;
            while (current) {
                adj_list_node* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(G->adj_list);
    }
    free(G);
}
