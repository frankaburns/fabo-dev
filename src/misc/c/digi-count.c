#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    char *s;
    char one_digit[2] = {0, 0};
    char *endptr;

    int  digits[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};   

    long value;

    s = malloc(1024 * sizeof(char));
    scanf("%[^\n]", s);
    s = realloc(s, strlen(s) + 1);
    
    for (int i=0; i<strlen(s); i++) {
       one_digit[0] = s[i];
       errno = 0; // Clear errno before the call

       value = strtol(&one_digit[0], &endptr, 10); // Base 10

       // Check for various possible errors
       if (errno == ERANGE) {
          printf("Value out of range for long int\n");
       } else if (endptr == &one_digit[0]) {
          printf("No valid digits were found\n");
       } else if (*endptr != '\0') {
          printf("Conversion stopped at character: %c (substring: %s)\n", *endptr, endptr);
       } else {
          digits[value]++;
          printf("Successfully converted value: %ld\n", value);
       }
    }
    for (int i=0; i<sizeof(digits)/sizeof(int); i++) printf ("%d ", digits[i]);
    printf ("\n");

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}

