#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int   num;
    int   size;
    int   index;
    int   queries;
    int **table;
     
    scanf("%d %d", &num, &queries);
    table = (int **)malloc(sizeof(int *)*num);
    
    for (int tab=0; tab<num; tab++) {
       scanf ("%d", &size);
       table[tab] = (int *)malloc(sizeof(int)*size); 
       for (int i=0; i<size-1; i++) {
          scanf(" %d", &table[tab][i]);     
       }
       scanf("%d", &table[tab][size-1]);
    }
    
    for (int i=0; i<queries; i++) {
       scanf("%d %d", &index, &num);
       printf ("%d\n", table[index][num]);
    }

    return 0;
}
