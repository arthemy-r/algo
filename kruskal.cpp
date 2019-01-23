// 609 e
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>
#define pb push_back //
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
#define endl "\n"
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
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

const ll LOG = 30;

struct edge {
	ll v, u, w;
	edge() {}
	edge(ll v, ll u, ll w) : v(v), u(u), w(w) {}
	bool operator < (edge e1) {
		if (w == e1.w) {
			return pll(v, u) < pll(e1.v, e1.u);
		}
		return w < e1.w;
	}
};

struct graph {
	ll n;//
	vector<vector<edge>> adj;
	vector<edge> es;
	graph() {}
	graph(ll n_) {
		n = n_;
		adj.resize(n);
	}
	void insert(ll v, ll u, ll w) {
		adj[v].pb({ v, u, w });
		adj[u].pb({ u, v, w });
		es.pb({ v, u, w });
	}
};

struct dsu {
	ll n;
	vll t, rk;
	dsu() {}
	dsu(ll n_) {
		n = n_;
		t.resize(n);
		iota(all(t), 0);
		rk.assign(n, 1);
	}
	ll find(ll v) {
		if (v == t[v]) {
			return v;
		}
		return t[v] = find(t[v]);
	}
	void join(ll a, ll b) {
		a = find(a), b = find(b);
		if (a != b) {
			if (rk[a] < rk[b]) {
				swap(a, b);
			}
			t[b] = a;
			if (rk[a] == rk[b]) {
				++rk[a];
			}
		}
	}
};

ll n, m, stw, timer = 0;
graph g, st;
dsu d;
vll ans, tin, tout, ind, dep;
vector<vll> up, binmax;

bool comp(ll a, ll b) {
	return g.es[a] < g.es[b];
}

void kruskal() {
	ind.resize(m);
	iota(all(ind), 0);
	sort(all(ind), comp);
	d = dsu(g.n);
	st = graph(g.n);
	vll r;
	stw = 0;
	for (ll i : ind) {
		edge e = g.es[i];
		ll v = e.v, u = e.u;
		if (d.find(v) != d.find(u)) {
			d.join(v, u);
			st.insert(e.v, e.u, e.w);
			stw += e.w;
			r.pb(i);
		}
	}
	for (ll i : r) {
		ans[i] = stw;
	}
}

void dfs(ll v, ll w, ll p) {
	dep[v] = dep[p] + 1;
	up[v][0] = p;
	binmax[v][0] = w;
	for (ll i = 1; i < LOG; i++) {
		up[v][i] = up[up[v][i - 1]][i - 1];
		binmax[v][i] = max(binmax[v][i - 1], binmax[up[v][i - 1]][i - 1]);
	}
	tin[v] = timer++;
	for (edge e : st.adj[v]) {
		if (e.u == p) {
			continue;
		}
		dfs(e.u, e.w, v);
	}
	tout[v] = timer++;
}

bool upper(ll a, ll b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

ll lca(ll a, ll b) {
	if (upper(a, b)) {
		return a;
	}
	if (upper(b, a)) {
		return b;
	}
	for (ll i = LOG - 1; i >= 0; i--) {
		if (!upper(up[a][i], b)) {
			a = up[a][i];
		}
	}
	return up[a][0];
}

bool checkbit(ll n, ll p) {
	return n & (1 << p);
}

ll getmax(ll a, ll b) {
	ll maxx = 0;
	ll diff = dep[a] - dep[b];
	for (ll i = LOG; i >= 0; i--) {
		if (checkbit(diff, i)) {
			maxeq(maxx, binmax[a][i]);
			a = up[a][i];
		}
	}
	return maxx;
}

ll add(ll v, ll u, ll w) {
	ll c = lca(v, u);
	ll m1 = getmax(v, c), m2 = getmax(u, c);
	ll m = max(m1, m2);
	return stw - m + w;
}

inline void solve() {
	kruskal();
	tin.resize(st.n), tout.resize(st.n);
	dep.resize(st.n);
	dep[0] = -1;
	up.assign(st.n, vll(LOG, 0));
	binmax.assign(st.n, vll(LOG, 0));
	dfs(0, 0, 0);
	for (ll i = 0; i < sz(g.es); i++) {
		if (ans[i]) {
			continue;
		}
		edge e = g.es[i];
		ans[i] = add(e.v, e.u, e.w);
	}
	for_each(all(ans), [](ll el) {cout << el << endl; });
}

inline void read() {
	cin >> n >> m;
	g = graph(n);
	ans.resize(m, 0);
	for (ll i = 0; i < m; i++) {
		ll v, u, w;
		cin >> v >> u >> w;
		--v, --u;
		g.insert(v, u, w);
	}
}

int main() {
	fast;
	read();
	solve();
	return 0;
}
