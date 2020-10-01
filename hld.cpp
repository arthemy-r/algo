// 1553
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

const ll LOG = 30;

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

struct segment {
	ll n;
	vll t;
	segment() {}
	segment(ll n_) {
		n = n_;
		t.assign(4 * n, 0);
	}
	void update(ll v, ll tl, ll tr, ll pos, ll x) {
		if (tl == tr) {
			t[v] += x;
			return;
		}
		ll tm = (tl + tr) / 2;
		if (pos <= tm) {
			update(2 * v, tl, tm, pos, x);
		} else {
			update(2 * v + 1, tm + 1, tr, pos, x);
		}
		t[v] = max(t[2 * v], t[2 * v + 1]);
	}
	ll get(ll v, ll tl, ll tr, ll l, ll r) {
		if (l > r) {
			return 0;
		}
		if (tl == l && tr == r) {
			return t[v];
		}
		ll tm = (tl + tr) / 2;
		ll v1 = get(2 * v, tl, tm, l, min(r, tm));
		ll v2 = get(2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
		return max(v1, v2);
	}
};

ll n, q;
graph g;
vll sub, tin, tout;
vector<pll> id, prv;
vector<vll> paths, up;
vector<segment> segs;
ll timer = 0;

void binlift(ll v, ll p) {
	up[v][0] = p;
	tin[v] = timer++;
	for (ll i = 1; i < LOG; i++) {
		up[v][i] = up[up[v][i - 1]][i - 1];
	}
	for (ll u : g.adj[v]) {
		if (u == p) {
			continue;
		}
		binlift(u, v);
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

void subtree(ll v, ll p) {
	sub[v] = 1;
	for (ll u : g.adj[v]) {
		if (u == p) {
			continue;
		}
		subtree(u, v);
		sub[v] += sub[u];
	}
}

void build(ll v, ll p, ll ind) {
	paths[ind].pb(v);
	id[v] = { ind, sz(paths[ind]) - 1 };
	for (ll u : g.adj[v]) {
		if (u == p) {
			continue;
		}
		if (sub[u] > sub[v] / 2) {
			build(u, v, ind);
		} else {
			paths.pb({});
			prv.pb(id[v]);
			build(u, v, sz(paths) - 1);
		}
	}
}

void init() {
	for (vll& a : paths) {
		segs.pb(segment(sz(a)));
	}
}

ll hld(ll a, ll b) {
	ll c = lca(a, b);
	ll ap, an, bp, bn, cp, cn;
	tie(ap, an) = id[a], tie(bp, bn) = id[b], tie(cp, cn) = id[c];
	ll ans = 0;
	segment* s = nullptr;
	
	while (ap != cp) {
		s = &segs[ap];
		maxeq(ans, s->get(1, 0, s->n - 1, 0, an));
		tie(ap, an) = prv[ap];
	}
	s = &segs[cp];
	maxeq(ans, s->get(1, 0, s->n - 1, cn, an));
	
	while (bp != cp) {
		s = &segs[bp];
		maxeq(ans, s->get(1, 0, s->n - 1, 0, bn));
		tie(bp, bn) = prv[bp];
	}
	s = &segs[cp];
	maxeq(ans, s->get(1, 0, s->n - 1, cn, bn));
	
	return ans;
}

inline void solve() {
	up.assign(n, vll(LOG));
	tin.resize(n);
	tout.resize(n);
	binlift(0, 0);
	
	sub.resize(n);
	subtree(0, -1);
	
	paths.pb({});
	prv.pb({ -1, -1 });
	id.resize(n);
	build(0, -1, 0);
	init();

	cin >> q;
	for (ll i = 0; i < q; i++) {
		char op;
		ll v, u;
		cin >> op >> v >> u;
		if (op == 'I') {
			--v;
			segment* s = &segs[id[v].ft];
			ll ind = id[v].sd;
			s->update(1, 0, s->n - 1, ind, u);
		} else if (op == 'G') {
			--v, --u;
			ll ans = hld(v, u);
			cout << ans << endl;
		}
	}
}

inline void read() {
	cin >> n;
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
