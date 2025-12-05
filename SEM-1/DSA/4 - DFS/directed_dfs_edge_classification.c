#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num_verts;
    int** adj_mat;
} graph;

graph* input_graph();
void display_graph(graph*);
void free_graph(graph*);

typedef struct {
    int* visited;
    int* discovery;
    int* finish;
    int time;
} DFSState;

void performDFS(graph*);
void dfs_recursive_directed(int, DFSState*, graph*);

int main() {
    // graph* G = input_graph();
    graph* G = (graph*)malloc(sizeof(graph));
    G->num_verts = 12;
    int adj_mat[12][12] = {
        {0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,},  
        {1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,},  
        {1,  1,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,},  
        {1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,},  
        {0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,},  
        {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,},  
        {0,  0,  1,  0,  0,  0,  0,  1,  1,  0,  0,  0,},  
        {0,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,},  
        {0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,},  
        {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,}, 
        {0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,},  
        {0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,}, 
    };
    int **dynamic_arr = malloc(12 * sizeof(int*));
    for (int i = 0; i < 12; i++) {
        dynamic_arr[i] = malloc(12 * sizeof(int));
        for (int j = 0; j < 12; j++) {
            dynamic_arr[i][j] = adj_mat[i][j]; // copy values
        }
    }
    G->adj_mat = dynamic_arr;

    if (!G) return -1;

    display_graph(G);
    printf("\n");
    performDFS(G);
    free_graph(G);
    printf("\n");
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

    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            printf("Is there an edge %d<->%d? (1/0): ", i, j);
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

    DFSState state;
    state.visited = (int*)calloc(G->num_verts, sizeof(int));
    state.discovery = (int*)malloc(G->num_verts * sizeof(int));
    state.finish = (int*)malloc(G->num_verts * sizeof(int));
    state.time = 0;

    int start_node;
    printf("Enter starting node: ");
    scanf("%d", &start_node);
    start_node = start_node - 1;
    if (start_node < 0 || start_node > G->num_verts - 1) {
        printf("Invalid starting node.");
        free(state.visited);
        free(state.discovery);
        free(state.finish);
        free_graph(G);
        exit(-1);
    }

    dfs_recursive_directed(start_node, &state, G);
    // Check if all edges are visited
    for (int u=0; u<G->num_verts; u++) {
        if (state.visited[u] != 2) {
            dfs_recursive_directed(u, &state, G);
        }
    }

    free(state.visited);
    free(state.discovery);
    free(state.finish);
}

void dfs_recursive_directed(int u, DFSState* state, graph* G) {
    state->visited[u] = 1;  // Mark as being processed
    state->discovery[u] = ++(state->time);
    printf("\nVisited: %d (time: %d)\n", u+1, state->discovery[u]);

    for (int v = 0; v < G->num_verts; v++) {
        if (G->adj_mat[u][v] == 1) {
            if (state->visited[v] == 0) {
                // Tree edge
                printf("Tree edge: (%d, %d)\n", u+1, v+1);
                dfs_recursive_directed(v, state, G);
            } 
            else if (state->visited[v] == 1) {
                // Back edge (v is an ancestor, still being processed)
                printf("Back edge: (%d, %d)\n", u+1, v+1);
            }
            else if (state->visited[v] == 2) {
                // v is finished
                if (state->discovery[u] < state->discovery[v]) {
                    // Forward edge (u was discovered before v)
                    printf("Forward edge: (%d, %d)\n", u+1, v+1);
                } else {
                    // Cross edge (v was discovered before u)
                    printf("Cross edge: (%d, %d)\n", u+1, v+1);
                }
            }
        }
    }
    
    state->visited[u] = 2;  // Mark as finished
    state->finish[u] = ++(state->time);
}
