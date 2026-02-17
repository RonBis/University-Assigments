#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int num_verts;
    int** adj_mat;
} graph;

graph* input_graph();
void display_graph(graph*);
void free_graph(graph*);
void performDFS(graph*);

typedef struct Stack {
    int* arr;
    int top, MAX;
} stack;

void push(stack* st, int node) {
    (st->top)++;
    st->arr[st->top] = node;
}
int pop(stack* st) {
    int node = st->arr[st->top];
    (st->top)--;
    return node;
}
void free_stack(stack* st) { free(st->arr); }

int main() {
    graph* G = input_graph();
    if (!G) return -1;

    display_graph(G);
    printf("\n");
    performDFS(G);
    free_graph(G);
    printf("\n");
    return 0;
}

graph* input_graph() {
    int N, E;
    printf("Enter number of nodes: ");
    scanf("%d", &N);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    // Allocate memory for N-node adjacency matrix
    int* data_block = (int*)malloc(N * N * sizeof(int));
    if (!data_block) return NULL;

    // Setup row pointers
    int** row_pointers = (int**)malloc(N * sizeof(int*));
    if (!row_pointers) {
        free(data_block);
        return NULL;
    }

    for (int i = 0; i < N; i++) {
        row_pointers[i] = &data_block[i * N];
    }

    // Initialize adjacency matrix to 0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < E; j++) {
            row_pointers[i][j] = 0;
        }
    }

    printf("Enter edges (from to):\n");
    for (int edge_idx = 0; edge_idx < E; edge_idx++) {
        int from, to;
        printf("Edge %d: ", edge_idx);
        scanf("%d %d", &from, &to);

        if (from < 0 || from >= N || to < 0 || to >= N) {
            printf("Invalid vertex! Please enter vertices between 0 and %d\n",
                   N - 1);
            edge_idx--;
            continue;
        }

        // For undirected unweighted graph:
        // 1 for incoming/outgoing edge (from/to vertex)
        row_pointers[from][to] = 1;
        row_pointers[to][from] = 1;
    }

    graph* G = (graph*)malloc(sizeof(graph));
    G->num_verts = N;
    G->adj_mat = row_pointers;
    return G;
}

void display_graph(graph* G) {
    printf("----- Graph -----\n\n");

    int N = G->num_verts;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d  ", G->adj_mat[i][j]);
        }
        printf("\n");
    }
}

void free_graph(graph* G) {
    if (!G) return;
    if (G->adj_mat) {
        if (G->num_verts > 0) {
            // Free data block
            free(G->adj_mat[0]);
        }
        // Free row pointers
        free(G->adj_mat);
    }
    free(G);
}

// ----- DFS ----- //
void performDFS(graph* G) {
    printf("----- DFS -----\n\n");

    int* visited_array = (int*)calloc(G->num_verts, sizeof(int));
    int* stack_arr = (int*)malloc(sizeof(int) * G->num_verts);

    stack st = {.arr = stack_arr, .top = -1, .MAX = G->num_verts};

    int start_node;
    printf("Enter starting node: ");
    scanf("%d", &start_node);
    if (start_node < 0 || start_node > G->num_verts - 1) {
        printf("Invalid starting node.");
        free(visited_array);
        free_stack(&st);
        free_graph(G);
        exit(-1);
    }

    // Explicitly visit starting node
    visited_array[start_node] = 1;
    push(&st, start_node);

    while (st.top != -1) {
        int explore_node = pop(&st);
        printf("Visited: %d\n", explore_node);
        
        for (int i = 0; i < G->num_verts; i++) {
            // If neighbour is not visited, push node
            if (G->adj_mat[explore_node][i] == 1 && visited_array[i] == 0) {
                visited_array[i] = 1;
                push(&st, i);
            }
        }
    }

    free(visited_array);
    free(stack_arr);
}
