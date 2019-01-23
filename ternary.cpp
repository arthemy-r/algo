// 106 e
#pragma GCC optimize("Ofast", "unroll-loops")
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
#define die(cond) if (cond) for(;;){}
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vector<ll> vll;
typedef set<ll> sll;
typedef map<ll, ll> mll;
const ll inf = numeric_limits<ll>::max() / 2;
const ld eps = 1e-6;
const ld pi = acos(-1);

inline void solve(), read();

int main() {
	fast;
	read();
	solve();
	return 0;
}

const ld MINX = -1e4 - 1;
const ld MAXX = 1e4 + 1;
ll n;
vll xs, ys, zs;

ld X = 0, Y = 0, Z = 0;

inline ld check(ld x, ld y, ld z) {
	ld ans = 0;
	for (ll i = 0; i < n; i++) {
		ld x2 = (x - xs[i])*(x - xs[i]);
		ld y2 = (y - ys[i])*(y - ys[i]);
		ld z2 = (z - zs[i])*(z - zs[i]);
		ld cur = sqrt(x2 + y2 + z2);
		maxeq(ans, cur);
	}
	return ans;
}

inline ld ztern(ld x, ld y) {
	ld l = MINX, r = MAXX;
	while (abs(r - l) > eps) {
		ld d = (r - l) / 3;
		ld m1 = l + d, m2 = r - d;
		ld a1 = check(x, y, m1);
		ld a2 = check(x, y, m2);
		if (a1 < a2) {
			r = m2;
		} else {
			l = m1;
		}
	}
	Z = l;
	return check(x, y, l);
}

inline ld ytern(ld x) {
	ld l = MINX, r = MAXX;
	while (abs(r - l) > eps) {
		ld d = (r - l) / 3;
		ld m1 = l + d, m2 = r - d;
		ld a1 = ztern(x, m1);
		ld a2 = ztern(x, m2);
		if (a1 < a2) {
			r = m2;
		} else {
			l = m1;
		}
	}
	Y = l;
	return ztern(x, l);
}

inline void xtern() {
	ld l = MINX, r = MAXX;
	while (abs(r - l) > eps) {
		ld d = (r - l) / 3;
		ld m1 = l + d, m2 = r - d;
		ld a1 = ytern(m1);
		ld a2 = ytern(m2);
		if (a1 < a2) {
			r = m2;
		} else {
			l = m1;
		}
	}
	X = l;
}

inline void solve() {
	xtern();
	cout << setprecision(40) << fixed;
	cout << X << " " << Y << " " << Z << endl;
}

inline void read() {
	cin >> n;
	xs.resize(n), ys.resize(n), zs.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> xs[i] >> ys[i] >> zs[i];
	}
}
