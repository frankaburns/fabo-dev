#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Complete the following function.

int find_nth_term(int n, int a, int b, int c) {
  //Write your code here.
  static int idx    = 0;
  static int target = 0;

         int  sum = 0;
  static int *sums;

  if (idx == 0) {
     sums = malloc(sizeof(int)*n);
     sums[0] = a;
     sums[1] = b;
     sums[2] = c;
     target  = n;
     idx = 3;
  } else {
     idx = n;
  }

  sum = a + b + c;
  sums[idx] = sum;
  
  if (target-1 <= idx) sum = sums[target-1];
  else                 sum = find_nth_term (idx+1, sums[idx],sums[idx-1],sums[idx-2]);
  
  return sum;
}

int main() {
    int n, a, b, c;
  
    scanf("%d %d %d %d", &n, &a, &b, &c);
    int ans = find_nth_term(n, a, b, c);
 
    printf("%d\n", ans); 
    return 0;
}
