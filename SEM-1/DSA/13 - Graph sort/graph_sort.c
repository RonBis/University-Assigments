#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int* arr;
} IntArray;

IntArray* new_intarray(int size) {
    IntArray* intArray = (IntArray*)malloc(sizeof(IntArray));
    int* arr = (int*)malloc(size * sizeof(int));
    intArray->arr = arr;
    intArray->size = size;
    return intArray;
}

typedef struct {
    int top;
    int* arr;
    int max;
} Stack;

Stack* new_stack(int size) {
    Stack* st = (Stack*)malloc(sizeof(Stack));
    int* arr = (int*)malloc(size * sizeof(int));
    st->arr = arr;
    st->max = size;
    st->top = -1;
    return st;
}

static inline bool is_stack_empty(Stack* st) { return st->top == -1; }

void push_to_stack(Stack* st, int data) {
    if (st->top == st->max - 1) {
        printf("Stack overflow!\n");
        return;
    }
    st->arr[++(st->top)] = data;
}

int pop_from_stack(Stack* st) {
    if (is_stack_empty(st)) {
        printf("Stack underflow!\n");
        return -9999;
    }
    int popped = st->arr[st->top];
    (st->top)--;
    return popped;
}

void display_stack(Stack* st) {
    printf("\nStack:\n");
    for (int i = 0; i <= st->top; i++) {
        printf("%d\t", st->arr[i]);
    }
    printf("\n");
}

typedef struct {
    int num_verts;
    int** adj_mat;
    int* delisted;
    int* in_degree_list;
} Graph;

void print_indegrees(IntArray* intArray, Graph* G);
IntArray* input_array();
void graph_sort(IntArray* intArray);
Graph* init_graph(IntArray* intArray);

int main() {
    // IntArray* intArray = input_array();
    int numbers[] = {4, 2, 1, 4, 3, 5, 4, 3, 1};
    IntArray intArray = (IntArray){
        .arr = numbers, .size = sizeof(numbers) / sizeof(numbers[0])};

    graph_sort(&intArray);

    printf("\n");
    return 0;
}

void print_indegrees(IntArray* intArray, Graph* G) {
    printf("El\t->\tIn Degree\n");
    for (int i = 0; i < intArray->size; i++) {
        printf("%d\t->\t%d\n", intArray->arr[i], G->in_degree_list[i]);
    }
}

IntArray* input_array() {
    int N;
    printf("Enter no of elements: ");
    scanf("%d", &N);

    IntArray* intArray = new_intarray(N);
    printf("Enter array elements one by one:\n");
    for (int i = 0; i < N; i++) {
        scanf("%d", &intArray->arr[i]);
    }
    return intArray;
}

void graph_sort(IntArray* intArray) {
    printf("No of elements: %d\n\n", intArray->size);

    Graph* G = init_graph(intArray);  // Construct initial graph
    Stack* src_stack =
        new_stack(intArray->size);  // Stack containing source vertices

    // Find vertices with in-degree zero and push them to stack
    for (int i = 0; i < intArray->size; i++) {
        if (G->in_degree_list[i] == 0) {
            push_to_stack(src_stack, i);
        }
    }
    int iter = 0;
    do {
        // Vertex with highest positional value will always be at the top
        int src_vertex_id = pop_from_stack(src_stack);
        int src_node = intArray->arr[src_vertex_id];

        // Update sorted array
        G->delisted[iter] = src_node;

        // Find the neighbours of the popped vertex and update in-degrees
        for (int i = 0; i < G->num_verts; i++) {
            if (G->adj_mat[src_vertex_id][i] == 1) {
                G->in_degree_list[i] -= 1;
                if (G->in_degree_list[i] == 0) {
                    push_to_stack(src_stack, i);
                }
            }
        }

        iter++;
    } while (!is_stack_empty(src_stack));

    for (int i = 0; i < G->num_verts; i++) {
        printf("%d\t", G->delisted[i]);
    }
}

Graph* init_graph(IntArray* intArray) {
    int N = intArray->size;
    int* arr = intArray->arr;

    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->num_verts = N;
    G->delisted = (int*)malloc(N * sizeof(int));
    G->in_degree_list = (int*)malloc(N * sizeof(int));

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
        for (int j = i + 1; j < N; j++) {
            row_pointers[i][j] = (arr[i] <= arr[j]) ? 1 : 0;
            // Set In-Degree
            if (row_pointers[i][j] == 1) {
                G->in_degree_list[j] = G->in_degree_list[j] + 1;
            }
        }
    }

    G->adj_mat = row_pointers;
    return G;
}
