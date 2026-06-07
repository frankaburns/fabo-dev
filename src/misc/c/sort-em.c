#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to count unique characters
int count_unique_chars(char* s) {
    // An array to store the presence of ASCII characters (0-127)
    // Initialize all elements to 0
    int counts[128] = {0}; 
    int unique_count = 0;
    int i;

    // Loop through the string until the null terminator
    for (i = 0; s[i] != '\0'; i++) {
        // Use the character's ASCII value as an index
        unsigned char c = (unsigned char)s[i]; 
        
        // If the character hasn't been encountered before, mark it and increment the count
        if (counts[c] == 0) {
            counts[c] = 1; // Mark as encountered
            unique_count++;
        }
    }

    return unique_count;
}


int lexicographic_sort(const char* a, const char* b) {
//
   int ret = 0;
// Use strcmp to compare the actual strings
   const char *str1 = *(const char **)a;
   const char *str2 = *(const char **)b;
   return strcmp(str1, str2);
}

int lexicographic_sort_reverse(const char* a, const char* b) {
   int ret = 0;
// Use strcmp to compare the actual strings
   const char *str1 = *(const char **)a;
   const char *str2 = *(const char **)b;
//
   ret = strcmp(str1, str2);
   ret = (ret < 0) ? abs(ret) : (0-ret);
   return ret;

}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
   int ret = 0;
//
// Use strcmp to compare the actual strings
   const char *str1 = *(const char **)a;
   const char *str2 = *(const char **)b;
   ret = count_unique_chars((char *)str1) - count_unique_chars((char *)str2);
   if (ret == 0) ret = strcmp(str1,str2);
   return ret;
}

int sort_by_length(const char* a, const char* b) {
   int ret = 0;
//
// Use strcmp to compare the actual strings
   const char *str1 = *(const char **)a;
   const char *str2 = *(const char **)b;
   ret = (strlen(str1)-strlen(str2));
   if (ret == 0) ret = strcmp(str1,str2);
   return ret;

}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
 qsort(arr, len, sizeof(char *), cmp_func); 

}


int main() 
{
    int n;
    FILE *fptr = 0;
    const char* filename = "./sort-em.dat";


    // Open the file in read mode ("r")
    fptr = fopen(filename, "r");

    // Check if the file was opened successfully
    if (fptr == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1); // Exit the program if the file cannot be opened
    }

    fscanf(fptr, "%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        fscanf(fptr, "%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}
