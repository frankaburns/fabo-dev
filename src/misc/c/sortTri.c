#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;

void swap(triangle *tr, double *s, int idx1, int idx2) {
    double dtmp;
    triangle tmp;
    dtmp = s[idx1];
    tmp = tr[idx1];
    s[idx1] = s[idx2];
    s[idx2] = dtmp;
    tr[idx1] = tr[idx2];
    tr[idx2] = tmp;  
}
void sort_by_area(triangle* tr, int n) {
   /**
    * Sort an array a of the length n
    */
    double p = 0;
    double *S = 0;
    
    S = malloc(sizeof(double)*n);
    
    for (int i=0; i<n; i++) {
       p = ((double)tr[i].a+(double)tr[i].b+(double)tr[i].c)/2.0;
       S[i] = sqrt(p*(p-(double)tr[i].a)*(p-(double)tr[i].b)*(p-(double)tr[i].c));
       printf ("S:= %f\n", S[i]);
    }
    
    for (int i=0; i<n-1; i++) {
       for (int j = 0; j < n-i-1; j++) {
           if (S[j] > S[j+1]) {
	      printf ("swap %d with %d\n", j, j+1);
              swap(tr, S, j, j+1);
           }
       }
    }

    for (int i=0; i<n; i++) {
       printf ("S:= %f\n", S[i]);
    }
}

int main()
{
    int n;
    FILE *fptr;
    char character;
    const char* filename = "./data.dat";

    // Open the file in read mode ("r")
    fptr = fopen(filename, "r");

    // Check if the file was opened successfully
    if (fptr == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1); // Exit the program if the file cannot be opened
    }

	
    fscanf(fptr, "%d", &n);
    triangle *tr = malloc(n * sizeof(triangle));
    for (int i = 0; i < n; i++) {
    	fscanf(fptr, "%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
    }
    sort_by_area(tr, n);
    for (int i = 0; i < n; i++) {
      	printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
    }
    return 0;
}
