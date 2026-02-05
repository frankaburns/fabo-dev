/* C implementation QuickSort */
#include<stdio.h> 
  
// A utility function to swap two elements 
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
  
/* Function to print an array */
void printArray(int arr[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("]\n"); 
} 

/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
    array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    printf("low: %d, high: %d\n\n", low, high); 
    // printArray(arr, high);
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j] <= pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    // printArray(arr, high);
    swap(&arr[i + 1], &arr[high]); 
    // printArray(arr, high);
    return (i + 1); 
} 
  
/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        printf("Interm array: [ "); 
        printArray(arr, high);
        quickSort(arr, low, pi - 1); 
        printf("Interm array: [ "); 
        printArray(arr, high);
        quickSort(arr, pi + 1, high); 
        printf("Interm array: [ "); 
        printArray(arr, high);
    } 
} 
  
// Driver program to test above functions 
int main() 
{ 
    int arr[] = {22, 3, 99, 4, 33, 50, 10, 7, 8, 9, 1, 5}; 
    int n = sizeof(arr)/sizeof(arr[0]); 
    printf("Initial array: [ "); 
    printArray(arr, n); 
    quickSort(arr, 0, n-1); 
    printf("Sorted array: [ "); 
    printArray(arr, n); 
    return 0; 
} 
