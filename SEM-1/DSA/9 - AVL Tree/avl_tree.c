#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

typedef struct Node {
    int data;
    struct Node* left_child;
    struct Node* right_child;
} node;

typedef struct TreeLevel {
    int current_level;
    int node_count;
    int MAXNODE;
} tree_level;

node* create_node(int data);
node* insert(node* root, int data, tree_level* tree_lvl);
void delete(node* root, int data);
void display(node* root);

void update_tree_level(tree_level* tree_lvl) {
    if (tree_lvl->node_count == tree_lvl->MAXNODE) {
        tree_lvl->current_level++;
        tree_lvl->node_count = 0;
        tree_lvl->MAXNODE = pow(2, tree_lvl->current_level);
    }
}

int get_terminal_width() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void center_text(const char* text) {
    int term_width = get_terminal_width();
    int text_length = strlen(text);
    int padding = (term_width - text_length) / 2;

    if (padding < 0) padding = 0;

    printf("%*s%s\n", padding, "", text);
}

int main() {
    int sequence[6] = {10, 20, 30, 40, 50, 25};
    tree_level tree_lvl = {.current_level = 0, .node_count = 0, .MAXNODE = 1};

    node* root = NULL;
    for (int i = 0; i < 6; i++) {
        if (root == NULL)
            root = insert(root, sequence[i], &tree_lvl);
        else
            insert(root, sequence[i], &tree_lvl);
    }

    // display_tree_enhanced(root);
    printf("\n");
    return 0;
}

node* create_node(int data) {
    node* root = (node*)malloc(sizeof(node));
    root->data = data;
    root->left_child = NULL;
    root->right_child = NULL;
    return root;
}

node* insert(node* root, int data, tree_level* tree_lvl) {
    tree_lvl->node_count++;
    printf("Tree level: {current_level: %d, node_count: %d, MAXNODE: %d}\n",
           tree_lvl->current_level, tree_lvl->node_count, tree_lvl->MAXNODE);

    if (root == NULL) {
        // Create root node
        root = create_node(data);
        update_tree_level(tree_lvl);
        return root;
    }

    node* tr = root; // To keep track of current node
    int level_tr = 0; // To keep track of current level
    printf("Current level: %d\n", level_tr);
    while (1) {
        level_tr++;
        printf("Current level: %d\n", level_tr);
        if (data <= tr->data) {
            if (tr->left_child == NULL) {
                tr->left_child = create_node(data);
                break;
            }
            // Explore left subtree
            tr = tr->left_child;
        } else {
            if (tr->right_child == NULL) {
                tr->right_child = create_node(data);
                break;
            }
            // Explore right subtree
            tr = tr->right_child;
        }
    }
    update_tree_level(tree_lvl);
    return NULL;
}

void delete(node* root, int data) {}

void display(node* root) {}
