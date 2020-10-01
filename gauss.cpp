// 251 d
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#include <random>
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
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define endl "\n"
#define y0 y_0
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
template<typename T> inline bool mineq(T& a, T b) { return (a > b) ? (a = b, 1) : 0; }
template<typename T> inline bool maxeq(T& a, T b) { return (a < b) ? (a = b, 1) : 0; }

inline void solve(), read();
const string file = "";

signed main() {
#ifndef _DEBUG
	if (file != "") {
		freopen((file + ".in").c_str(), "r", stdin);
		freopen((file + ".out").c_str(), "w", stdout);
	}
#endif
	fast;
	read();
	solve();
	return 0;
}

typedef vector<vll> matrix;
const ll LOG = 63;
ll n;
vll a;
ll x;
vll ans;

bool checkbit(ll n, ll p) {
	return n & (1ll << p);
}
ll gauss(matrix& a) {
	ll n = sz(a);
	ll m = sz(a[0]) - 1;
	vll pos(m, -1);
	for (ll i = 0, j = 0; i < n && j < m; j++) {
		for (ll p = i; p < n; p++) {
			if (a[p][j]) {
				swap(a[p], a[i]);
				break;
			}
		}
		if (!a[i][j]) {
			continue;
		}
		pos[j] = i;
		for (ll p = 0; p < n; p++) {
			if (p != i && a[p][j]) {
				for (ll q = j; q <= m; q++) {
					a[p][q] ^= a[i][q];
				}
			}
		}
		++i;
	}
	ans.assign(m, 0);
	for (ll i = 0; i < m; i++) {
		if (pos[i] != -1) {
			ans[i] = a[pos[i]][m];
		}
	}
	for (ll i = 0; i < n; i++) {
		ll s = 0;
		for (ll j = 0; j < m; j++) {
			s ^= ans[j] & a[i][j];
		}
		if (s != a[i][m]) {
			return 0;
		}
	}
	return 1;
}

inline void solve() {
	for (ll i = 0; i < n; i++) {
		x ^= a[i];
	}
	matrix M;
	for (ll j = LOG - 1; j >= 0; j--) {
		if (!checkbit(x, j)) {
			vll b(n, 0);
			for (ll i = 0; i < n; i++) {
				b[i] = checkbit(a[i], j);
			}
			b.pb(1);
			M.pb(b);
			if (!gauss(M)) {
				M.back().back() = 0;
			}
		}
	}
	for (ll j = LOG - 1; j >= 0; j--) {
		if (checkbit(x, j)) {
			vll b(n, 0);
			for (ll i = 0; i < n; i++) {
				b[i] = checkbit(a[i], j);
			}
			b.pb(0);
			M.pb(b);
			if (!gauss(M)) {
				M.back().back() = 1;
			}
		}
	}
	for (ll i = 0; i < n; i++) {
		if (ans[i]) {
			cout << "1 ";
		} else {
			cout << "2 ";
		}
	}
}

inline void read() {
	cin >> n;
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
}
