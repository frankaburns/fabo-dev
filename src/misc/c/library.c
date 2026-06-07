#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * This stores the total number of books in each shelf.
 */
int* total_number_of_books;

/*
 * This stores the total number of pages in each book of each shelf.
 * The rows represent the shelves and the columns represent the books.
 */
int** total_number_of_pages;

int main()
{
    FILE *fptr = 0;
    char character;
    const char* filename = "./library.dat";

    // Open the file in read mode ("r")
    fptr = fopen(filename, "r");

    // Check if the file was opened successfully
    if (fptr == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1); // Exit the program if the file cannot be opened
    }

    int total_number_of_shelves;
    fscanf(fptr, "%d", &total_number_of_shelves);
    total_number_of_pages = malloc(sizeof(int *)*total_number_of_shelves);
    total_number_of_books = malloc(sizeof(int)*total_number_of_shelves);
    
    memset(total_number_of_pages, 0, sizeof(int *)*total_number_of_shelves);
    memset(total_number_of_books, 0, sizeof(int)*total_number_of_shelves);

    int total_number_of_queries;
    fscanf(fptr, "%d", &total_number_of_queries);
    
    while (total_number_of_queries--) {
        int type_of_query;
        fscanf(fptr, "%d", &type_of_query);
        
        if (type_of_query == 1) {
            /*
             * Process the query of first type here.
             */
            int x, y;
            fscanf(fptr, "%d %d", &x, &y);
	    if (total_number_of_pages[x] == 0) total_number_of_pages[x] = malloc(sizeof(int));
	    else total_number_of_pages[x] = realloc(total_number_of_pages[x], (total_number_of_books[x]+1)*sizeof(int));
	    total_number_of_pages[x][total_number_of_books[x]] = y;
	    total_number_of_books[x]++;

        } else if (type_of_query == 2) {
            int x, y;
            fscanf(fptr, "%d %d", &x, &y);
            printf("%d\n", *(*(total_number_of_pages + x) + y));
        } else {
            int x;
            fscanf(fptr, "%d", &x);
            printf("%d\n", *(total_number_of_books + x));
        }
    }

    if (total_number_of_books) {
        free(total_number_of_books);
    }
    
    for (int i = 0; i < total_number_of_shelves; i++) {
        if (*(total_number_of_pages + i)) {
            free(*(total_number_of_pages + i));
        }
    }
    
    if (total_number_of_pages) {
        free(total_number_of_pages);
    }
    
    return 0;
}
