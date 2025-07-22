#include <stdio.h>

int main (void) {
  int i=0;
  for (i=0; i<61; i++) {
    if ( i%3 == 0 || i%5 == 0) {
      if (i%3 == 0) printf ("fiz");
      if (i%5 == 0) printf ("buzz");
      printf ( " - %d\n", i );
    } else {
   }
  }
}
