/* Enter your macros here */

#define INF 10000000

#define TO_STR_HELPER(x) #x
#define toStr(x) TO_STR_HELPER(x)

#define FUNCTION(NAME, OP)  \
template <typename T>   \
   T NAME(T a, T b) {       \
   return (a OP b) ? a : b; \
   }
    
#define io(v) (cin >> v, cin) // Reads the element directly

#define foreach(v, i) \
for(int i=0; i<(int)v.size(); i++)

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
