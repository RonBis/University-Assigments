#include <stdio.h>

#define MAXV 50

typedef struct Edge {
  int u, v;
} Edge;

int V, E;
int adj[MAXV][MAXV];
int disc[MAXV], low[MAXV], parent[MAXV];
int timeCounter = 0;

Edge stack[MAXV * MAXV];
int top = -1;

/* Push edge */
void push(int u, int v) {
  stack[++top].u = u;
  stack[top].v = v;
}

/* Pop and print BCC */
void popBCC(int u, int v) {
  printf("BCC: ");
  while (top >= 0) {
    Edge e = stack[top--];
    printf("(%d-%d) ", e.u, e.v);
    if (e.u == u && e.v == v)
      break;
  }
  printf("\n");
}

/* DFS */
void dfsBCC(int u) {
  disc[u] = low[u] = ++timeCounter;
  int children = 0;

  for (int v = 1; v <= V; v++) {
    if (adj[u][v]) {
      if (disc[v] == 0) {
        children++;
        parent[v] = u;
        push(u, v);

        dfsBCC(v);

        low[u] = (low[u] < low[v]) ? low[u] : low[v];

        if ((disc[u] == 1 && children > 1) ||
            (disc[u] > 1 && low[v] >= disc[u])) {
          popBCC(u, v);
        }
      } else if (v != parent[u] && disc[v] < disc[u]) {
        if (low[u] > disc[v])
          low[u] = disc[v];
        push(u, v);
      }
    }
  }
}

int main() {
  printf("Enter number of vertices (>=15): ");
  scanf("%d", &V);

  printf("Enter number of edges: ");
  scanf("%d", &E);

  /* initialize */
  for (int i = 1; i <= V; i++) {
    for (int j = 1; j <= V; j++)
      adj[i][j] = 0;
    disc[i] = 0;
    parent[i] = -1;
  }

  printf("Enter undirected edges (u v):\n");
  for (int i = 0; i < E; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    adj[u][v] = adj[v][u] = 1;
  }

  for (int i = 1; i <= V; i++) {
    if (disc[i] == 0)
      dfsBCC(i);

    /* leftover edges in stack */
    if (top >= 0) {
      printf("BCC: ");
      while (top >= 0) {
        Edge e = stack[top--];
        printf("(%d-%d) ", e.u, e.v);
      }
      printf("\n");
    }
  }

  return 0;
}
