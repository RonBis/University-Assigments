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
void performBFS_shortest_path(graph*);

typedef struct Queue {
    int* arr;
    int front, rear, MAX;
} queue;

void enqueue(queue* q, int node) {
    if (q->front == -1 && q->rear == -1) {
        q->front = 0, q->rear = 0;
    } else {
        (q->rear)++;
    }
    q->arr[q->rear] = node;
}

int dequeue(queue* q) {
    int node = q->arr[q->front];
    (q->front)++;
    return node;
}

void free_queue(queue* q) { free(q->arr); }

void print_path(int* parent, int start, int end) {
    if (end == start) {
        printf("%d", start);
        return;
    }
    if (parent[end] == -1) {
        printf("No path exists");
        return;
    }
    print_path(parent, start, parent[end]);
    printf(" -> %d", end);
}

int main() {
    graph* G = input_graph();
    if (!G) return -1;

    display_graph(G);
    printf("\n");
    performBFS_shortest_path(G);

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

void performBFS_shortest_path(graph* G) {
    printf("----- BFS Shortest Path -----\n\n");

    int start, end;
    printf("Enter starting node: ");
    scanf("%d", &start);
    printf("Enter ending node: ");
    scanf("%d", &end);

    if (start < 0 || start >= G->num_verts || end < 0 || end >= G->num_verts) {
        printf("Invalid starting and/or ending node(s).\n");
        return;
    }

    int* visited_array = (int*)calloc(G->num_verts, sizeof(int));
    int* distance = (int*)malloc(G->num_verts * sizeof(int));
    int* parent = (int*)malloc(G->num_verts * sizeof(int));
    
    // Initialize distances and parents with -1
    for (int i = 0; i < G->num_verts; i++) {
        distance[i] = -1;  // -1 means unreachable
        parent[i] = -1;
    }
    
    int* queue_arr = (int*)malloc(sizeof(int) * G->num_verts);
    queue q = {.arr = queue_arr, .front = -1, .rear = -1, .MAX = G->num_verts};

    // BFS from start node
    enqueue(&q, start);
    visited_array[start] = 1;
    distance[start] = 0;

    int found = 0;
    while (q.front <= q.rear) {
        int u = dequeue(&q);

        // Early exit if we found the target
        if (u == end) {
            found = 1;
            break;
        }

        for (int v = 0; v < G->num_verts; v++) {
            if (G->adj_mat[u][v] == 1 && visited_array[v] == 0) {
                visited_array[v] = 1;
                distance[v] = distance[u] + 1;
                parent[v] = u;
                enqueue(&q, v);
            }
        }
    }

    printf("\n");
    if (distance[end] == -1) {
        printf("No path exists from %d to %d\n", start, end);
    } else {
        printf("Shortest distance from %d to %d: %d\n", start, end,
               distance[end]);
        printf("Path: ");
        print_path(parent, start, end);
        printf("\n");
    }

    free(visited_array);
    free(distance);
    free(parent);
    free_queue(&q);
}
