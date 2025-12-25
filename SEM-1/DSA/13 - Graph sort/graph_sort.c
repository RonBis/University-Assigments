#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int* arr;
} IntArray;

typedef struct {
    int num_verts;
    int** adj_mat;
    int* delisted;
    int* in_degree_list;
} Graph;

IntArray* input_array();
void graph_sort(IntArray* intArray);
Graph* init_graph(IntArray* intArray);

int main() {
    IntArray* intArray = input_array();
    graph_sort(intArray);
    return 0;
}

IntArray* input_array() {
    IntArray* intArray = (IntArray*)malloc(sizeof(IntArray));

    printf("Enter no of elements: ");
    scanf("%d", &intArray->size);

    int N = intArray->size;
    int* arr = (int*)malloc(N * sizeof(int));
    printf("Enter array elements one by one:\n");
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    intArray->arr = arr;
    return intArray;
}

void graph_sort(IntArray* intArray) {
    // Construct initial graph
    Graph* G = init_graph(intArray);

    for (int i = 0; i < intArray->size; i++) {
        printf("%d -> %d\n", intArray->arr[i], G->in_degree_list[i]);
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
