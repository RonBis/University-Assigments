#include <stdio.h>
#include <stdlib.h>

struct node {
    float coef;
    int expo;
    struct node* link;
};

// Insert a term into the polynomial in sorted (descending exponent) order
struct node* insertNode(struct node* head, float coef, int expo) {
    struct node* newNode = malloc(sizeof(struct node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->coef = coef;
    newNode->expo = expo;
    newNode->link = NULL;

    // Insert at head if list empty OR exponent is greater
    if (head == NULL || expo > head->expo) {
        newNode->link = head;
        return newNode;
    }

    struct node* temp = head;
    while (temp->link != NULL && temp->link->expo > expo) {
        temp = temp->link;
    }

    newNode->link = temp->link;
    temp->link = newNode;
    return head;
}

// Create polynomial dynamically
struct node* createPoly(struct node* head) {
    int n;
    float coef;
    int expo;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter coefficient of term %d: ", i + 1);
        scanf("%f", &coef);

        printf("Enter exponent of term %d: ", i + 1);
        scanf("%d", &expo);

        head = insertNode(head, coef, expo);
    }

    return head;
}

void printPoly(struct node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }

    struct node* temp = head;
    while (temp != NULL) {
        printf("(%.2fx^%d)", temp->coef, temp->expo);
        temp = temp->link;
        if (temp != NULL) printf(" + ");
    }
    printf("\n");
}

// Add two polynomials
void addPoly(struct node* head1, struct node* head2) {
    struct node *ptr1 = head1, *ptr2 = head2;
    struct node* result = NULL;

    while (ptr1 && ptr2) {
        if (ptr1->expo == ptr2->expo) {
            result = insertNode(result, ptr1->coef + ptr2->coef, ptr1->expo);
            ptr1 = ptr1->link;
            ptr2 = ptr2->link;
        } else if (ptr1->expo > ptr2->expo) {
            result = insertNode(result, ptr1->coef, ptr1->expo);
            ptr1 = ptr1->link;
        } else {
            result = insertNode(result, ptr2->coef, ptr2->expo);
            ptr2 = ptr2->link;
        }
    }

    while (ptr1) {
        result = insertNode(result, ptr1->coef, ptr1->expo);
        ptr1 = ptr1->link;
    }

    while (ptr2) {
        result = insertNode(result, ptr2->coef, ptr2->expo);
        ptr2 = ptr2->link;
    }

    printf("\nAddition result: ");
    printPoly(result);
}

// Subtract polynomial 2 from polynomial 1
void subPoly(struct node* head1, struct node* head2) {
    struct node *ptr1 = head1, *ptr2 = head2;
    struct node* result = NULL;

    while (ptr1 && ptr2) {
        if (ptr1->expo == ptr2->expo) {
            result = insertNode(result, ptr1->coef - ptr2->coef, ptr1->expo);
            ptr1 = ptr1->link;
            ptr2 = ptr2->link;
        } else if (ptr1->expo > ptr2->expo) {
            result = insertNode(result, ptr1->coef, ptr1->expo);
            ptr1 = ptr1->link;
        } else {
            result = insertNode(result, -ptr2->coef, ptr2->expo);
            ptr2 = ptr2->link;
        }
    }

    while (ptr1) {
        result = insertNode(result, ptr1->coef, ptr1->expo);
        ptr1 = ptr1->link;
    }

    while (ptr2) {
        result = insertNode(result, -ptr2->coef, ptr2->expo);
        ptr2 = ptr2->link;
    }

    printf("\nSubtraction result: ");
    printPoly(result);
}

// Multiply two polynomials
void multPoly(struct node* head1, struct node* head2) {
    struct node *ptr1 = head1, *ptr2;
    struct node* result = NULL;

    // Multiply each term of poly1 with every term of poly2
    while (ptr1) {
        ptr2 = head2;
        while (ptr2) {
            result = insertNode(result, ptr1->coef * ptr2->coef,
                                ptr1->expo + ptr2->expo);
            ptr2 = ptr2->link;
        }
        ptr1 = ptr1->link;
    }

    // Combine like terms
    struct node* p = result;
    while (p && p->link) {
        if (p->expo == p->link->expo) {
            p->coef += p->link->coef;
            struct node* del = p->link;
            p->link = p->link->link;
            free(del);
        } else {
            p = p->link;
        }
    }

    printf("\nMultiplication result: ");
    printPoly(result);
}

// Derivative of a polynomial
void derivative(struct node* head) {
    struct node* result = NULL;
    struct node* temp = head;

    while (temp) {
        if (temp->expo != 0) {
            result =
                insertNode(result, temp->coef * temp->expo, temp->expo - 1);
        }
        temp = temp->link;
    }

    printf("Derivative: ");
    printPoly(result);
}

int main() {
    struct node *poly1 = NULL, *poly2 = NULL;

    printf("\n--- Enter 1st Polynomial ---\n");
    poly1 = createPoly(poly1);

    printf("\n--- Enter 2nd Polynomial ---\n");
    poly2 = createPoly(poly2);

    printf("\nPolynomial 1: ");
    printPoly(poly1);

    printf("Polynomial 2: ");
    printPoly(poly2);

    addPoly(poly1, poly2);
    subPoly(poly1, poly2);
    multPoly(poly1, poly2);

    printf("\nDerivative of Polynomial 1: ");
    derivative(poly1);

    printf("Derivative of Polynomial 2: ");
    derivative(poly2);

    return 0;
}
