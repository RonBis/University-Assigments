#include <stdio.h>
#include <stdlib.h>

typedef struct BinomialNode {
  int key;
  int degree;
  struct BinomialNode *parent;
  struct BinomialNode *child;
  struct BinomialNode *sibling;
} Node;

Node *head = NULL;

/* Create Node */
Node *createNode(int key) {
  Node *n = (Node *)malloc(sizeof(Node));
  n->key = key;
  n->degree = 0;
  n->parent = n->child = n->sibling = NULL;
  return n;
}

/* Merge root lists by degree */
Node *mergeRootLists(Node *h1, Node *h2) {
  if (!h1)
    return h2;
  if (!h2)
    return h1;

  Node *head = NULL, *tail = NULL;

  while (h1 && h2) {
    Node *min;
    if (h1->degree <= h2->degree) {
      min = h1;
      h1 = h1->sibling;
    } else {
      min = h2;
      h2 = h2->sibling;
    }

    if (!head)
      head = tail = min;
    else {
      tail->sibling = min;
      tail = min;
    }
  }

  if (h1)
    tail->sibling = h1;
  if (h2)
    tail->sibling = h2;

  return head;
}

/* Link trees */
void linkTrees(Node *y, Node *z) {
  y->parent = z;
  y->sibling = z->child;
  z->child = y;
  z->degree++;
}

/* Union Heaps */
Node *unionHeaps(Node *h1, Node *h2) {
  Node *newHead = mergeRootLists(h1, h2);
  if (!newHead)
    return NULL;

  Node *prev = NULL, *curr = newHead, *next = curr->sibling;

  while (next) {
    if ((curr->degree != next->degree) ||
        (next->sibling && next->sibling->degree == curr->degree)) {
      prev = curr;
      curr = next;
    } else {
      if (curr->key <= next->key) {
        curr->sibling = next->sibling;
        linkTrees(next, curr);
      } else {
        if (!prev)
          newHead = next;
        else
          prev->sibling = next;

        linkTrees(curr, next);
        curr = next;
      }
    }
    next = curr->sibling;
  }

  return newHead;
}

/* Insert */
void insert(int key) {
  Node *temp = createNode(key);
  head = unionHeaps(head, temp);
}

/* Reverse child list */
Node *reverseList(Node *node) {
  Node *prev = NULL;
  Node *curr = node;
  while (curr) {
    curr->parent = NULL;
    Node *next = curr->sibling;
    curr->sibling = prev;
    prev = curr;
    curr = next;
  }
  return prev;
}

/* Extract Min */
void extractMin() {
  if (!head) {
    printf("Heap is empty!\n");
    return;
  }

  Node *minPrev = NULL, *minNode = head;
  Node *prev = NULL, *curr = head;
  int min = curr->key;

  while (curr) {
    if (curr->key < min) {
      min = curr->key;
      minPrev = prev;
      minNode = curr;
    }
    prev = curr;
    curr = curr->sibling;
  }

  if (minPrev)
    minPrev->sibling = minNode->sibling;
  else
    head = minNode->sibling;

  Node *childReversed = reverseList(minNode->child);
  head = unionHeaps(head, childReversed);

  printf("Extracted Min: %d\n", minNode->key);
  free(minNode);
}

/* Display Root List */
void display() {
  if (!head) {
    printf("Heap Empty\n");
    return;
  }

  Node *curr = head;
  printf("Root List:\n");
  while (curr) {
    printf("Key: %d | Degree: %d\n", curr->key, curr->degree);
    curr = curr->sibling;
  }
}

/* Main Menu */
int main() {
  int choice, val;

  while (1) {
    printf("\n--- BINOMIAL HEAP MENU ---\n");
    printf("1. Insert\n");
    printf("2. Extract Min\n");
    printf("3. Display Root List\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter value: ");
      scanf("%d", &val);
      insert(val);
      break;
    case 2:
      extractMin();
      break;
    case 3:
      display();
      break;
    case 4:
      return 0;
    default:
      printf("Invalid choice\n");
    }
  }
}
