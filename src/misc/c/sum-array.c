#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int num;
    int *data;
    int sum = 0;
    
    FILE *fptr = 0;
    char character;
    const char* filename = "./sum-array.dat";

    // Open the file in read mode ("r")
    fptr = fopen(filename, "r");

    // Check if the file was opened successfully
    if (fptr == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1); // Exit the program if the file cannot be opened
    }
    
    fscanf (fptr, "%d\n", &num);

    data = malloc(sizeof(int)*num);
    for (int i=0; i<num; i++) fscanf (fptr, "%d", &data[i]);
    for (int i=0; i<num; i++) sum += data[i];
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    printf ("%d\n", sum);
    return 0;
}
