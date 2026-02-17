#include <stdio.h>
#include <stdlib.h>

typedef struct GraphIncidence {
    int num_verts;
    int num_edges;
    int** inc_mat;
} graph_inc;

graph_inc* input_graph_incidence();
void display_graph_incidence(graph_inc*);
void free_graph_incidence(graph_inc*);

int main() {
    graph_inc* G = input_graph_incidence();
    if (!G) return -1;

    display_graph_incidence(G);
    free_graph_incidence(G);
    return 0;
}

graph_inc* input_graph_incidence() {
    int N, E;
    printf("Enter number of nodes: ");
    scanf("%d", &N);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    // Allocate memory for incidence matrix (vertices x edges)
    int* data_block = (int*)malloc(N * E * sizeof(int));
    if (!data_block) return NULL;

    // Setup row pointers
    int** row_pointers = (int**)malloc(N * sizeof(int*));
    if (!row_pointers) {
        free(data_block);
        return NULL;
    }

    for (int i = 0; i < N; i++) {
        row_pointers[i] = &data_block[i * E];
    }

    // Initialize incidence matrix to 0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < E; j++) {
            row_pointers[i][j] = 0;
        }
    }

    printf("Enter edges (from to weight):\n");
    for (int edge_idx = 0; edge_idx < E; edge_idx++) {
        int from, to, weight;
        printf("Edge %d: ", edge_idx);
        scanf("%d %d %d", &from, &to, &weight);

        if (from < 0 || from >= N || to < 0 || to >= N) {
            printf("Invalid vertex! Please enter vertices between 0 and %d\n",
                   N - 1);
            edge_idx--;
            continue;
        }

        // For undirected unweighted graph:
        // 1 for incoming/outgoing edge (from/to vertex)
        row_pointers[from][edge_idx] = 1;
        row_pointers[to][edge_idx] = 1;
    }

    graph_inc* G = (graph_inc*)malloc(sizeof(graph_inc));
    G->num_verts = N;
    G->num_edges = E;
    G->inc_mat = row_pointers;
    return G;
}

void display_graph_incidence(graph_inc* G) {
    int N = G->num_verts;
    int E = G->num_edges;

    printf("\nIncidence Matrix (%d vertices x %d edges):\n", N, E);
    printf("    ");
    for (int j = 0; j < E; j++) {
        printf("E%-4d", j);
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("V%-2d ", i);
        for (int j = 0; j < E; j++) {
            printf("%-5d", G->inc_mat[i][j]);
        }
        printf("\n");
    }
}

void free_graph_incidence(graph_inc* G) {
    if (!G) return;
    if (G->inc_mat) {
        if (G->num_verts > 0 && G->num_edges > 0) {
            free(G->inc_mat[0]);
        }
        free(G->inc_mat);
    }
    free(G);
}
