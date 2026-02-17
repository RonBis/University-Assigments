#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float coeff;
  int exp;
} PolyTerm;

typedef struct {
  int term_count;
  PolyTerm *poly;
} Polynomial;

Polynomial input_polynomial();
void print_polynomial(Polynomial P);
Polynomial multiply(Polynomial A, Polynomial B);

int main() {
  printf("Enter polynomial A:\n");
  Polynomial A = input_polynomial();

  printf("\nEnter polynomial B:\n");
  Polynomial B = input_polynomial();
  
  printf("\nPolynomial A:\n");
  print_polynomial(A);
  printf("\nPolynomial B:\n");
  print_polynomial(B);
  
  printf("\n-- Product --\n");
  print_polynomial(multiply(A, B));

  printf("\n");
  return 0;
}

Polynomial input_polynomial() {
  int TERM_COUNT;
  printf("Enter maximum number of terms in polynomial: ");
  scanf("%d", &TERM_COUNT);

  PolyTerm *polyterms = (PolyTerm *)calloc(TERM_COUNT, sizeof(PolyTerm));

  printf("Note: Enter polynomial terms in descending order\n\n");
  for (int i = 0; i < TERM_COUNT; i++) {
    printf("-- term %d: --\n", i + 1);

    printf("Enter power: ");
    scanf("%d", &polyterms[i].exp);

    printf("Enter coefficient: ");
    scanf("%f", &polyterms[i].coeff);
  }

  return (Polynomial){.poly = polyterms, .term_count = TERM_COUNT};
}

void print_polynomial(Polynomial P) {
  for (int i=0; i<P.term_count; i++) {
    printf("%.2fx^%d", P.poly[i].coeff, P.poly[i].exp);
    if (i != P.term_count-1) {
      printf(" + ");
    }
  }
}

Polynomial multiply(Polynomial A, Polynomial B) {
  PolyTerm *polyterms =
      (PolyTerm *)calloc(A.term_count * B.term_count, sizeof(PolyTerm));
  Polynomial polynomial = {.term_count = 0};

  for (int i = 0; i < A.term_count; i++) {
    for (int j = 0; j < B.term_count; j++) {
      PolyTerm prodterm;
      prodterm.coeff = A.poly[i].coeff * B.poly[j].coeff;
      prodterm.exp = A.poly[i].exp + B.poly[j].exp;

      // If 'polyterms' array includes 'prodterm.exp', add 'prodterm'
      int flag_new_exponent = 1;
      int k;
      for (k = 0; k < polynomial.term_count; k++) {
        if (polyterms[k].exp == prodterm.exp) {
          flag_new_exponent = 0;
          break;
        }
      }
      if (flag_new_exponent == 1) {
        // term with new exponent
        polyterms[polynomial.term_count] = prodterm;
        polynomial.term_count++;
      } else {
        // add 'prodterm' to k-th element of 'polyterms' array
        polyterms[k].coeff += prodterm.coeff;
      }
    }
  }
  
  polynomial.poly = polyterms;
  return polynomial;
}
