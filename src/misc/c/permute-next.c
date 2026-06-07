#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structure to hold the state of the permutation generator
typedef struct {
    char **data;
    size_t length;
    // Internal state variables for the algorithm (e.g., indices)
    // The lexicographical algorithm doesn't need much state beyond the array itself
} PermutationState;

// Helper function to swap two elements
void swap(char *a, char *b) {
    char temp[32];

    strcpy (&temp[0], a);
    strcpy (a, b);
    strcpy (b, temp);
}

// Helper function to reverse a sub-array
void reverse(char **arr, size_t start, size_t end) {
    while (start < end) {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

/**
 * Generates the next permutation in lexicographical order.
 * 
 * @param state Pointer to the PermutationState structure.
 * @return 1 if a new permutation was found, 0 if it was the last permutation 
 *         (meaning the array is now sorted in ascending order for the 'next' 
 *         call to work from the beginning).
 */
int next_permutation_reentrant(PermutationState* state) {
    char **arr = state->data;
    size_t n = state->length;
    int i = n - 2;

    // 1. Find the largest index i such that arr[i] < arr[i + 1]
    while (i >= 0 && strcmp(arr[i], arr[i+1]) > 0) {
        i--;
    }

    // If no such index exists, the permutation is the last one (sorted in descending order)
    if (i < 0) {
        // Optional: reverse to the first permutation to loop around
        reverse(arr, 0, n - 1); 
        return 0; // Indicate that we've wrapped around
    }

    // 2. Find the largest index j greater than i such that arr[i] < arr[j]
    int j = n - 1;
    while (strcmp(arr[i], arr[j]) > 0) {
        j--;
    }

    // 3. Swap the value of arr[i] with that of arr[j]
    swap(arr[i], arr[j]);

    // 4. Reverse the sequence from arr[i + 1] up to and including the final element
    reverse(arr, i + 1, n - 1);

    return 1; // Indicate a new permutation was found
}

int next_permutation(int n, char **arr) {

           int    i   = 0;
           int    j   = 0;
           int    ret = 0;

    static int    dupIndex = 0;
    static bool   firstPermute = true;

    static char **s;
    static char  *dup;

    static PermutationState state;
    
    if (firstPermute) {
       dupIndex     = -1;
       firstPermute = false;

       s   = calloc(n, sizeof(char*));
       dup = calloc(11, sizeof(char));

       for (i,j = 0; i < n; i++) {
          s[i] = calloc(11, sizeof(char));
	  if (i <= n-2) {
             if (!strcmp(arr[i], arr[i+1])) {
		dupIndex = i;
                strcpy (dup, arr[i]);
             } else {
                strcpy (s[j++], arr[i]);
             }
          } else {
             strcpy (s[j++], arr[i]);
          }
       }

       // Initialize the state structure
       // PermutationState state;
       state.data = s;
       state.length = (i == j) ? n : (n-(i-j));
    }
    if (next_permutation_reentrant(&state)) {
       for (i=0,j=0; j<n; i++) {
          if (i == dupIndex) {
             strcpy (arr[j++], dup);
             strcpy (arr[j++], s[i]);
          } else {
             strcpy (arr[j++], s[i]);
          }
       }
       ret = 1;
   } else {
      if (dupIndex == -1) {
         ret          = 0;
         dupIndex     = -1;
         firstPermute = true;
      } else {
	 for (i=0; i<state.length; i++) {
	   strcpy (arr[i], s[i]);
	 }
	 strcpy(arr[i], dup);
         ret          = 1;
         dupIndex     = -1;
      }
   }
   return ret;
}

// Function to print the current permutation
void print_permutation(const PermutationState* state) {
    for (size_t i = 0; i < state->length; i++) {
        printf("%s ", state->data[i]);
    }
    printf("\n");
}

int main() {
    char **s;
    char  *initial_data[] = {"bc", "bc", "cd"};
    size_t n = sizeof(initial_data) / sizeof(initial_data[0]);

    s = calloc(n, sizeof(char*));
    for (int i = 0; i < n; i++) {
       s[i] = calloc(11, sizeof(char));
       strcpy (s[i], initial_data[i]);
    }

    // Initialize the state structure
    PermutationState state;
    state.data = s;
    state.length = n;

    // Start with the initial sorted permutation
    print_permutation(&state); 

    // Generate and print subsequent permutations
    while (next_permutation(n, s)) {
        print_permutation(&state);
    }
    
    return 0;
}

