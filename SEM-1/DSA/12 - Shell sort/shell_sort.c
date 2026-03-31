#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int size;
  int *arr;
} IntArray;

IntArray *new_intarray(int size) {
  IntArray *intArray = (IntArray *)malloc(sizeof(IntArray));
  int *arr = (int *)malloc(size * sizeof(int));
  intArray->arr = arr;
  intArray->size = size;
  return intArray;
}

IntArray *input_array() {
  int N;
  printf("Enter no of elements: ");
  scanf("%d", &N);

  IntArray *intArray = new_intarray(N);
  printf("Enter array elements one by one:\n");
  for (int i = 0; i < N; i++) {
    scanf("%d", &intArray->arr[i]);
  }
  return intArray;
}

void print_array(IntArray *intArray) {
  for (int i = 0; i < intArray->size; i++)
    printf("%d  ", intArray->arr[i]);
  printf("\n");
}

void shell_sort(IntArray *arr) {
  for (int gap = arr->size / 2; gap >= 1; gap /= 3) {
    // Sort (insertion sort) sublists at interval `gap`
    // ie: Sort { arr[i], arr[i+gap], arr[i+2*gap], ... }
    
    for (int i=0; i<)
  }
}

int main() {
  IntArray *intArray = input_array();

  shell_sort(intArray);

  printf("\nSorted array: ");
  print_array(intArray);

  return 0;
}
