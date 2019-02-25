// 1107 f
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

struct edge {
	ll v, u, p, c, f = 0;
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
	void add(ll v, ll u, ll p, ll c) {
		es.pb({ v, u, p, c });
		adj[v].pb(sz(es) - 1);
		es.pb({ u, v, -p, 0 });
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
		ll f = 1;
		while (f) {
			f = 0;
			for (edge e : g.es) {
				if (e.c - e.f == 0) {
					continue;
				}
				if (mineq(d[e.u], d[e.v] + e.p)) {
					f = 1;
				}
			}
		}
		phi = d;
	}
	ll dijkstra() {
		d.assign(g.n, inf);
		path.assign(g.n, -1);
		set<pll> q;
		d[s] = 0;
		q.insert({ d[s], s });
		while (!q.empty()) {
			ll v, dist;
			tie(dist, v) = *q.begin();
			q.erase(q.begin());
			for (int i : g.adj[v]) {
				edge e = g.es[i];
				if (e.c - e.f == 0) {
					continue;
				}
				ll w = e.p + phi[e.v] - phi[e.u];
				ll old = d[e.u];
				if (mineq(d[e.u], d[e.v] + w)) {
					q.erase({ old, e.u });
					q.insert({ d[e.u], e.u });
					path[e.u] = i;
				}
			}
		}
		for (ll i = 0; i < g.n; i++) {
			phi[i] += d[i];
		}
		ll c = inf;
		int v = t;
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
		return cost;
	}
	ll max_flow() {
		ford_bellman();
		ll cost = 0;
		ll ans = 0;
		while (1) {
			ll p = dijkstra();
			cost += p;
			if (p >= 0) {
				break;
			}
			mineq(ans, cost);
		}
		return ans;
	}
};

ll n;
vector<int> as, bs, ks;
vector<vll> c;
mcmf M;

void build() {
	c.resize(n, vll(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = as[j] - bs[j] * 1ll * min(i, ks[j]);
		}
	}
	M.g = graph(n + n + 2);
	M.s = n + n, M.t = n + n + 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			M.g.add(i, n + j, -c[i][j], 1);
		}
	}
	for (int i = 0; i < n; i++) {
		M.g.add(M.s, i, 0, 1);
		M.g.add(n + i, M.t, 0, 1);
	}
}

inline void solve() {
	build();
	ll ans = -M.max_flow();
	cout << ans << endl;
}

inline void read() {
	cin >> n;
	as.resize(n), bs.resize(n), ks.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> as[i] >> bs[i] >> ks[i];
	}
}
