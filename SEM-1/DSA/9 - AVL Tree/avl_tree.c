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

node* create_node(int data);
node* insert(node* root, int data);
void delete(node* root, int data);
void display(node* root);

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

    node* root = NULL;
    for (int i = 0; i < 6; i++) {
        if (root == NULL)
            root = insert(root, sequence[i]);
        else
            insert(root, sequence[i]);
    }

    display_tree_enhanced(root);
    return 0;
}

node* create_node(int data) {
    node* root = (node*)malloc(sizeof(node));
    root->data = data;
    root->left_child = NULL;
    root->right_child = NULL;
    return root;
}

node* insert(node* root, int data) {
    if (root == NULL) {
        // Create root node
        root = create_node(data);
        return root;
    }

    node* tr = root;
    while (1) {
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
    return NULL;
}

void delete(node* root, int data) {}

void display(node* root) {}
