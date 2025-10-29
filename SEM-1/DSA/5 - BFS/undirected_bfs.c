#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int num_verts;
    int** adj_mat;
} graph;

graph* input_graph();
void display_graph(graph*);
void free_graph(graph*);
void performBFS(graph*);

int *queue, front = -1, rear = -1;
void enqueue(int node);
int dequeue();

int main() {
    graph* G = input_graph();
    if (!G) return -1;

    display_graph(G);
    printf("\n");
    performBFS(G);
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

// ----- BFS ----- //
void performBFS(graph* G) {
    printf("----- BFS -----\n\n");

    int* visited_array = (int*)calloc(G->num_verts, sizeof(int));
    queue = (int*)malloc(sizeof(int) * G->num_verts);

    int start_node;
    printf("Enter starting node: ");
    scanf("%d", &start_node);
    if (start_node < 0 || start_node > G->num_verts-1) {
        printf("Invalid starting node.");
        exit(-1);
    }

    enqueue(start_node);
    while (front <= rear) {
        int visited_node = dequeue();
        visited_array[visited_node] = 1;
        printf("Visited: %d\n", visited_node);
        
        for (int i=0; i<G->num_verts; i++) {
            // If neighbour is not visited, enqueue node
            if (G->adj_mat[visited_node][i] == 1 && visited_array[i] == 0) {
                enqueue(i);
            }
        }
    }
}

void enqueue(int node) {
    if (front == -1 && rear == -1) {
        front = 0;
        rear = 0;
    } else {
        rear++;
    }
    queue[rear] = node;
}
int dequeue() {
    int node = queue[front];
    front++;
    return node;
}
