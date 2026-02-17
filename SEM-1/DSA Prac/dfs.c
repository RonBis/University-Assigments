#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
  int **adj_matrix;
  int n;
} Graph;

typedef struct DfsState {
  int *visited;
  int *discovery;
  int *finish;
  int time;
} DfsState;

Graph *input_graph();
void display_graph(Graph *G);
void perform_dfs(Graph *G);
void dfs_recursive(int start_node, DfsState *state, Graph *G);

int main() { return 0; }

Graph *input_graph() {
  int N, E;
  printf("Number of nodes: ");
  scanf("%d", &N);
  printf("Number of edges: ");
  scanf("%d", &E);

  // allocate memory for a N-node adjacency matrix
  int *data_block = (int *)calloc(N * N, sizeof(int));
  // setup row pointers
  int **row_pointers = (int **)malloc(N * sizeof(int *));
  for (int i = 0; i < N; i++) {
    row_pointers[i] = &data_block[i * N];
  }

  // take user input
  printf("Enter edges (from to):\n");
  for (int edge_index = 0; edge_index < E; edge_index++) {
    int from, to;
    printf("Edge %d: ", edge_index);
    scanf("%d %d", &from, &to);
    from--;
    to--;

    if (from < 1 || from > N || to < 0 || to > N) {
      printf("Invalid vertex id! Please enter vertex between 0 and %d\n", N);
      edge_index--;
      continue;
    }
    row_pointers[from][to] = 1;
  }

  Graph *G = (Graph *)malloc(sizeof(Graph));
  G->adj_matrix = row_pointers;
  G->n = N;
  return G;
}

void perform_dfs(Graph *G) {
  printf("----- DFS -----\n\n");

  DfsState state;
  state.visited = (int *)calloc(G->n, sizeof(int));
  state.discovery = (int *)calloc(G->n, sizeof(int));
  state.finish = (int *)calloc(G->n, sizeof(int));
  state.time = 0;

  int start_node;
  while (1) {
    printf("Starting node: ");
    scanf("%d", &start_node);
    start_node = start_node - 1;
    if (start_node < 1 || start_node > G->n) {
      printf("Invalid starting node!");
      continue;
    } else {
      break;
    }
  }

  dfs_recursive(start_node, &state, G);
}

void dfs_recursive(int u, DfsState *state, Graph *G) {
  state->visited[u] = 1; // Mark u as being processed
  state->discovery[u] = ++(state->time);
  printf("Visited: %d (time: %d)\n", u + 1, state->discovery[u]);

  for (int v = 0; v < G->n; v++) {
    if (G->adj_matrix[u][v] == 1) {
      if (state->visited[v] == 0) {
        // tree edge
        printf("Tree edge: (%d, %d)\n", u+1,v+1);
        dfs_recursive(u, state, G);
      } else if (state->visited[v] == 1) {
        // back edge (v is an ancestor, still being processed)
        printf("Back edge: (%d, %d)\n", u+1, v+1);
      } else if (state->visited[v] == 2) {
        // v is finished processing
        if (state->discovery[u] < state->discovery[v]) {
          // forward edge (u was discovered before v)
          printf("Forward edge: (%d, %d)\n", u+1, v+1);
        } else {
          // cross edge (v was discovered before u)
          printf("cross edge: (%d, %d)\n", u+1, v+1);
        }
      }
    }
  }
  
  state->visited[u] = 2; // mark as finished processing
  state->finish[u] = ++(state->time);
}
