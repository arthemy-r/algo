// 85 d
#define _CRT_SECURE_NO_WARNINGS
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
#define die(cond) if (cond) for (;;){}
#define y1 y_1
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
const ld pi = acos(-1);
template<typename T> inline bool mineq(T& a, T b) { return (a > b) ? (a = b, 1) : 0; }
template<typename T> inline bool maxeq(T& a, T b) { return (a < b) ? (a = b, 1) : 0; }

inline void solve(), read();
const string file = "";

int main() {
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

const ll SQRT = 320;

struct sqrtd {
	ll n;
	vll a;
	vector<vll> t;
	vector<vector<long long>> s;
	sqrtd() {
		build(1);
	}
	void build(ll n_) {
		n = n_;
		t.assign(SQRT, {});
		s.assign(SQRT, vector<long long>(5, 0));
		for (ll i = 0; i < sz(a); i++) {
			t[i / SQRT].pb(a[i]);
			s[i / SQRT][i % 5] += a[i];
		}
	}
	void rebuild() {
		a.clear();
		for (ll i = 0; i < sz(t); i++) {
			for (ll j = 0; j < sz(t[i]); j++) {
				a.pb(t[i][j]);
			}
		}
		build(sz(a) + 1);
	}
	void add(ll x) {
		ll cl = 0, cr = 0;
		ll was = 0;
		for (ll i = 0; i < sz(t); i++) {
			cr = cl + sz(t[i]) - 1;
			if (t[i].empty() && (i != sz(t) - 1 || was)) {
				continue;
			}
			if (!t[i].empty() && i != sz(t) - 1 && t[i].back() < x) {
				cl += sz(t[i]);
				continue;
			}
			if (was) {
				rotate(s[i].begin(), s[i].begin() + 4, s[i].end());
				cl += sz(t[i]);
				continue;
			}
			was = 1;
			s[i].assign(5, 0);
			auto it = lower_bound(all(t[i]), x);
			t[i].insert(it, x);
			for (ll j = 0; j < sz(t[i]); j++) {
				s[i][(cl + j) % 5] += t[i][j];
			}
			cl += sz(t[i]);
		}
	}
	void del(ll x) {
		ll cl = 0, cr = 0;
		ll was = 0;
		for (ll i = 0; i < sz(t); i++) {
			cr = cl + sz(t[i]) - 1;
			if (t[i].empty()) {
				continue;
			}
			if (t[i].back() < x) {
				cl += sz(t[i]);
				continue;
			}
			if (was) {
				rotate(s[i].begin(), s[i].begin() + 1, s[i].end());
				cl += sz(t[i]);
				continue;
			}
			was = 1;
			s[i].assign(5, 0);
			auto it = lower_bound(all(t[i]), x);
			t[i].erase(it);
			for (ll j = 0; j < sz(t[i]); j++) {
				s[i][(cl + j) % 5] += t[i][j];
			}
			cl += sz(t[i]);
		}
	}
	long long get() {
		long long ans = 0;
		for (ll i = 0; i < sz(t); i++) {
			ans += s[i][2];
		}
		return ans;
	}
};

ll n;
sqrtd sq;

inline void solve() {
	for (ll i = 0; i < n; i++) {
		if (i % (2 * SQRT) == 0) {
			sq.rebuild();
		}
		string s;
		cin >> s;
		if (s == "add") {
			ll x;
			cin >> x;
			sq.add(x);
		} else if (s == "del") {
			ll x;
			cin >> x;
			sq.del(x);
		} else if (s == "sum") {
			long long cur = sq.get();
			cout << cur << endl;
		}
	}
}

inline void read() {
	cin >> n;
}
