// 898 f
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
#define y0 y0998244353
#define y1 y1998244353
#define die(cond) if (cond) for (;;) {}
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
const ld pi = acosl(-1);
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

const ll R = 1e9+637;
const ll P = 10;

struct shash {
	ll n;
	string s;
	vll ps;
	vll hs;
	shash() {}
	shash(string& s_) {
		s = s_;
		n = sz(s);
		hs.resize(n);
		hs[0] = s[0] - '0';
		for (ll i = 1; i < n; i++) {
			hs[i] = hs[i - 1] * P % R + (s[i] - '0');
			hs[i] %= R;
		}
		ps.resize(n);
		ps[0] = 1;
		for (ll i = 1; i < n; i++) {
			ps[i] = ps[i - 1] * P % R;
		}
	}
	ll gethash(ll l, ll r) {
		if (r >= n || l >= n) {
			return rand() % R;
		}
		if (l == 0) {
			return hs[r];
		}
		return (hs[r] - hs[l - 1] * ps[r - l + 1] % R + R) % R;
	}
};

string s;
shash hs;

ll check(ll i, ll j) {
	if (i + 1 >= sz(s) || j + 1 >= sz(s)) {
		return 0;
	}
	if (j < 0) {
		return 0;
	}
	if (i + 1 > j) {
		return 0;
	}
	if (s[i + 1] == '0' && j - (i + 1) + 1 > 1) {
		return 0;
	}
	if (s[j + 1] == '0' && sz(s) - 1 - (j + 1) + 1 > 1) {
		return 0;
	}
	ll h1 = hs.gethash(0, i);
	ll h2 = hs.gethash(i + 1, j);
	ll h3 = hs.gethash(j + 1, sz(s) - 1);
	ll hs = (h1 + h2) % R;
	if (h3 == hs) {
		return 1;
	}
	return 0;
}
void print(ll I, ll J) {
	for (ll k = 0; k <= I; k++) {
		cout << s[k];
	}
	cout << "+";
	for (ll k = I + 1; k <= J; k++) {
		cout << s[k];
	}
	cout << "=";
	for (ll k = J + 1; k < sz(s); k++) {
		cout << s[k];
	}
	cout << endl;
}

inline void solve() {
	hs = shash(s);
	for (ll i = 0; i < sz(s) - 2; i++) {
		for (ll j = i - 3; j <= i + 3; j++) {
			ll I = i, J = sz(s) - j;
			if (check(I, J)) {
				print(I, J);
				return;
			}
		}
		ll len = (sz(s) - i) / 2;
		for (ll j = len - 3; j <= len + 3; j++) {
			ll I = i, J = i + j - 1;
			if (check(I, J)) {
				print(I, J);
				return;
			}
		}
	}
}

inline void read() {
	cin >> s;
}
