// 1082 g
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
const ll inf = numeric_limits<ll>::max() / 10;
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

struct edge {
	ll v, u, c, f;
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
		es.pb({ v, u, c, 0 });
		adj[v].pb(sz(es) - 1);
		es.pb({ u, v, 0, 0 });
		adj[u].pb(sz(es) - 1);
	}
};
struct dinic {
	graph g;
	ll n;
	ll s, t;
	vll d, used, beg;
	ll bfs(ll scale) {
		d.assign(n, inf);
		used.assign(n, 0);
		queue<ll> q;
		used[s] = 1;
		d[s] = 0;
		q.push(s);
		while (!q.empty()) {
			ll v = q.front();
			q.pop();
			for (ll i : g.adj[v]) {
				edge e = g.es[i];
				ll u = e.u;
				if (used[u]) {
					continue;
				}
				if (e.c - e.f >= scale) {
					used[u] = 1;
					q.push(u);
					d[u] = d[v] + 1;
				}
			}
		}
		return d[t] != inf;
	}
	ll dfs(ll v, ll c, ll scale) {
		if (v == t) {
			return c;
		}
		for (; beg[v] < sz(g.adj[v]); beg[v]++) {
			ll i = g.adj[v][beg[v]];
			edge e = g.es[i];
			ll u = e.u;
			if (d[u] != d[v] + 1) {
				continue;
			}
			if (e.c - e.f >= scale) {
				ll c_ = dfs(u, min(c, e.c - e.f), scale);
				if (c_) {
					g.es[i].f += c_;
					g.es[i ^ 1].f -= c_;
					return c_;
				}
			}
		}
		return 0;
	}
	ll maxflow() {
		n = g.n;
		ll ans = 0;
		ll scale = 1ll << 32;
		while (scale) {
			while (bfs(scale)) {
				beg.assign(n, 0);
				ll a;
				while (a = dfs(s, inf, scale)) {
					ans += a;
				}
			}
			scale /= 2;
		}
		return ans;
	}
};

ll n, m;
vll a;
dinic d;
vector<pair<pll, ll>> es;

void build() {
	d.g = graph(n + m + 2);
	d.s = n + m;
	d.t = n + m + 1;
	for (ll i = 0; i < m; i++) {
		d.g.add(d.s, i, es[i].sd);
	}
	for (ll i = 0; i < n; i++) {
		d.g.add(m + i, d.t, a[i]);
	}
	for (ll i = 0; i < m; i++) {
		d.g.add(i, m + es[i].ft.ft, inf);
		d.g.add(i, m + es[i].ft.sd, inf);
	}
}

inline void solve() {
	build();
	ll ans = d.maxflow();
	ll s = 0;
	for (auto p : es) {
		s += p.sd;
	}
	ans = s - ans;
	cout << ans << endl;
}

inline void read() {
	cin >> n >> m;
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (ll i = 0; i < m; i++) {
		ll v, u, w;
		cin >> v >> u >> w;
		--v, --u;
		es.pb({ {v, u}, w });
	}
}
