#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void) {

char *string ="abaabcfjgtalkhrgiugwfgadsgjhasdgqoirgrg";

typedef struct {
     char symbol;
     int  count;
} charCnt;

typedef int bool;

#define TRUE 1
#define FALSE 0

bool found = FALSE;

int i = 0;
int j = 0;
int count = 0;

charCnt **arr = 0;

   if ((arr = (charCnt **)malloc (sizeof (charCnt **)))) {
     arr[0] = (charCnt *) malloc(sizeof(charCnt));
     memset ( arr[0], 0, sizeof (charCnt));
     arr[count]->count++ ;
     arr[count++]->symbol = string[0];

     for (i=1; i<strlen (string); i++, found=FALSE) {
        for (j=0; j<count; j++) {
          if (string[i] == arr[j]->symbol) {
             arr[j]->count++;
             found = TRUE;
             break;
          }
        }

        if (!found) {
          arr = (charCnt **) realloc (arr, sizeof(charCnt **)*(count+1));
          arr[count] = (charCnt *) malloc(sizeof(charCnt));
          memset ( arr[count], 0, sizeof (charCnt));
          arr[count]->count++ ;
          arr[count++]->symbol = string[i];
        }
      }
      printf ( "String Contains: %d like symols in a %d size string\n", count, (int)strlen(string));
      for ( i=0; i< count; i++) {
         printf ( "Symbol %c appeared %d times\n", arr[i]->symbol, arr[i]->count);
         free (arr[i]); arr[i] = 0;
      }
      free (arr);
      arr = 0;
   } else {
     printf ("malloc error");
   }
}
