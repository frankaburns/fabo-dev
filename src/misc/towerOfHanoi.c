#include <stdio.h>
#include <stdlib.h>


void towerOfHanoi(int n, char fromRod, char toRod, char auxRod) {
    static int count = 0;
    /* printf("In: Disk %d Source %c, Destination %c, Temp %c\n", n, fromRod, toRod, auxRod); */

    if (n == 0) {
        return;
    }
    towerOfHanoi(n - 1, fromRod, auxRod, toRod);
    printf("Disk %d moved from %c to %c, Count %d\n\n", n, fromRod, toRod, ++count);
    towerOfHanoi(n - 1, auxRod, toRod, fromRod);
}

int main(int argc, char **argv) {

    int n = 0;
    if (argc > 1) {
	    n = atoi(argv[1]);
    } else {
	    n = 3;
    }

    // A, B and C are names of rods
    towerOfHanoi(n, 'A', 'C', 'B');
    return 0;
}
