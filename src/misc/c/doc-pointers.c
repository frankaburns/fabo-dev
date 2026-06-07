#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

//
//
char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
   return document[--n][--m][--k];
}

//
//
char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
   return document[--m][--k];
}

//
//
char*** kth_paragraph(char**** document, int k) {
   return document[--k];
}

//
//
//
char ***get_paragraph(char *data) {
   int w_count = 0;
   int s_count = 0;


   char *dot_ptr = 0;
   char *token;

   char  eol    = '\n';
   char  dot    = '.';
   char  space  = ' ';

   static char  **words = 0;

   static int     num_para = 0;
   static bool    first = true;
   static char ***para;

   // get a new paragraph.
   // 

   if (first) {
      first = false;

      words = 0;
      w_count = 0;
      num_para = 1;
      
   } else {
      num_para++;
   }
   para = (char ***)malloc(sizeof(char ***));

   *para = (char **)malloc(sizeof(char **));
   s_count = 1;

   // Get the first token
   // The first call uses the original string pointer
   token = strtok(data, " ");

   // Walk through other tokens
   while (token != NULL) {

      w_count++;
      if (words == 0) {
         words = (char **)malloc(sizeof(char **));
      } else {
         words = (char **)realloc(words, w_count*sizeof(char **));
      }
      words[w_count-1] = (char *)malloc(strlen(token)+1);

      // Use strchr to find the first occurrence of '.'
      dot_ptr = strchr(token, '.');

      if (dot_ptr != NULL) {
	 if (dot_ptr != (token+strlen(token)-1) && *(dot_ptr+1) != eol) {
	    s_count++;
            *para = (char **)realloc(*para, sizeof(char **)*(s_count));
	    memset (words[w_count-1], 0, strlen(token));
	    strncpy(words[w_count-1], token, (dot_ptr-token));
            *para = words;
            words = (char **)malloc(sizeof(char **));
            w_count = 1;
            words[w_count-1] = (char *)malloc(strlen(token)+1);
	    dot_ptr++;
            strcpy (words[w_count-1], dot_ptr);
         } else {
	   *dot_ptr = 0;
            strcpy (words[w_count-1], token);
            *(para+s_count-1) = words;
	    words = 0;
	    w_count = 0;
	 }
      } else {
         strcpy (words[w_count-1], token);
      }
      token = strtok(NULL, " ");
    }
    
    return para;
}

//
//
//
char**** get_document(char* text) {

           int   p_start = 0;
           int   p_count = 0;

           bool  new_para = false; 
           char *line = 0;
    static char ****doc;

    doc          = (char ****)malloc(sizeof(char ****));
    doc[p_count] = (char ***)malloc(sizeof(char ***));

    for (int i=0; i<strlen(text); i++) {
      if (new_para) {
	  p_count++;
         *doc = (char ***)realloc(*doc, (p_count+1)*sizeof(char ***));
	  new_para = false;
      }
      if (text[i] == '\n' || i == (strlen(text)-1)) {
	 line = (char *)malloc(i-p_start+1);
	 strncpy (line, &text[p_start], i-p_start+1);
	 doc[p_count] = get_paragraph(line);
	 new_para = true;
	 p_start = i+1;
      }
    }
    return doc;
}

//
//
//
char* get_input_text(FILE *fptr) {
    int paragraph_count;
    fscanf(fptr, "%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    fgetc(fptr);
    for (int i = 0; i < paragraph_count; i++) {
        fscanf(fptr, "%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence, FILE *fptr) {
    int word_count;
    fscanf(fptr, "%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
}

void print_paragraph(char*** paragraph, FILE *fptr) {
    int sentence_count;
    fscanf(fptr, "%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i), fptr);
        printf(".");
    }
}

int main() 
{   
    FILE *fptr = 0;
    char character;
    const char* filename = "./doc.dat";


    // Open the file in read mode ("r")
    fptr = fopen(filename, "r");

    // Check if the file was opened successfully
    if (fptr == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1); // Exit the program if the file cannot be opened
    }

    char* text = get_input_text(fptr);
    char**** document = get_document(text);

    int q;
    fscanf(fptr, "%d", &q);

    while (q--) {
        int type;
        fscanf(fptr, "%d", &type);

        if (type == 3){
            int k, m, n;
            fscanf(fptr, "%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            fscanf(fptr, "%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence, fptr);
        }

        else{
            int k;
            fscanf(fptr, "%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph, fptr);
        }
        printf("\n");
    }
}
