// 818 g
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
	vll d, path;
	pll ford_bellman() {
		d.assign(g.n, inf);
		path.assign(g.n, -1);
		d[s] = 0;
		ll f = 1;
		while (f) {
			f = 0;
			for (ll j = 0; j < sz(g.es); j++) {
				edge e = g.es[j];
				if (e.c - e.f == 0) {
					continue;
				}
				if (mineq(d[e.u], d[e.v] + e.p)) {
					path[e.u] = j;
					f = 1;
				}
			}
		}
		ll c = inf;
		ll v = t;
		while (path[v] != -1) {
			mineq(c, g.es[path[v]].c - g.es[path[v]].f);
			v = g.es[path[v]].v;
		}
		v = t;
		ll cost = 0;
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
	ll flow(ll f) {
		ll cost = 0;
		while (f) {
			pll p = ford_bellman();
			cost += p.sd;
			f -= p.ft;
		}
		return cost;
	}
};

const ll K = 4;
ll n;
vll a;
vector<vll> adj;
mcmf mf;

void build() {
	mf.g = graph(n + n + 2);
	mf.s = 2 * n;
	mf.t = 2 * n + 1;
	for (ll i = 0; i < n; i++) {
		for (ll j : adj[i]) {
			mf.g.add(i + n, j, 1, 0);
		}
	}
	for (ll i = 0; i < n; i++) {
		mf.g.add(mf.s, i, 1, 0);
	}
	for (ll i = 0; i < n; i++) {
		mf.g.add(i + n, mf.t, 1, 0);
	}
	for (ll i = 0; i < n; i++) {
		mf.g.add(i, i + n, 1, -1);
	}
}

inline void solve() {
	build();
	ll ans = mf.flow(K);
	cout << abs(ans) << endl;
}

inline void read() {
	cin >> n;
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	adj.resize(n);
	for (ll i = 0; i < n; i++) {
		ll w1 = 0;
		ll w2 = 0;
		ll w3 = 0;
		for (ll j = i + 1; j < n; j++) {
			if (w1 < K && a[i] - a[j] == 1) {
				adj[i].pb(j);
				++w1;
			}
			if (w2 < K && a[i] - a[j] == -1) {
				adj[i].pb(j);
				++w2;
			}
			if (w3 < K && a[i] % 7 == a[j] % 7) {
				adj[i].pb(j);
				++w3;
			}
		}
	}
}
