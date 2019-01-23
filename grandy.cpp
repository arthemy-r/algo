// 1465
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast", "unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define all(a) (a).begin(), (a).end()
#define sz(a) (ll)((a).size())
#define heap priority_queue
#define hash_map unordered_map
#define hash_set unordered_set
#define ft first
#define sd second
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl "\n"
#define mineq(a, b) (a) = ((a)>(b))?(b):(a)
#define maxeq(a, b) (a) = ((a)<(b))?(b):(a)
#define die(cond) if (cond) for (;;){}
#define y1 y_1
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vector<ll> vll;
typedef set<ll> sll;
typedef map<ll, ll> mll;
const ll inf = numeric_limits<ll>::max() / 2;
const ld eps = 1e-9;
const ld pi = acos(-1);

inline void solve(), read();

int main() {
	fast;
	read();
	solve();
	return 0;
}

ll n;
vll g;

vll p1 = { 0, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 0, 5, 2, 2, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 2, 7, 4, 0, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5, 5, 2 };
vll pre = { 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 3, 7, 4, 8, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5, 5, 9 };

ll mex(vll& a) {
	sll b(all(a));
	for (ll i = 0; ; i++) {
		if (!b.count(i)) {
			return i;
		}
	}
	return -1;
}

ll grundy(ll n) {
	if (g[n] != -1) {
		return g[n];
	}
	if (n == 0) {
		return g[n] = 0;
	}
	if (n == 1) {
		return g[n] = 1;
	}
	if (n == 2) {
		return g[n] = 1;
	}
	vll a;
	a.pb(grundy(n - 2));
	for (ll i = 1; i < n - 1; i++) {
		a.pb(grundy(i - 1) ^ grundy(n - i - 2));
	}
	g[n] = mex(a);
	return g[n];
}

inline void solve() {
	/*g.assign(n + 1, -1);
	for (ll i = 1; i <= n; i++) {
		cout << grundy(i) << " ";
	}*/
	ll g = -1;
	if (n < sz(p1)) {
		g = p1[n];
	} else {
		n -= sz(p1);
		g = pre[n%sz(pre)];
	}
	if (g) {
		cout << "White" << endl;
	} else {
		cout << "Black" << endl;
	}
}

inline void read() {
	cin >> n;
}
