#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;


void print_all_packages(town t) {
   
   printf("%s:\n", t.name);
   for (int i=0; i<t.offices_count; i++) {
     printf("\t%d:\n", i);
     for (int j=0; j<t.offices[i].packages_count; j++) {
       printf("\t\t%s\n", t.offices[i].packages[j].id);
     }
   }
}

void send_all_acceptable_packages(town* source, int src_idx, town* target, int tgt_idx) {	
	
   int reject_count = 0;
   package *rejects = 0;

   for (int i=0; i<source->offices[src_idx].packages_count; i++) {
     if (source->offices[src_idx].packages[i].weight <= target->offices[tgt_idx].max_weight &&
         source->offices[src_idx].packages[i].weight >= target->offices[tgt_idx].min_weight   ) {

       target->offices[tgt_idx].packages = (package *)realloc (target->offices[tgt_idx].packages, 
		       (target->offices[tgt_idx].packages_count + 1)*sizeof(package));
       target->offices[tgt_idx].packages[target->offices[tgt_idx].packages_count++] = 
		 source->offices[src_idx].packages[i];
     } else {
       reject_count++;
       if (rejects == 0) {
	 rejects = (package *)malloc (reject_count*sizeof(package));
       } else {
	 rejects = (package *)realloc (rejects, reject_count*sizeof(package));
       }
       rejects[reject_count-1] = source->offices[src_idx].packages[i];
     }
   }
   free (source->offices[src_idx].packages);
   source->offices[src_idx].packages_count = reject_count;
   source->offices[src_idx].packages = rejects;
}

town town_with_most_packages(town* towns, int towns_count) {

   int max_mail_town = 0;
   int package_count = 0;
   int max_package_count = 0;
   for (int i=0; i<towns_count; i++) {
     package_count = 0;
     for (int j=0; j<towns[i].offices_count; j++) {
       for (int p=0; p<towns[i].offices[j].packages_count; p++) {
         package_count++;
       }
     }
     if (package_count > max_package_count) {
        max_package_count = package_count;
        max_mail_town = i;
     }
   }
   return towns[max_mail_town];
}

town* find_town(town* towns, int towns_count, char* name) {
    
    town *found = 0;

    for (int i=0; i<towns_count; i++) {
       if (strcmp(name, towns[i].name) == 0) {
          found = &towns[i];
	  break;
       }
    }
    return found;
}

int main()
{
    int towns_count;
    FILE *fptr;
    const char* filename = "./mail.dat";

    // Open the file in read mode ("r")
    fptr = fopen(filename, "r");

    // Check if the file was opened successfully
    if (fptr == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1); // Exit the program if the file cannot be opened
    }

    fscanf(fptr, "%d", &towns_count);
    town* towns = malloc(sizeof(town)*towns_count);
    for (int i = 0; i < towns_count; i++) {
      	towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
      	fscanf(fptr, "%s", towns[i].name);
      	fscanf(fptr, "%d", &towns[i].offices_count);
      	towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
      	for (int j = 0; j < towns[i].offices_count; j++) {
      		fscanf(fptr, "%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
		towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
		for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
			towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
			fscanf(fptr, "%s", towns[i].offices[j].packages[k].id);
			fscanf(fptr, "%d", &towns[i].offices[j].packages[k].weight);
		}
	}
    }

    for (int idx=0; idx<towns_count; idx++) {
      print_all_packages(towns[idx]);
    }

    int queries;
    fscanf(fptr, "%d", &queries);
    char town_name[MAX_STRING_LENGTH];
    while (queries--) {
      	int type;
      	fscanf(fptr, "%d", &type);
      	switch (type) {
      	case 1:
      		fscanf(fptr, "%s", town_name);
      		town* t = find_town(towns, towns_count, town_name);
      		print_all_packages(*t);
      		break;
      	case 2:
      		fscanf(fptr, "%s", town_name);
      		town* source = find_town(towns, towns_count, town_name);
      		int source_index;
      		fscanf(fptr, "%d", &source_index);
      		fscanf(fptr, "%s", town_name);
      		town* target = find_town(towns, towns_count, town_name);
      		int target_index;
      		fscanf(fptr, "%d", &target_index);
      		send_all_acceptable_packages(source, source_index, target, target_index);
      		break;
      	case 3:
      		printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
      		break;
      	}
    }
    return 0;
}
