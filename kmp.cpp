// 291 e
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

struct edge {
	ll v, u;
	string s;
};

struct graph {
	ll n;
	vector<edge> es;
	vector<vll> adj;
	graph() {}
	graph(ll n_) {
		n = n_;
		adj.resize(n);
	}
	void add(ll v, ll u, string& s) {
		es.pb({ v, u, s });
		adj[v].pb(sz(es) - 1);
		adj[u].pb(sz(es) - 1);
	}
};

ll n;
graph g;
string cur;
vll p;
string t;
ll ans = 0;
ll ptr = 0;

vll prefix(string& s) {
	n = sz(s);
	p.resize(n);
	p[0] = 0;
	for (ll i = 1; i < n; i++) {
		ll j = p[i - 1];
		while (j && s[i] != s[j]) {
			j = p[j - 1];
		}
		if (s[i] == s[j]) {
			++j;
		}
		p[i] = j;
	}
	return p;
}
void add(ll i, char c, ll s, ll pos) {
	cur[i] = c;
	p[i] = 0;
	ll j = p[i - 1];
	while (j && cur[i] != cur[j]) {
		j = p[j - 1];
		if (s - pos + 1 + j < sz(t) - 1) {
			break;
		}
	}
	if (cur[i] == cur[j]) {
		++j;
	}
	p[i] = j;
	if (p[i] == sz(t)) {
		++ans;
	}
}

void dfs(ll v, ll p) {
	for (ll i : g.adj[v]) {
		edge e = g.es[i];
		ll u = (e.v == v) ? e.u : e.v;
		if (u == p) {
			continue;
		}
		ll old = ptr;
		for (ll i = 0; i < sz(e.s); i++) {
			add(ptr++, e.s[i], sz(e.s), i);
		}
		dfs(u, v);
		ptr = old;
	}
}

inline void solve() {
	dfs(0, 0);
	cout << ans << endl;
}

inline void read() {
	cin >> n;
	g = graph(n);
	ll sum = 0;
	for (ll i = 1; i < n; i++) {
		ll p;
		string s;
		cin >> p >> s;
		--p;
		g.add(i, p, s);
		sum += sz(s);
	}
	cin >> t;
	cur = t + "#";
	prefix(cur);
	ptr = sz(cur);
	cur.resize(ptr + sum);
	p.resize(ptr + sum);
}
