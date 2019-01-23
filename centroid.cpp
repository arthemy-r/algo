// 342 e
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

struct graph {
	ll n;
	vector<vll> adj;
	graph() {}
	graph(ll n_) {
		n = n_;
		adj.resize(n);
	}
	void insert(ll v, ll u) {
		adj[v].pb(u);
		adj[u].pb(v);
	}
};

ll n, m;
graph g;
vll sub;
vll cntr;
vll near;
vector<mll> dist;

void subtree(ll v, ll p) {
	sub[v] = 1;
	for (ll u : g.adj[v]) {
		if (u == p || cntr[u] != -1) {
			continue;
		}
		subtree(u, v);
		sub[v] += sub[u];
	}
}

ll centroid(ll v, ll sz, ll p) {
	for (ll u : g.adj[v]) {
		if (u == p || cntr[u] != -1) {
			continue;
		}
		if (sub[u] > sz / 2) {
			return centroid(u, sz, v);
			break;
		}
	}
	return v;
}

void distance(ll v, ll c, ll p, ll d = 0) {
	dist[c][v] = d;
	for (ll u : g.adj[v]) {
		if (u == p || cntr[u] != -1) {
			continue;
		}
		distance(u, c, v, d + 1);
	}
}

void build(ll v, ll parc) {
	ll c = centroid(v, sub[v], parc);
	cntr[c] = parc;
	distance(c, c, c);
	if (dist[c].count(0)) {
		near[c] = dist[c][0];
	}
	for (ll u : g.adj[c]) {
		if (cntr[u] != -1) {
			continue;
		}
		subtree(u, c);
		build(u, c);
	}
}

ll getans(ll v) {
	ll c = v;
	ll ans = inf;
	while (c != inf) {
		mineq(ans, near[c] + dist[c][v]);
		c = cntr[c];
	}
	return ans;
}

void color(ll v) {
	ll c = v;
	while (c != inf) {
		mineq(near[c], dist[c][v]);
		c = cntr[c];
	}
}

inline void solve() {
	sub.resize(n);
	cntr.assign(n, -1);
	near.assign(n, inf);
	dist.resize(n);
	subtree(0, 0);
	build(0, inf);

	for (ll i = 0; i < m; i++) {
		ll op, v;
		cin >> op >> v;
		--v;
		if (op == 1) {
			color(v);
		} else if (op == 2) {
			ll ans = getans(v);
			cout << ans << endl;
		}
	}
}

inline void read() {
	cin >> n >> m;
	g = graph(n);
	for (ll i = 0; i < n - 1; i++) {
		ll v, u;
		cin >> v >> u;
		--v, --u;
		g.insert(v, u);
	}
}

int main() {
	fast;
	read();
	solve();
	return 0;
}
