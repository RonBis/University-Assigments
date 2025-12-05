#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

typedef struct Node {
    int data;
    int height;
    struct Node* left_child;
    struct Node* right_child;
} node;

// typedef struct TreeLevel {
//     int current_level;
//     int node_count;
//     int MAXNODE;
// } tree_level;

node* create_node(int data);
node* insert(node* root, int data);
void delete(node* root, int data);
void display(node* root, int space);

// void update_tree_level(tree_level* tree_lvl) {
//     if (tree_lvl->node_count == tree_lvl->MAXNODE) {
//         tree_lvl->current_level++;
//         tree_lvl->node_count = 0;
//         tree_lvl->MAXNODE = pow(2, tree_lvl->current_level);
//     }
// }

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

int max(int a, int b) { return (a > b) ? a : b; }

static inline int height(node* node) {
    return node == NULL ? -1 : node->height;
}

int main() {
    int sequence[6] = {10, 20, 30, 40, 50, 25};

    node* root = NULL;
    for (int i = 0; i < 6; i++) {
        if (root == NULL)
            root = insert(root, sequence[i]);
        else
            insert(root, sequence[i]);
    }

    display(root, 0);
    printf("\n");
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
    root->height = 1 + max(height(root->left_child), height(root->right_child));
    // Check balance factor (bf)
    int bf = height(root->left_child) - height(root->right_child);
    printf("root: %d, balance factor: %d\n", root->data, bf);
    return root;
}

void delete(node* root, int data) {}

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
