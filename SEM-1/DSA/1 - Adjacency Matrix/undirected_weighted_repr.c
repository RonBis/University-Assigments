#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int num_verts;
    int** adj_mat;
} graph;

graph* input_graph();
void display_graph(graph*);
void free_graph(graph*);

int main() {
    graph* G = input_graph();
    if (!G) return -1;

    display_graph(G);
    free_graph(G);
    return 0;
}

graph* input_graph() {
    int N;
    printf("Enter number of nodes: ");
    scanf("%d", &N);

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

    printf("Enter edge weights - 0 for no edge, otherwise else\n\n");
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            printf("Edge weight %d<->%d? ", i, j);
            scanf("%d", &row_pointers[i][j]);
            // Copy value to position [j][i]
            row_pointers[j][i] = row_pointers[i][j];
        }
        printf("\n");
    }

    graph* G = (graph*)malloc(sizeof(graph));
    G->num_verts = N;
    G->adj_mat = row_pointers;
    return G;
}

void display_graph(graph* G) {
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
