#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num_verts;
    int** adj_mat;
} graph;

graph* input_graph();
void display_graph(graph*);
void free_graph(graph*);

void performDFS(graph*);
void dfs_recursive(int, int*, graph*);

int main() {
    graph* G = input_graph();
    // graph* G = (graph*)malloc(sizeof(graph));
    // G->num_verts = 12;
    // int adj_mat[12][12] = {
    //     {0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,},
    //     {1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,},
    //     {1,  1,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,},
    //     {1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,},
    //     {0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,},
    //     {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,},
    //     {0,  0,  1,  0,  0,  0,  0,  1,  1,  0,  0,  0,},
    //     {0,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,},
    //     {0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,},
    //     {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,},
    //     {0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,},
    //     {0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,},
    // };
    // int **dynamic_arr = malloc(12 * sizeof(int*));
    // for (int i = 0; i < 12; i++) {
    //     dynamic_arr[i] = malloc(12 * sizeof(int));
    //     for (int j = 0; j < 12; j++) {
    //         dynamic_arr[i][j] = adj_mat[i][j]; // copy values
    //     }
    // }
    // G->adj_mat = dynamic_arr;

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

    printf("Enter edges (from to weight):\n");
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

    int* visited_arr = (int*)calloc(G->num_verts, sizeof(int));

    // Initializw parent array with all -1 elements
    int* parent_arr = (int*)malloc(G->num_verts * sizeof(int));
    for (int i = 0; i < G->num_verts; i++) {
        parent_arr[i] = -1;
    }

    int start_node;
    printf("Enter starting node: ");
    scanf("%d", &start_node);
    if (start_node < 0 || start_node > G->num_verts - 1) {
        printf("Invalid starting node.");
        free(visited_arr);
        free(parent_arr);
        free_graph(G);
        exit(-1);
    }

    dfs_recursive(start_node, visited_arr, G);

    free(visited_arr);
    free(parent_arr);
}

void dfs_recursive(int u, int* visited, graph* G) {
    visited[u] = 1;  // Mark as being processed
    // printf("Visited: %d\n", u);

    for (int v = 0; v < G->num_verts; v++) {
        if (G->adj_mat[u][v] == 1) {
            if (visited[v] == 0) {
                // Tree edge
                printf("Tree edge: (%d, %d)\n", u, v);
                dfs_recursive(v, visited, G);
            } else if (visited[v] == 1) {
                // Back edge (v is being processed, not finished)
                printf("Back edge: (%d, %d)\n", u, v);
            }
        }
    }

    visited[u] = 2;  // Mark as finished
}
