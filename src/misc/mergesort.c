// C program for the implementation of merge sort
#include <stdio.h>
#include <stdlib.h>

// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int leftArr[n1], rightArr[n2];

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArr[], if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// The subarray to be sorted is in the index range [left-right]
void mergeSort(int arr[], int left, int right, int size) {
    if (left < right) {

	printf ("arr before: { ");
        for (int i = 0; i < size; i++)
	            printf("%d ", arr[i]);
        printf (" }\n");
      
        // Calculate the midpoint
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid, size);
        mergeSort(arr, mid + 1, right, size);

	printf ("Merge ---- left(%d), mid(%d), right(%d)\n", left, mid, right);
        // Merge the sorted halves
        merge(arr, left, mid, right);

	printf ("arr After: { ");
        for (int i = 0; i < size; i++)
	            printf("%d ", arr[i]);
        printf (" }\n");

    }
}

int main() {
    int arr[] = { 12, 11, 13, 5, 7, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
	
  	// Sorting arr using mergesort
    mergeSort(arr, 0, n - 1, n);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf ("\n");
    return 0;
}
