#include <stdio.h>
#include <cmath> // Or <cstdlib>

using namespace std;

void update(int *a,int *b) {
    int sum;
    int diff;
    
    sum = *a + *b;
    diff = abs(*a - *b);
    *a = sum;
    *b = diff;
    // Complete this function    
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}
