#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void print_pattern(int size) {
    int  i, j;

    int  mid_val;
    int  mid_cnt;
    int  b_count;

    int  cols = size*2-1;
    int  rows = size*2-1;
    int *border = 0;

    border = malloc(sizeof(int)*(size-1));

    // build the border for this pattern
    for (i=0; i<size-1; i++) {
       border[i] = size-i;
    }
   
    b_count = 0;

    // Outer loop for rows
    for (i=0; i<rows; i++) {
       // set the middle fill value
       if (i < size) {
	  mid_val = size - i;
          mid_cnt = cols - b_count*2;
       } else {
	  mid_val++;
          mid_cnt = cols - b_count*2;
       }

       // Inner left border loop for columns
       for (j=0; j<b_count; j++) {
          printf("%d ", border[j]);
       }

       // Inner mjddle loop for columns
       for (j=0; j<mid_cnt; j++) {
          printf("%d ", mid_val);
       }
       // Inner rjght border loop for columns
       for (j=b_count;j>0; j--) {
          printf("%d ", border[j-1]);
       }
       printf("\n");
       if (i<size-1) b_count++;
       else        b_count--; 

    }
}
    
int main() 
{

    int n;
    scanf("%d", &n);
    // Complete the code to print the pattern.
    print_pattern(n);
    return 0;
}
