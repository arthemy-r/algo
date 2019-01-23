// 1100 e
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

struct edge {
	ll v, u, c;
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
	void add(ll v, ll u, ll c) {
		es.pb({ v, u, c });
		adj[v].pb(sz(es) - 1);
	}
};

ll n, m;
graph g;
vll used;
vll order;
vll pos;

ll dfs(ll v, ll sc) {
	used[v] = 1;
	for (ll i : g.adj[v]) {
		edge e = g.es[i];
		ll u = e.u;
		if (e.c <= sc) {
			continue;
		}
		if (used[u] == 2) {
			continue;
		}
		if (used[u] == 1) {
			return 1;
		}
		if (dfs(u, sc)) {
			return 1;
		}
	}
	used[v] = 2;
	return 0;
}

ll check(ll m) {
	used.assign(n, 0);
	ll ok = 0;
	for (ll i = 0; i < n; i++) {
		if (!used[i]) {
			ok |= dfs(i, m);
		}
	}
	return !ok;
}

void tsort(ll v, ll sc) {
	used[v] = 1;
	for (ll i : g.adj[v]) {
		edge e = g.es[i];
		ll u = e.u;
		if (e.c <= sc) {
			continue;
		}
		if (used[u]) {
			continue;
		}
		tsort(u, sc);
	}
	order.pb(v);
}

inline void solve() {
	ll l = -1, r = 1e9 + 10;
	while (r - l > 1) {
		ll m = (l + r) / 2;
		if (check(m)) {
			r = m;
		} else {
			l = m;
		}
	}
	used.assign(n, 0);
	for (ll i = 0; i < n; i++) {
		if (!used[i]) {
			tsort(i, r);
		}
	}
	reverse(all(order));
	pos.assign(n, 0);
	for (ll i = 0; i < n; i++) {
		pos[order[i]] = i;
	}
	vll res;
	for (ll i = 0; i < m; i++) {
		edge e = g.es[i];
		if (e.c <= r) {
			if (pos[e.v] > pos[e.u]) {
				res.pb(i);
			}
		}
	}
	cout << r << " " << sz(res) << endl;
	for (ll i : res) {
		cout << i + 1 << " ";
	}
	cout << endl;
}

inline void read() {
	cin >> n >> m;
	g = graph(n);
	for (ll i = 0; i < m; i++) {
		ll v, u, c;
		cin >> v >> u >> c;
		--v, --u;
		g.add(v, u, c);
	}
}
