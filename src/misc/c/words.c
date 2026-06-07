#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    char *token;
    char *s;
    
    s = malloc(1024 * sizeof(char));
    scanf("%[^\n]", s);
    s = realloc(s, strlen(s) + 1);
    //Write your logic to print the tokens of the sentence here.
    token = strtok(s, " ");
    while (token != NULL) {
        printf ("%s", token);
        token = strtok(NULL, " ");
        if (token != NULL) printf("\n");
    }
    return 0;
}
