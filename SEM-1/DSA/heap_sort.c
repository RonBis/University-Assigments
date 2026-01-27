#include<stdio.h>
#include<stdlib.h>

void make_heap(int* a, int n, int i) {
	int largest = i;
	int left=(2*i)+1;
	int right=(2*i)+2;
	if(left < n && a[left] > a[largest]) largest = left;
	if(right < n && a[right]  > a[largest]) largest = right;
	if(largest != i) {
		int temp=a[i];
		a[i]=a[largest];
		a[largest]=temp;
		make_heap(a, n, largest);
	}
}

void heapsort(int *a, int n) {
	int i,j,temp;
	
	for(i=n-1;i>=0;i--) {
//		printf("iteration no: %d",i-1);
		printf("\n%d is taken out of heap.\n",a[0]);
		 temp=a[0];
		a[0]=a[i];
		a[i]=temp;
		printf("\nNew heap: ");
		for(j=0;j<i;j++) {
			printf("%d ",a[j]);
		}
		printf("\n");
		make_heap(a,i,0);
			printf("New heap after heapifying\n");
			for(j=0;j<i;j++) {
				printf("%d ",a[j]);
	 	}
	 	printf("\n");
	}
	for(i=0;i<n/2;i++) {
		 temp = a[i];
		a[i]=a[n-i-1];
		a[n-i-1]=temp;
	}
	printf("Sorted list: ");
	for(j=0;j<n;j++) {
		printf("%d ",a[j]);
	}
}

int main() {
	int n,i,j;
	printf("Enter the number of elements to be sorted: \n");
	scanf("%d",&n);
	int *a = malloc(n * sizeof(int));
	for(i=0;i<n;i++) {
		printf("\n\nEnter element: ");
		scanf("%d",&a[i]);
		
		printf("New heap before heapifying: ");
		for(j=0;j<=i;j++) {
			printf("%d ",a[j]);
		}
		for(j = (i-1)/2; j >= 0; j--) {
			make_heap(a, i+1, j);
			if(j==0) break;
		}
			printf("\nNew heap after heapifying: ");
			for(j=0;j<i+1;j++) {
				printf("%d ",a[j]);
			}
	}
	heapsort(a, n);
	return 0;
}
