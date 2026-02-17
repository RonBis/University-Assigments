#include <stdio.h>
#define MAXV 50

int parent[MAXV], rankArr[MAXV];
int degreeArr[MAXV];
int adj[MAXV][MAXV];

/* ---------- DISJOINT SET ---------- */
void makeSet(int n) {
  for (int i = 1; i <= n; i++) {
    parent[i] = i;
    rankArr[i] = 0;
  }
}

int findSet(int x) {
  if (parent[x] != x)
    parent[x] = findSet(parent[x]);
  return parent[x];
}

void unionSet(int a, int b) {
  int pa = findSet(a);
  int pb = findSet(b);
  if (pa == pb)
    return;

  if (rankArr[pa] < rankArr[pb])
    parent[pa] = pb;
  else if (rankArr[pb] < rankArr[pa])
    parent[pb] = pa;
  else {
    parent[pb] = pa;
    rankArr[pa]++;
  }
}

int isClique(int arr[], int size) {
  for (int i = 0; i < size; i++)
    for (int j = i + 1; j < size; j++)
      if (!adj[arr[i]][arr[j]])
        return 0;
  return 1;
}

int main() {
  int V, E;
  printf("Enter number of vertices (>=15): ");
  scanf("%d", &V);

  printf("Enter number of edges: ");
  scanf("%d", &E);

  makeSet(V);

  /* initialize */
  for (int i = 1; i <= V; i++) {
    degreeArr[i] = 0;
    for (int j = 1; j <= V; j++)
      adj[i][j] = 0;
  }

  printf("Enter edges (u v):\n");
  for (int i = 0; i < E; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    adj[u][v] = adj[v][u] = 1;
    degreeArr[u]++;
    degreeArr[v]++;
    unionSet(u, v);
  }

  /* COMPONENTS */
  int visitedRep[MAXV] = {0};
  int compCount = 0;

  printf("\nConnected Components:\n");
  for (int i = 1; i <= V; i++) {
    int rep = findSet(i);
    if (!visitedRep[rep]) {
      compCount++;
      visitedRep[rep] = 1;
      printf("Component %d: ", compCount);
      for (int j = 1; j <= V; j++)
        if (findSet(j) == rep)
          printf("%d ", j);
      printf("\n");
    }
  }

  printf("\nNumber of Components = %d\n", compCount);

  /* DEGREE */
  printf("\nDegrees of Vertices:\n");
  for (int i = 1; i <= V; i++)
    printf("Vertex %d -> %d\n", i, degreeArr[i]);

  /* PENDANT & ISOLATED */
  printf("\nPendant Vertices: ");
  for (int i = 1; i <= V; i++)
    if (degreeArr[i] == 1)
      printf("%d ", i);

  printf("\nIsolated Vertices: ");
  for (int i = 1; i <= V; i++)
    if (degreeArr[i] == 0)
      printf("%d ", i);

  /* CLIQUES (PAIRWISE) */
  printf("\n\nMaximal Cliques (pairs):\n");
  for (int i = 1; i <= V; i++) {
    for (int j = i + 1; j <= V; j++) {
      int arr[2] = {i, j};
      if (isClique(arr, 2))
        printf("{%d,%d}\n", i, j);
    }
  }

  return 0;
}
