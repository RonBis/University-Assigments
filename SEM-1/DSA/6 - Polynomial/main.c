#include <stdio.h>
#include <stdlib.h>

struct poly {
    int coeff;
    int expo;
};

struct poly *p1, *p2, *p3;
int t1, t2, t3;
int max1, max2, max3;

int read(struct poly[]);
void display(struct poly[], int);

int add(int);
int multiply();
int differentiate(struct poly[], int);

int main() {
    int f = 1, g = 0, ch;

    printf("Enter maximum number of terms for Polynomial-1: ");
    scanf("%d", &max1);
    printf("Enter maximum number of terms for Polynomial-2: ");
    scanf("%d", &max2);

    max3 = max1 + max2;   // maximum possible for multiplication

    /* ---- Allocate memory for polynomials ---- */
    p1 = (struct poly*) malloc(max1 * sizeof(struct poly));
    p2 = (struct poly*) malloc(max2 * sizeof(struct poly));
    p3 = (struct poly*) malloc(max3 * sizeof(struct poly));

    if (!p1 || !p2 || !p3) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    while (f == 1) {
        if (g == 0) {
            printf("\nEntering Polynomial-1 (Enter terms in descending exponent order)\n");
            t1 = read(p1);
            printf("\nPolynomial-1: ");
            display(p1, t1);

            printf("\nEntering Polynomial-2 (Enter terms in descending exponent order)\n");
            t2 = read(p2);
            printf("\nPolynomial-2: ");
            display(p2, t2);
        }

        printf("\nMENU");
        printf("\n1. Addition");
        printf("\n2. Subtraction (P1 - P2)");
        printf("\n3. Multiplication");
        printf("\n4. Differentiation");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                t3 = add(1);
                printf("\nResultant Polynomial: ");
                display(p3, t3);
                break;

            case 2:
                t3 = add(0);
                printf("\nResultant Polynomial: ");
                display(p3, t3);
                break;

            case 3:
                t3 = multiply();
                printf("\nResultant Polynomial: ");
                display(p3, t3);
                break;

            case 4:
                t3 = differentiate(p1, t1);
                printf("\nDifferentiation of P1: ");
                display(p3, t3);

                t3 = differentiate(p2, t2);
                printf("\nDifferentiation of P2: ");
                display(p3, t3);
                break;

            default:
                printf("\nInvalid choice!");
        }

        printf("\nContinue? (1=Yes 0=No): ");
        scanf("%d", &f);

        if (f == 1) {
            printf("Use the same polynomials? (1=Yes 0=No): ");
            scanf("%d", &g);
        }
    }

    free(p1);
    free(p2);
    free(p3);

    return 0;
}

/* --------------------------- READ --------------------------- */
int read(struct poly p[]) {
    int t, i;
    printf("Enter number of terms: ");
    scanf("%d", &t);

    for (i = 0; i < t; i++) {
        printf("Coefficient of term-%d: ", i + 1);
        scanf("%d", &p[i].coeff);
        printf("Exponent of term-%d: ", i + 1);
        scanf("%d", &p[i].expo);
    }
    return t;
}

/* ------------------------- DISPLAY -------------------------- */
void display(struct poly p[], int t) {
    for (int i = 0; i < t; i++) {
        if (p[i].coeff == 0) continue;

        if (i != 0 && p[i].coeff > 0)
            printf(" + ");

        printf("%dx^%d", p[i].coeff, p[i].expo);
    }
    printf("\n");
}

/* -------------------------- ADD / SUB ------------------------ */
int add(int sign) {   // sign=1 → add,  sign=0 → subtract
    int i = 0, j = 0, k = 0;

    while (i < t1 && j < t2) {
        if (p1[i].expo == p2[j].expo) {
            p3[k].expo = p1[i].expo;
            p3[k].coeff = p1[i].coeff + (sign ? p2[j].coeff : -p2[j].coeff);
            k++;
            i++;
            j++;
        }
        else if (p1[i].expo > p2[j].expo) {
            p3[k++] = p1[i++];
        }
        else {
            p3[k].expo = p2[j].expo;
            p3[k].coeff = sign ? p2[j].coeff : -p2[j].coeff;
            k++;
            j++;
        }
    }

    while (i < t1) p3[k++] = p1[i++];
    while (j < t2) {
        p3[k].expo = p2[j].expo;
        p3[k].coeff = sign ? p2[j].coeff : -p2[j].coeff;
        k++;
        j++;
    }

    return k;
}

/* ------------------------ MULTIPLICATION ----------------------- */
int multiply() {
    int k = 0;

    for (int i = 0; i < t1; i++) {
        for (int j = 0; j < t2; j++) {
            p3[k].coeff = p1[i].coeff * p2[j].coeff;
            p3[k].expo  = p1[i].expo + p2[j].expo;
            k++;
        }
    }

    // Combine like terms
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            if (p3[i].expo == p3[j].expo) {
                p3[i].coeff += p3[j].coeff;

                for (int p = j; p < k - 1; p++)
                    p3[p] = p3[p + 1];

                k--;
                j--;
            }
        }
    }

    return k;
}

/* ---------------------- DIFFERENTIATION ----------------------- */
int differentiate(struct poly pol[], int l) {
    int k = 0;

    for (int i = 0; i < l; i++) {
        if (pol[i].expo == 0)
            continue;
        p3[k].coeff = pol[i].coeff * pol[i].expo;
        p3[k].expo = pol[i].expo - 1;
        k++;
    }

    return k;
}
