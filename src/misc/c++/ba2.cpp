#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

const unsigned bit_mask = ((1U << 31) - 1);

inline unsigned mask(unsigned num) {
    return num & bit_mask;
}

inline unsigned next_value(unsigned value, unsigned P, unsigned Q) {
    return mask(value * P + Q);
}

int main() {
    // Get the 4 input integers as unsigned ints
    unsigned N, S, P, Q; cin >> N >> S >> P >> Q;
    
    // Used Floyd's tortoise and hare cycle-finding algorithm:
    //  https://en.wikipedia.org/wiki/Cycle_detection
    unsigned tort = mask(S);
    unsigned hare = tort;
    unsigned cycle = 1;
    
    // Calculate the length of a cycle (if one exists) or stop at N
    for (unsigned i = 1; i < N; i++) {
        tort = next_value(tort, P, Q);
        hare = next_value(next_value(hare, P, Q), P, Q);
        cycle++;
        
        if (tort == hare) break;
    }
    
    cout << cycle;
    
    return 0;
}
