// 1068 d
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
typedef int ll;
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

struct fast_io {
	inline char read_char() {
		char c = _getchar_nolock();
		while (c <= 32) {
			c = _getchar_nolock();
		}
		return c;
	}
	inline ll read_int() {
		ll ans = 0;
		char c = _getchar_nolock();
		while (c <= 32) {
			c = _getchar_nolock();
		}
		bool sign = 0;
		if (c == '-') {
			sign = 1;
			c = _getchar_nolock();
		}
		while ('0' <= c && c <= '9') {
			ans = (ans << 3) + (ans << 1) + (c - '0');
			c = _getchar_nolock();
		}
		if (sign) {
			ans = -ans;
		}
		return ans;
	}
	inline string read_string(bool full = 0) {
		string ans = "";
		char c = _getchar_nolock();
		while (c == 32) {
			c = _getchar_nolock();
		}
		while (full ? (c != '\n') : (c > 32)) {
			ans.pb(c);
			c = _getchar_nolock();
		}
		return ans;
	}
	inline void write_string(string s) {
		for (char c : s) {
			_putchar_nolock(c);
		}
	}
	inline void write_int(ll x) {
		write_string(to_string(x));
	}
	inline void write_char(char c) {
		_putchar_nolock(c);
	}
} io;
const ll MAXN = 1e5 + 10;
const ll MAXC = 200;
const ll R = 998244353;

ll n;
vll a;
ll dp[MAXN][MAXC + 10][2];
ll pref[MAXC + 10][2];

inline void solve() {
	for (ll j = 1; j <= MAXC; j++) {
		if (a[0] != j && a[0] != -1) {
			continue;
		}
		dp[0][j][0] = 1;
	}
	for (ll j = 1; j <= MAXC; j++) {
		pref[j][0] = dp[0][j][0] + pref[j - 1][0];
		pref[j][0] %= R;
		pref[j][1] = dp[0][j][1] + pref[j - 1][1];
		pref[j][1] %= R;
	}
	for (ll i = 1; i < n; i++) {
		for (ll j = 1; j <= MAXC; j++) {
			if (a[i] != -1 && a[i] != j) {
				continue;
			}
			dp[i][j][0] += (pref[j - 1][0] + pref[j - 1][1]) % R;
			dp[i][j][0] %= R;
			dp[i][j][1] += dp[i - 1][j][0];
			dp[i][j][1] %= R;
			dp[i][j][1] += (pref[MAXC][1] - pref[j - 1][1] + R) % R;
			dp[i][j][1] %= R;
		}
		for (ll j = 1; j <= MAXC; j++) {
			pref[j][0] = dp[i][j][0] + pref[j - 1][0];
			pref[j][0] %= R;
			pref[j][1] = dp[i][j][1] + pref[j - 1][1];
			pref[j][1] %= R;
		}
	}
	ll ans = pref[MAXC][1];
	io.write_int(ans);
}

inline void read() {
	n = io.read_int();
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		a[i] = io.read_int();
	}
}
