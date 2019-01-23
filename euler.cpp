// 36 e
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
	if (file != "1") {
		freopen((file + "input.txt").c_str(), "r", stdin);
		freopen((file + "output.txt").c_str(), "w", stdout);
	}
#endif
	fast;
	read();
	solve();
	return 0;
}

struct edge {
	ll v, u;
};
struct graph {
	ll n;
	vll deg;
	vector<edge> es;
	vector<vll> adj;
	graph() {}
	graph(ll n_) {
		n = n_;
		adj.resize(n);
		deg.assign(n, 0);
	}
	void add(ll v, ll u) {
		es.pb({ v, u });
		adj[v].pb(sz(es) - 1);
		adj[u].pb(sz(es) - 1);
		++deg[v], ++deg[u];
	}
};

ll n, m;
vector<pll> a;
graph g;
vector<vll> comp;
vll used;
vll path;
vll eused;

void dfs(ll v) {
	used[v] = 1;
	comp.back().pb(v);
	for (ll i : g.adj[v]) {
		edge e = g.es[i];
		ll u = (e.v == v) ? e.u : e.v;
		if (used[u]) {
			continue;
		}
		dfs(u);
	}
}

void euler(ll v) {
	while (!g.adj[v].empty()) {
		ll i = g.adj[v].back();
		g.adj[v].popb();
		if (eused[i]) {
			continue;
		}
		eused[i] = 1;
		edge e = g.es[i];
		ll u = (e.v == v) ? e.u : e.v;
		euler(u);
		path.pb(i + 1);
	}
}

inline void solve() {
	used.assign(n, 0);
	for (ll i = 0; i < n; i++) {
		if (!used[i]) {
			if (g.adj[i].empty()) {
				continue;
			}
			comp.pb({});
			dfs(i);
		}
	}
	if (sz(comp) > 2) {
		cout << -1 << endl;
		return;
	}
	eused.assign(m + 1, 0);
	if (sz(comp) == 1) {
		vll bad;
		for (ll v : comp[0]) {
			if (g.deg[v] % 2 == 1) {
				bad.pb(v);
			}
		}
		if (sz(bad) > 4 || sz(bad) == 3 || sz(bad) == 1) {
			cout << -1 << endl;
			return;
		}
		eused.assign(m, 0);
		if (sz(bad) == 0) {
			euler(comp[0][0]);
			cout << sz(path) / 2 << endl;
			for (ll i = 0; i < sz(path) / 2; i++) {
				cout << path[i] << " ";
			}
			cout << endl;
			cout << sz(path) - sz(path) / 2 << endl;
			for (ll i = sz(path) / 2; i < sz(path); i++) {
				cout << path[i] << " ";
			}
			cout << endl;
		} else if (sz(bad) == 2) {
			if (m == 1) {
				cout << -1 << endl;
				return;
			}
			euler(bad[0]);
			cout << sz(path) / 2 << endl;
			for (ll i = 0; i < sz(path) / 2; i++) {
				cout << path[i] << " ";
			}
			cout << endl;
			cout << sz(path) - sz(path) / 2 << endl;
			for (ll i = sz(path) / 2; i < sz(path); i++) {
				cout << path[i] << " ";
			}
			cout << endl;
		} else if (sz(bad) == 4) {
			g.add(bad[2], bad[3]);
			euler(bad[0]);
			ll pos = find(all(path), m + 1) - path.begin();
			cout << pos << endl;
			for (ll i = 0; i < pos; i++) {
				cout << path[i] << " ";
			}
			cout << endl;
			cout << m - pos << endl;
			for (ll i = pos + 1; i < sz(path); i++) {
				cout << path[i] << " ";
			}
			cout << endl;
		}
	} else if (sz(comp) == 2) {
		vll bad1;
		ll cnt1 = 0;
		for (ll v : comp[0]) {
			if (g.deg[v] % 2 == 1) {
				bad1.pb(v);
			}
		}
		vll bad2;
		ll cnt2 = 0;
		for (ll v : comp[1]) {
			if (g.deg[v] % 2 == 1) {
				bad2.pb(v);
			}
		}
		if (sz(bad1) == 1 || sz(bad1) > 2 || sz(bad2) == 1 || sz(bad2) > 2) {
			cout << -1 << endl;
			return;
		}
		if (sz(bad1)) {
			euler(bad1[0]);
		} else {
			euler(comp[0][0]);
		}
		cout << sz(path) << endl;
		for (ll i : path) {
			cout << i << " ";
		}
		cout << endl;
		path.clear();
		if (sz(bad2)) {
			euler(bad2[0]);
		} else {
			euler(comp[1][0]);
		}
		cout << sz(path) << endl;
		for (ll i : path) {
			cout << i << " ";
		}
		cout << endl;
	}
}

inline void read() {
	cin >> m;
	for (ll i = 0; i < m; i++) {
		ll v, u;
		cin >> v >> u;
		maxeq(n, v);
		maxeq(n, u);
		--v, --u;
		a.pb({ v, u });
	}
	g = graph(n);
	for (pll p : a) {
		g.add(p.ft, p.sd);
	}
}
