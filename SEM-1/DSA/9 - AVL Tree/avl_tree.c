#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

typedef struct Node {
    int data;
    int height;
    struct Node* left_child;
    struct Node* right_child;
} node;

node* create_node(int data);
node* insert(node* root, int data);
node* delete(node* root, int data);
void display(node* root, int space);

void preorder(node* node);
void inorder(node* node);
void postorder(node* root);

node* rotate_left(node* node);
node* rotate_right(node* node);
node* rotate_left_right(node* node);
node* rotate_right_left(node* node);

node* rebalance_tree(node* root, int data);

// int get_terminal_width() {
//     struct winsize w;
//     ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
//     return w.ws_col;
// }

// void center_text(const char* text) {
//     int term_width = get_terminal_width();
//     int text_length = strlen(text);
//     int padding = (term_width - text_length) / 2;

//     if (padding < 0) padding = 0;

//     printf("%*s%s\n", padding, "", text);
// }

static inline int max(int a, int b) { return (a > b) ? a : b; }

static inline int height(node* node) {
    return node == NULL ? -1 : node->height;
}

static inline void update_height(node* node) {
    if (node == NULL) return;
    node->height = 1 + max(height(node->left_child), height(node->right_child));
}

node* rebalance_tree(node* root, int data) {
    // Calculate balance factor (bf)
    int bf = height(root->left_child) - height(root->right_child);
    // printf("node: %d, balance factor: %d\n", root->data, bf);

    // Rotation cases
    if (bf > 1 && data < root->left_child->data) {
        // printf("Left Left Case\n");
        return rotate_right(root);
    }

    if (bf < -1 && data > root->right_child->data) {
        // printf("Right Right Case\n");
        return rotate_left(root);
    }

    if (bf > 1 && data > root->left_child->data) {
        // printf("Left Right Case\n");
        return rotate_left_right(root);
    }

    if (bf < -1 && data < root->right_child->data) {
        // printf("Right Left Case\n");
        return rotate_right_left(root);
    }

    return NULL;
}

// int main() {
//     int sequence[6] = {10, 20, 30, 40, 50, 25};

//     node* root = NULL;
//     char ch;
//     do {
      
//     } while ();
    
//     for (int i = 0; i < 6; i++) {
//         root = insert(root, sequence[i]);
//         printf("\n");
//         display(root, 0);
//         printf("\n");
//     }

//     printf("Deleting 20\n");
//     delete(root, 20);
//     display(root, 0);

//     printf("\n");
//     return 0;
// }

int main() {
    node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n====== AVL TREE MENU ======\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display As Tree\n");
        printf("4. Preorder Traversal\n");
        printf("5. Inorder Traversal\n");
        printf("6. Postorder Travresal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = delete(root, value);
                break;

            case 3:
                printf("\nAVL Tree:\n");
                display(root, 0);
                printf("\n");
                break;
            
            case 4:
                printf("\nPreorder Traversal:\n");
                preorder(root);
                printf("\n");
                break;

            case 5:
                printf("\nInorder Traversal:\n");
                inorder(root);
                printf("\n");
                break;

            case 6:
                printf("\nPostorder Traversal:\n");
                postorder(root);
                printf("\n");
                break;

            case 7:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}


node* create_node(int data) {
    node* root = (node*)malloc(sizeof(node));
    root->data = data;
    root->height = 0;
    root->left_child = NULL;
    root->right_child = NULL;
    return root;
}

node* insert(node* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }

    if (data <= root->data) {
        root->left_child = insert(root->left_child, data);
    } else {
        root->right_child = insert(root->right_child, data);
    }

    // Update height (here root is last inserted node's parent)
    update_height(root);

    // Rebalance tree if needed
    node* rebalanced_tree_root = rebalance_tree(root, data);
    if (rebalanced_tree_root != NULL) {
        return rebalanced_tree_root;
    }

    return root;
}

node* min_value_node(node* root) {
    node* t = root;
    while (t->left_child != NULL) {
        t = t->left_child;
    }
    return t;
}

node* delete(node* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left_child = delete(root->left_child, data);
    } else if (data > root->data) {
        root->right_child = delete(root->right_child, data);
    } else {
        // Found node with deletion key
        if (root->left_child == NULL && root->right_child == NULL) {
            node* t = root->left_child ? root->right_child : root->left_child;
            if (t == NULL) {
                t = root;
                root = NULL;
            } else {
                root = t;
            }
            free(t);
        } else {
            node* t = min_value_node(root->right_child);
            root->data = t->data;
            root->right_child = delete(root->right_child, t->data);
        }
    }

    if (root == NULL) return NULL;

    update_height(root);

    // Rebalance tree if needed
    node* rebalanced_tree_root = rebalance_tree(root, data);
    if (rebalanced_tree_root != NULL) {
        return rebalanced_tree_root;
    }

    return root;
}

// Horizontal tree display function
void display(node* root, int space) {
    if (root == NULL) return;

    space += 8;  // indentation between levels

    display(root->right_child, space);  // print right subtree first

    printf("\n");
    for (int i = 8; i < space; i++) printf(" ");
    printf("%d\n", root->data);

    display(root->left_child, space);
}

node* rotate_left(node* X) {
    node* Y = X->right_child;
    node* T2 = Y->left_child;

    Y->left_child = X;
    X->right_child = T2;

    update_height(X);
    update_height(Y);

    return Y;
}

node* rotate_right(node* X) {
    node* Y = X->left_child;
    node* T2 = Y->right_child;

    Y->right_child = X;
    X->left_child = T2;

    update_height(X);
    update_height(Y);

    return Y;
}

node* rotate_left_right(node* X) {
    X->left_child = rotate_left(X->left_child);
    return rotate_right(X);
}

node* rotate_right_left(node* X) {
    X->right_child = rotate_right(X->right_child);
    return rotate_left(X);
}

void inorder(node* root) {
    if (root == NULL) return;
    inorder(root->left_child);
    printf("%d ", root->data);
    inorder(root->right_child);
}

void preorder(node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left_child);
    preorder(root->right_child);
}

void postorder(node* root) {
    if (root == NULL) return;
    postorder(root->left_child);
    postorder(root->right_child);
    printf("%d ", root->data);
}
