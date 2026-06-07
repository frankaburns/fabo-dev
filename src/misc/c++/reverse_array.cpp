#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int  array_size;
    int *array;
    
    scanf("%d", &array_size);
    array = (int *)malloc(sizeof(int)*array_size);
    
    for (int i=0; i<array_size-1; i++) {
       scanf("%d ", &array[i]);     
    }
    scanf("%d", &array[array_size-1]);
    
    for (int i=array_size-1; i>0; i--) {
       printf ("%d ", array[i]);
    }
    printf ("%d\n", array[0]);
    return 0;
}
