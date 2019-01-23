// 1061 e
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
const ll inf = 1e12;
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
	ll v, u, c, f, p;
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
	void add(ll v, ll u, ll c, ll p) {
		es.pb({ v, u, c, 0, +p });
		adj[v].pb(sz(es) - 1);
		es.pb({ u, v, 0, 0, -p });
		adj[u].pb(sz(es) - 1);
	}
};
struct mcmf {
	graph g;
	ll s, t;
	vll d, path, phi;
	void ford_bellman() {
		d.assign(g.n, inf);
		d[s] = 0;
		for (ll i = 0; i < g.n; i++) {
			for (edge e : g.es) {
				if (e.c - e.f == 0) {
					continue;
				}
				mineq(d[e.u], d[e.v] + e.p);
			}
		}
		phi = d;
	}
	pll dijkstra() {
		d.assign(g.n, inf);
		path.assign(g.n, -1);
		heap<pll> q;
		d[s] = 0;
		q.push({ -d[s], s });
		while (!q.empty()) {
			ll v, dist;
			tie(dist, v) = q.top();
			q.pop();
			if (dist != -d[v]) {
				continue;
			}
			for (ll i : g.adj[v]) {
				edge e = g.es[i];
				if (e.c - e.f == 0) {
					continue;
				}
				ll w = e.p + phi[e.u] - phi[e.v];
				if (mineq(d[e.u], d[e.v] + w)) {
					q.push({ -d[e.u], e.u });
					path[e.u] = i;
				}
			}
		}
		phi = d;
		ll c = inf;
		ll v = t;
		while (path[v] != -1) {
			mineq(c, g.es[path[v]].c - g.es[path[v]].f);
			v = g.es[path[v]].v;
		}
		ll cost = 0;
		v = t;
		while (path[v] != -1) {
			g.es[path[v]].f += c;
			g.es[path[v] ^ 1].f -= c;
			cost += g.es[path[v]].p * c;
			v = g.es[path[v]].v;
		}
		if (c == inf) {
			c = 0;
		}
		return { c, cost };
	}
	pll flow() {
		ford_bellman();
		ll cost = 0;
		ll flow = 0;
		do {
			pll p = dijkstra();
			cost += p.sd;
			flow += p.ft;
		} while (d[t] != inf);
		return { flow, cost };
	}
};

ll n, x, y, q1, q2;
vll a;
graph g1, g2;
vll d1, d2;
vll col1, col2;
vll sub1, sub2;
mcmf mf;

ll dfs(ll v, ll p, graph& g, vll& col, vll& d, vll& sub, ll good) {
	if (d[v]) {
		good = v;
	}
	col[v] = good;
	for (ll i : g.adj[v]) {
		edge e = g.es[i];
		if (e.u == p) {
			continue;
		}
		sub[v] += dfs(e.u, v, g, col, d, sub, good);
	}
	return max(d[v], sub[v]);
}

void build() {
	mf.g = graph(2 * n + 2);
	mf.s = 2 * n;
	mf.t = 2 * n + 1;
	for (ll i = 0; i < n; i++) {
		if (d1[i]) {
			ll c = d1[i] - sub1[i];
			if (c < 0) {
				cout << -1 << endl;
				exit(0);
			}
			mf.g.add(mf.s, i, c, 0);
		}
	}
	for (ll i = 0; i < n; i++) {
		if (d2[i]) {
			ll c = d2[i] - sub2[i];
			if (c < 0) {
				cout << -1 << endl;
				exit(0);
			}
			mf.g.add(n + i, mf.t, c, 0);
		}
	}
	for (ll i = 0; i < n; i++) {
		ll v = col1[i], u = col2[i] + n;
		mf.g.add(v, u, 1, -a[i]);
	}
}

inline void solve() {
	col1.assign(n, -1);
	col2.assign(n, -1);
	sub1.assign(n, 0);
	sub2.assign(n, 0);
	dfs(x, x, g1, col1, d1, sub1, x);
	dfs(y, y, g2, col2, d2, sub2, y);
	build();
	pll ans = mf.flow();
	if (ans.ft != d1[x] || ans.ft != d2[y]) {
		cout << -1 << endl;
		return;
	}
	cout << -ans.sd << endl;
}

inline void read() {
	cin >> n >> x >> y;
	--x, --y;
	a.resize(n);
	g1 = graph(n);
	g2 = graph(n);
	d1.resize(n, 0), d2.resize(n, 0);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (ll i = 0; i < n - 1; i++) {
		ll v, u;
		cin >> v >> u;
		--v, --u;
		g1.add(v, u, 0, 0);
	}
	for (ll i = 0; i < n - 1; i++) {
		ll v, u;
		cin >> v >> u;
		--v, --u;
		g2.add(v, u, 0, 0);
	}
	cin >> q1;
	for (ll i = 0; i < q1; i++) {
		ll k, x;
		cin >> k >> x;
		--k;
		d1[k] = x;
	}
	cin >> q2;
	for (ll i = 0; i < q2; i++) {
		ll k, x;
		cin >> k >> x;
		--k;
		d2[k] = x;
	}
}
