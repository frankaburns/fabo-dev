#include <stdio.h>
#include <stdlib.h>

// Helper function to swap two integers
void swap(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

//int next_permutation(int n, char **s)


// Recursive function to generate all permutations
void permute(int *arr, int start, int end) {
    int i;
    // Base case: If start equals end, a permutation is complete
    if (start == end) {
        // Print the current permutation (this is where you would "map" or store it)
	printf ("Permutation: ");
        for (i = 0; i <= end; i++) {
            printf ("%d ", arr[i]);
        }
        printf ("\n");
    } else {
        // Recursive case: Iterate through all elements from start to end
        for (i = start; i <= end; i++) {
            // Swap the current element with the element at the start index
            swap((arr + start), (arr + i));
            
            // Recursively call permute for the remaining elements
	    printf ("\nRecursing...\n");
            permute(arr, start + 1, end);
            
            // Backtrack: Swap them back to restore the original array state
            // This is crucial for generating all unique permutations correctly
            swap((arr + start), (arr + i));
        }
    }
}


// Main function to demonstrate the permutation generator
int main() {
    int list[] = {1, 2, 3};
    int n = sizeof(list) / sizeof(list[0]);
    
    printf("Generating all permutations for the list: {1, 2, 3}\n");
    // Call the permute function, initial start index is 0, end index is n-1
    permute(list, 0, n - 1);

    return 0;
}
/*
int main() {
    FILE *fptr;
    char character;
    const char* filename = "./permute.txt";

    // Open the file in read mode ("r")
    fptr = fopen(filename, "r");

    // Check if the file was opened successfully
    if (fptr == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1); // Exit the program if the file cannot be opened
    }

    int q;
    char **s;
    int n;
    fscanf(fptr, "%d", &n);
    s = calloc(n, sizeof(char*));
    for (int i = 0; i < n; i++)
    {
	s[i] = calloc(11, sizeof(char));
	fscanf(fptr, "%s", s[i]);
    } do {
      for (int i = 0; i < n; i++)
          printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
    } while (next_permutation(n, s));
    for (int i = 0; i < n; i++)
 	free(s[i]);
    free(s);
    return 0;
}
*/
