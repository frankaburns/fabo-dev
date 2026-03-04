#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Helper function to swap two elements
void swap(char *a, char *b) {
    char temp[32];

    strcpy (&temp[0], a);
    strcpy (a, b);
    strcpy (b, temp);
}


// Helper to compare for qsort
int compare_strings(const void *a, const void *b) {
    // Cast the void pointers to pointers to char pointers, 
    // then dereference them to get the char pointers (the actual strings)
    const char *str1 = *((const char **)a);
    const char *str2 = *((const char **)b);
    
    // Use strcmp to compare the strings lexicographically
    return strcmp(str1, str2);
}

// Helper to reverse part of the array
void reverse(char **arr, int start, int end) {
    while (start < end) {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

int next_permutation(char **arr, int n) {
    int i = n - 2;
    static bool sort = true;

    // 1. Initial sort is required for lexicographical order
    if (sort) {
       sort = false;
       qsort(arr, n, sizeof(char *), compare_strings);
    }
    // 2. Find the rightmost character smaller than its neighbor
    while (i >= 0 && strcmp(arr[i], arr[i + 1]) >= 0) i--;
    
    if (i < 0) {
      sort = true;
      return 0; // No more permutations
    }

    // 3. Find the ceiling of arr[i] to its right
    int j = n - 1;
    while (strcmp(arr[j], arr[i]) <= 0) j--;

    // 4. Swap them
    swap(arr[i], arr[j]);

    // 5. Reverse the suffix to get the next lexicographical order
    reverse(arr, i + 1, n - 1);
    return 1;
}

int main() {

   char **s;
   char  *initial_data[] = {"a", "a", "bc", "cd"};
   size_t n = sizeof(initial_data) / sizeof(initial_data[0]);

   s = calloc(n, sizeof(char*));
   for (int i = 0; i < n; i++) {
           s[i] = calloc(11, sizeof(char));
         strcpy (s[i], initial_data[i]);
   }

    do {
        for (int i = 0; i < n; i++) printf("%s ", s[i]);
        printf("\n");
    } while (next_permutation(s, n));

    return 0;
}

