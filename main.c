#include "mm.h"
#include<stdio.h>
#include<stdlib.h>

int main(){
	int *arr;
	int size = 10;

	arr = mymalloc( size * sizeof(int) );
	printf("----------malloc----------\narray size = %d\n", size);
	if( arr == NULL ) {
    		fprintf(stderr, "Error: unable to allocate required memory\n");
    		return 1;
  	}
	
  	int i;

  	for (i = 0; i < size; i++) {
    		arr[i] = i + 1;
    		printf("%d ", arr[i]);
  	}

	myfree(arr);


	arr = mycalloc( size, sizeof(int) );
	printf("\n----------calloc----------\narray size = %d\n", size);
  	if( arr == NULL ) {
    		fprintf(stderr, "Error: unable to allocate required memory\n");
    		return 1;
  	}
  	
  	for (i = 0; i < size; i++) {
    		printf("%d ", arr[i]);
  	}
  	myfree(arr);

  	size = 20;
  	arr = myrealloc( arr, size * sizeof(int) );
	printf("\n----------realloc----------\narray size = %d\n", size);
  	if( arr == NULL ) {
    		fprintf(stderr, "Error: unable to allocate required memory\n");
    		return 1;
  	}

  	
  	for (i = 0; i < size; i++) {
    		arr[i] = i + 1;
    		printf("%d ", arr[i]);
  	}

  	size = 5;
  	arr = myrealloc( arr, size * sizeof(int) );
	printf("\narray size = %d\n", size);
  	if( arr == NULL ) {
    		fprintf(stderr, "Error: unable to allocate required memory\n");
    		return 1;
  	}

  	for (i = 0; i < size; i++) {
    		arr[i] = i + 1;
    		printf("%d ", arr[i]);
  	}

  	myfree(arr);
	printf("\n");
	
	return 0;
}