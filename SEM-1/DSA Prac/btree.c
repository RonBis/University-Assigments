#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define M 5 // order of B-tree

typedef struct BTreeNode {
  int n;                        // number of keys
  const char* keys[M - 1];  
  struct BTreeNode *children[M];
  bool is_leaf;
} BTreeNode;

int compare_keys(const char *k1, const char *k2) {
  char c1 = k1[0], c2 = k2[0];
  if (c1 != c2) {
    return c1 - c2;
  }
  
  int n1 = atoi(k1 + 1);
  int n2 = atoi(k2 + 1);
  return n1 - n2;
}

void insert_key_into_position(BTreeNode *node, const char *key) {
  // insert key in its sorted position
  int i;
  for (i=0; i<node->n; i++) {
    if (key < node->keys[i]) {
      break;
    }
  }
  // shift keys right by 1 position
  memmove(&node->keys[i+1], &node->keys[i], (node->n - i) * sizeof(int));
  // insert key
  node->keys[i] = key;
  node->n++;
}

void insert(BTreeNode *node, const char *key) {
  insert_key_into_position(node, key);
  
  // split keys
  int mid = M/2;
  
  BTreeNode left, right;
  memcpy(&left.keys, &node->keys[mid], unsigned long)
}

int main() {
  return 0;
}
