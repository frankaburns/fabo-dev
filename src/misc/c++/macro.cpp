/* Enter your macros here */
#define INF 10000000

#define minimum(a, b) ((a) < (b) ? (a) : (b))
#define maximum(a, b) ((a) > (b) ? (a) : (b))

#define TO_STR_HELPER(x) #x
#define toStrStr(x) TO_STR_HELPER(x)

#define FUNCTION(NAME, OP) \
    template<typename T> \
    T NAME(T a, T b) { \
        return (a OP b) ? a : b; \
    }

#include <iostream>
#include <vector>
using namespace std;

#if !defined toStr || !defined io || !defined FUNCTION || !defined INF
#error Missing preprocessor definitions
#endif 

FUNCTION(minimum, <)
FUNCTION(maximum, >)

int main(){
	int n; cin >> n;
	vector<int> v(n);
	foreach(v, i) {
		io(v)[i];
	}
	int mn = INF;
	int mx = -INF;
	foreach(v, i) {
		minimum(mn, v[i]);
		maximum(mx, v[i]);
	}
	int ans = mx - mn;
	cout << toStr(Result =) <<' '<< ans;
	return 0;

}
