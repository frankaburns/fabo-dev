#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};


struct paragraph *get_paragraph(char *data) {
   int w_count = 0;
   int s_count = 0;


   char *dot_ptr = 0;
   char *token;

   char  eol    = '\n';
   char  dot    = '.';
   char  space  = ' ';

   static struct word *words = 0;

   static int    num_para = 0;
   static bool   first = true;
   static struct paragraph *para;

   // get a new paragraph.
   // 

   if (first) {
      first = false;

      w_count = 0;
      num_para = 1;
      
      words = 0;
      para = (struct paragraph *)malloc(sizeof(struct paragraph));
   } else {
      num_para++;
      para = (struct paragraph *)realloc(para, num_para*sizeof(struct paragraph));
   }

   para[num_para-1].data = (struct sentence *)malloc(sizeof(struct sentence));
   para[num_para-1].sentence_count = 1;
   s_count = 1;

   // Get the first token
   // The first call uses the original string pointer
   token = strtok(data, " ");

   // Walk through other tokens
   while (token != NULL) {

      w_count++;
      if (words == 0) {
         words = (struct word *)malloc(sizeof(struct word));
      } else {
         words = (struct word *)realloc(words, w_count*sizeof(struct word));
      }
      words[w_count-1].data = (char *)malloc(strlen(token)+1);

      // Use strchr to find the first occurrence of '.'
      dot_ptr = strchr(token, '.');

      if (dot_ptr != NULL) {
	 printf ("dot_ptr: %lx, token: %lx\n", (unsigned long int)dot_ptr,(unsigned long int)token);
	 if (dot_ptr != (token+strlen(token)-1) && *(dot_ptr+1) != eol) {
            para[num_para-1].data = (struct sentence *)realloc(para[num_para-1].data, sizeof(struct sentence)*(s_count+1));
            para[num_para-1].sentence_count++;
	    printf("Adding word: %s to sentance: %d.\n", token, para[num_para-1].sentence_count);
	    memset (words[w_count-1].data, 0, strlen(token));
	    strncpy(words[w_count-1].data, token, (dot_ptr-token));
            para[num_para-1].data[s_count-1].data = words;
            para[num_para-1].data[s_count-1].word_count = w_count;
            words = (struct word *)malloc(sizeof(struct word));
            w_count = 1;
            words[w_count-1].data = (char *)malloc(strlen(token)+1);
	    dot_ptr++;
            strcpy (words[w_count-1].data, dot_ptr);
	    s_count++;
         } else {
	   *dot_ptr = 0;
	    printf("Adding word: %s to sentance: %d.\n", token, para[num_para-1].sentence_count);
            strcpy (words[w_count-1].data, token);
            para[num_para-1].data[s_count-1].data = words;
            para[num_para-1].data[s_count-1].word_count = w_count;
	    words = 0;
	    w_count = 0;
	 }
      } else {
	 printf("Adding word: %s to sentance: %d.\n", token, para[num_para-1].sentence_count);
         strcpy (words[w_count-1].data, token);
      }
      token = strtok(NULL, " ");
    }
    return para;
}

struct document get_document(char* text) {
    int   p_start = 0;
    char *line = 0;
    static struct document *doc;

    doc = (struct document *)malloc(sizeof(struct document));

    doc->paragraph_count = 0;
    for (int i=0; i<strlen(text); i++) {
      if (text[i] == '\n' || i == (strlen(text)-1)) {
	 line = (char *)malloc(i-p_start+1);
	 strncpy (line, &text[p_start], i-p_start+1);
	 doc->data = get_paragraph(line);
	 doc->paragraph_count++;
	 p_start = i;
      }
    }
    return *doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
   return Doc.data[--n].data[--m].data[--k];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
   return Doc.data[--m].data[--k];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
   return Doc.data[--k];
}


void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

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

int main() 
{   
    FILE *fptr;
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
    struct document Doc = get_document(text);

    int q;
    fscanf(fptr, "%d", &q);

    while (q--) {
        int type;
        fscanf(fptr, "%d", &type);

        if (type == 3){
            int k, m, n;
            fscanf(fptr, "%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            fscanf(fptr, "%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            fscanf(fptr, "%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}
