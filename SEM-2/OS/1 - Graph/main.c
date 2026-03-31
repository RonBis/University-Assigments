#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num_verts;
    int** adj_mat;
} graph;

typedef struct {
    int* arr;
    int top, max;
} stack;

stack new_stack(int max_size) {
    int* stack_arr = (int*)calloc(max_size, sizeof(int));
    return (stack){.arr = stack_arr, .top = -1, .max = max_size};
}

void stack_push(stack* st, int node) {
    (st->top)++;
    st->arr[st->top] = node;
}

int pop(stack* st) {
    int node = st->arr[st->top];
    (st->top)--;
    return node;
}

void display_graph(graph* G) {
    printf("----- Graph (Adjacency Matrix) -----\n");

    int N = G->num_verts;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d  ", G->adj_mat[i][j]);
        }
        printf("\n");
    }
}

void performDFS(graph* G, int start_node, int* visited_array) {
    printf("\n----- DFS -----\n");

    int* stack_arr = (int*)malloc(sizeof(int) * G->num_verts);
    stack st = {.arr = stack_arr, .top = -1, .max = G->num_verts};

    // Explicitly visit starting node
    visited_array[start_node] = 1;
    stack_push(&st, start_node);

    while (st.top != -1) {
        int explore_node = pop(&st);
        printf("Visited: %d\n", explore_node + 1);

        for (int i = 0; i < G->num_verts; i++) {
            // If neighbour is not visited, push node
            if (G->adj_mat[explore_node][i] == 1 && visited_array[i] == 0) {
                visited_array[i] = 1;
                stack_push(&st, i);
            }
        }
    }

    free(stack_arr);
}

int main() {
    FILE* fp = fopen("graph.txt", "r");
    if (!fp) {
        printf("Error opening file");
        return 1;
    }

    int u, v;
    int maxNode = 0;

    // First pass: find max node
    while (fscanf(fp, "%d %d", &u, &v) == 2) {
        if (u > maxNode) maxNode = u;
        if (v > maxNode) maxNode = v;
    }
    rewind(fp);

    // Allocate adjacency matrix
    int* data_block = (int*)malloc(maxNode * maxNode * sizeof(int));
    int** row_pointers = (int**)malloc(maxNode * sizeof(int*));

    for (int i = 0; i < maxNode; i++) {
        row_pointers[i] = &data_block[i * maxNode];
    }
    // Initialize all values to zero
    for (int i = 0; i < maxNode; i++) {
        for (int j = 0; j < maxNode; j++) {
            row_pointers[i][j] = 0;
        }
    }

    // Second pass: Construct adjacency list
    while (fscanf(fp, "%d %d", &u, &v) == 2) {
        row_pointers[u - 1][v - 1] = 1;  // Directed Graph
    }
    fclose(fp);

    graph* G = (graph*)malloc(sizeof(graph));
    G->num_verts = maxNode;
    G->adj_mat = row_pointers;

    display_graph(G);
    printf("\n");

    // Number of components = Number of DFS calls
    int component_count = 0;
    int num_nodes_visited_in_dfs = 0;

    int* visited_array = (int*)calloc(G->num_verts, sizeof(int));

    stack central_vertices = new_stack(G->num_verts);

    // performDFS(G, 1, visited_array);
    // component_count++;

    for (int i = 0; i < G->num_verts; i++) {
        if (visited_array[i] == 0) {
            performDFS(G, i, visited_array);
            component_count++;

            // push i to central_vertices stack
            stack_push(&central_vertices, i);
        }
    }

    printf("\nNo of components: %d", component_count);

    printf("\n----- Central Vertices ----\n");
    for (int i = 0; i <= central_vertices.top; i++) {
        printf("%2d, ", central_vertices.arr[i] + 1);
    }

    printf("\n");
    return 0;
}
