#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int num_verts;
    int** adj_mat;
} graph;

graph* input_graph();
void display_graph(graph*);
void free_graph(graph*);
void performDFS(graph*, int, int*);

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

    // Number of components = Number of DFS calls
    int component_count = 0;
    int* visited_array = (int*)calloc(G->num_verts, sizeof(int));
    for (int i=0; i<G->num_verts; i++) {
        if (visited_array[i] == 0) {
            performDFS(G, i, visited_array);
            component_count++;
        }
    }

    printf("\nNo of components: %d", component_count);

    free(visited_array);
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
            printf("Is there an edge %d<-->%d ? (1/0): ", i, j);
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
void performDFS(graph* G, int start_node, int* visited_array) {
    printf("\n----- DFS -----\n");

    int* stack_arr = (int*)malloc(sizeof(int) * G->num_verts);
    stack st = {.arr = stack_arr, .top = -1, .MAX = G->num_verts};

    // Explicitly visit starting node
    visited_array[start_node] = 1;
    push(&st, start_node);

    while (st.top != -1) {
        int explore_node = pop(&st);
        printf("Visited: %d\n", explore_node+1);

        for (int i = 0; i < G->num_verts; i++) {
            // If neighbour is not visited, push node
            if (G->adj_mat[explore_node][i] == 1 && visited_array[i] == 0) {
                visited_array[i] = 1;
                push(&st, i);
            }
        }
    }

    free(stack_arr);
}

// 0  1  1  1  0  0  0  0  0  0  0  0  
// 1  0  1  0  0  0  0  0  0  0  0  0  
// 1  1  0  0  1  0  1  0  0  0  0  0  
// 1  0  0  0  1  0  0  0  0  0  0  0  
// 0  0  1  1  0  0  0  0  0  0  0  0  
// 0  0  0  0  0  0  0  0  0  0  0  0  
// 0  0  1  0  0  0  0  1  1  0  0  0  
// 0  0  0  0  0  0  1  0  1  0  0  0  
// 0  0  0  0  0  0  1  1  0  0  0  0  
// 0  0  0  0  0  0  0  0  0  0  1  1  
// 0  0  0  0  0  0  0  0  0  1  0  0  
// 0  0  0  0  0  0  0  0  0  1  0  0 