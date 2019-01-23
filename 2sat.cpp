// 228 e
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(a) (ll)((a).size())
#define heap priority_queue
#define hash_map unordered_map
#define hash_set unordered_set
#define ft first
#define sd second
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl "\n"
#define mineq(a, b) (a) = min((a), (b))
#define maxeq(a, b) (a) = max((a), (b))
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

struct ngraph {
	ll n;
	vector<vll> adj;
	ngraph() {}
	ngraph(ll n_) {
		n = n_;
		adj.assign(n, vll(n, -1));
	}
	void insert(ll v, ll u, ll c) {
		adj[v][u] = c;
		adj[u][v] = c;
	}
};

struct graph {
	ll n;
	map<pll, vector<pll>> adj;
	graph() {}
	graph(ll n_) {
		n = n_;
		for (ll i = 0; i < n; i++) {
			for (ll j = 0; j < 2; j++) {
				adj[{i, j}] = {};
			}
		}
	}
	void insert(pll v, pll u) {
		adj[v].pb(u);
		adj[u].pb(v);
	}
};

ll n, m;
ngraph in;
graph g;
map<pll, ll> used;
vector<pll> order;
vll ans, vis;

void build() {
	g = graph(n);
	for (ll v = 0; v < n; v++) {
		for (ll u = 0; u < n; u++) {
			if (in.adj[v][u] == -1) {
				continue;
			}
			if (in.adj[v][u]) {
				g.insert({ v, 0 }, { u, 0 });
				g.insert({ v, 1 }, { u, 1 });
			} else {
				g.insert({ v, 1 }, { u, 0 });
				g.insert({ v, 0 }, { u, 1 });
			}
		}
	}
}

void tsort(pll v) {
	used[v] = 1;
	for (pll u : g.adj[v]) {
		if (used[u]) {
			continue;
		}
		tsort(u);
	}
	order.pb(v);
}

void css(pll v) {
	ans[v.ft] = v.sd;
	used[v] = 1;
	for (pll u : g.adj[v]) {
		if (used[u]) {
			continue;
		}
		css(u);
	}
}

inline void solve() {
	build();
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < 2; j++) {
			if (!used[{i, j}]) {
				tsort({ i, j });
			}
		}
	}
	used.clear();
	reverse(all(order));
	ans.assign(n, -1);
	for (pll v : order) {
		if (!used[v]) {
			css(v);
		}
	}
	for (ll v = 0; v < n; v++) {
		for (ll u = 0; u < n; u++) {
			if (ans[v] && in.adj[v][u] != -1) {
				in.adj[v][u] ^= 1;
				in.adj[u][v] ^= 1;
			}
		}
	}
	for (ll v = 0; v < n; v++) {
		for (ll u = 0; u < n; u++) {
			if (abs(in.adj[v][u]) != 1) {
				cout << "Impossible" << endl;
				return;
			}
		}
	}
	vll a;
	for (ll i = 0; i < n; i++) {
		if (ans[i]) {
			a.pb(i);
		}
	}
	cout << sz(a) << endl;
	for_each(all(a), [](ll el) {cout << el + 1 << " "; });
	cout << endl;
}

inline void read() {
	cin >> n >> m;
	in = ngraph(n);
	for (ll i = 0; i < m; i++) {
		ll v, u, c;
		cin >> v >> u >> c;
		--v, --u;
		in.insert(v, u, c);
	}
}

int main() {
	fast;
	read();
	solve();
	return 0;
}
