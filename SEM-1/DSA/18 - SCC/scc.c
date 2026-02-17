#include <stdio.h>

#define MAXV 50

int V, E;
int adj[MAXV][MAXV], revAdj[MAXV][MAXV];
int visited[MAXV];
int stack[MAXV], top = -1;

/* Push stack */
void push(int v) { stack[++top] = v; }

/* DFS for order */
void dfs1(int v) {
  visited[v] = 1;
  for (int i = 1; i <= V; i++) {
    if (adj[v][i] && !visited[i])
      dfs1(i);
  }
  push(v);
}

/* DFS on reversed graph */
void dfs2(int v) {
  visited[v] = 1;
  printf("%d ", v);
  for (int i = 1; i <= V; i++) {
    if (revAdj[v][i] && !visited[i])
      dfs2(i);
  }
}

int main() {
  printf("Enter number of vertices (>=15): ");
  scanf("%d", &V);

  printf("Enter number of directed edges: ");
  scanf("%d", &E);

  /* Initialize */
  for (int i = 1; i <= V; i++)
    for (int j = 1; j <= V; j++)
      adj[i][j] = revAdj[i][j] = 0;

  printf("Enter directed edges (u v):\n");
  for (int i = 0; i < E; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    adj[u][v] = 1;
    revAdj[v][u] = 1; // reverse edge
  }

  /* Step 1 DFS */
  for (int i = 1; i <= V; i++)
    visited[i] = 0;
  for (int i = 1; i <= V; i++)
    if (!visited[i])
      dfs1(i);

  /* Step 2 DFS on reversed */
  for (int i = 1; i <= V; i++)
    visited[i] = 0;

  printf("\nStrongly Connected Components:\n");
  while (top >= 0) {
    int v = stack[top--];
    if (!visited[v]) {
      dfs2(v);
      printf("\n");
    }
  }

  return 0;
}
