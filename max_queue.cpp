// Queue with maximum
// I love meowmur
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

struct maxqueue {
	deque<pll> t;
	ll k;
	maxqueue() {}
	maxqueue(ll k_) {
		k = k_;
	}
	void add(ll i, ll x) {
		while (!t.empty() && i - t[0].sd >= k) {
			t.popf();
		}
		while (!t.empty() && t.back().ft < x) {
			t.popb();
		}
		t.pb({ x, i });
	}
	ll get() {
		return t[0].ft;
	}
};

ll n, k, x;
vll a;
vector<vll> dp;
vector<maxqueue> mq;

inline void solve() {
	mq.assign(n + 1, maxqueue(k));
	dp.assign(n + 1, vll(n + 1, -inf));
	dp[0][0] = 0;
	mq[0].add(0, 0);
	for (ll i = 1; i <= n; i++) {
		mq[i].add(0, -inf);
	}
	for (ll i = 1; i <= n; i++) {
		for (ll j = 1; j <= n; j++) {
			ll cur = mq[j - 1].get();
			if (cur != -inf) {
				dp[i][j] = cur + a[i];
			}
		}
		for (ll j = 0; j <= n; j++) {
			mq[j].add(i, dp[i][j]);
		}
	}
	ll ans = -inf;
	for (ll i = n - k + 1; i <= n; i++) {
		maxeq(ans, dp[i][x]);
	}
	if (ans == -inf) {
		ans = -1;
	}
	cout << ans << endl;
}

inline void read() {
	cin >> n >> k >> x;
	a.resize(n + 1);
	for (ll i = 1; i <= n; i++) {
		cin >> a[i];
	}
}
