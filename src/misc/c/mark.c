#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//Complete the following function.

int marks_summation(int* marks, int number_of_students, char gender) {
  //Write your code here.
  int mod = 0;
  int sum = 0;
  if (gender == 'g') mod = 1;
  for (int i=mod; i<number_of_students; i+=2){
     sum += marks[i];
  }
  return sum; 
}

int main() {
    int number_of_students;
    char gender;
    int sum;
    
    FILE *fptr = 0;
    char character;
    const char* filename = "./marks.dat";


    // Open the file in read mode ("r")
    fptr = fopen(filename, "r");

    // Check if the file was opened successfully
    if (fptr == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1); // Exit the program if the file cannot be opened
    }


  
    fscanf(fptr, "%d", &number_of_students);
    int *marks = (int *) malloc(number_of_students * sizeof (int));
 
    for (int student = 0; student < number_of_students; student++) {
        fscanf(fptr, "%d", (marks + student));
    }
    
    fscanf(fptr, " %c", &gender);
    sum = marks_summation(marks, number_of_students, gender);
    printf("%d\n", sum);
    free(marks);
 
    return 0;
}
