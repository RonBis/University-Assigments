#include <stdio.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

/* Heapify a subtree rooted at index i
   n is size of heap */
void heapify(int arr[], int n, int i) {
  int largest = i;       // Initialize largest as root
  int left = 2 * i + 1;  // Left child
  int right = 2 * i + 2; // Right child

  // If left child is larger than root
  if (left < n && arr[left] > arr[largest])
    largest = left;

  // If right child is larger than largest so far
  if (right < n && arr[right] > arr[largest])
    largest = right;

  // If largest is not root
  if (largest != i) {
    swap(&arr[i], &arr[largest]);
    heapify(arr, n, largest);
  }
}

void heap_sort(int arr[], int n) {
  // Build max heap
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  // Extract elements from heap one by one
  for (int i = n - 1; i > 0; i--) {
    swap(&arr[0], &arr[i]); // Move current root to end
    heapify(arr, i, 0);     // Call heapify on reduced heap
  }
}

void print_array(int arr[], int n) {
  for (int i = 0; i < n; i++)
    printf("%d  ", arr[i]);
  printf("\n");
}

int main() {
  int arr[] = {12, 11, 13, 5, 6, 7};
  int n = sizeof(arr) / sizeof(arr[0]);

  heap_sort(arr, n);

  printf("Sorted array:\n");
  print_array(arr, n);

  return 0;
}
