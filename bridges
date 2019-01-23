// 1000 e
#pragma GCC optimize ("O3", "unroll-loops")
#include <bits/stdc++.h>
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define all(a) (a).begin(), (a).end()
#define heap priority_queue
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vector<ll> vll;
const ll inf = numeric_limits<ll>::max() / 2;
const ld eps = 1e-9;
const ld pi = acos(-1);

struct graph {
	ll vn;
	vector<set<ll>> es;
	graph() {}
	graph(ll v) {
		vn = v;
		es.resize(vn + 1);
	}
	void insert(ll v, ll u) {
		es[v].insert(u);
		es[u].insert(v);
	}
	void erase(ll v, ll u) {
		es[v].erase(u);
		es[u].erase(v);
	}
};

ll N, M;
graph g, h;

vll fup, d;
vector<bool> used;
vector<pll> bs;
void brs(ll v, ll p) {
	used[v] = true;
	d[v] = d[p] + 1;
	fup[v] = d[v];
	for (ll u : g.es[v]) {
		if (u == p) {
			continue;
		}
		if (used[u]) {
			fup[v] = min(fup[v], d[u]);
		} else {
			brs(u, v);
			fup[v] = min(fup[v], fup[u]);
			if (fup[u] > d[v]) {
				bs.pb({ u, v });
			}
		}
	}
}

vll color;
void coloring(ll v, ll c) {
	used[v] = true;
	color[v] = c;
	for (ll u : g.es[v]) {
		if (used[u]) {
			continue;
		}
		coloring(u, c);
	}
}

ll dep = -1, leaf = -1;
void dfs(ll v, ll p, ll d = 0) {
	for (ll u : h.es[v]) {
		if (u == p) {
			continue;
		}
		dfs(u, v, d + 1);
	}
	if (d > dep) {
		dep = d;
		leaf = v;
	}
}

ll dfs2(ll v, ll p, ll b) {
	for (ll u : h.es[v]) {
		if (u == p) {
			continue;
		}
		ll d = dfs2(u, v, b);
		if (d) {
			return d + 1;
		}
	}
	if (v == b) {
		return 1;
	}
	return 0;
}

void solve() {
	used.assign(g.vn + 1, 0);
	fup.assign(g.vn + 1, -1);
	d.assign(g.vn + 1, 0);
	for (ll i = 1; i <= g.vn; i++) {
		if (!used[i]) {
			brs(i, i);
		}
	}
	for (pll p : bs) {
		g.erase(p.first, p.second);
	}
	color.assign(g.vn + 1, 0);
	used.assign(g.vn + 1, 0);
	ll c = 0;
	for (ll i = 1; i <= g.vn; i++) {
		if (!used[i]) {
			coloring(i, c);
			++c;
		}
	}
	h = graph(c);
	for (pll p : bs) {
		if (color[p.first] != color[p.second]) {
			h.insert(color[p.first], color[p.second]);
		}
	}
	dfs(0, -1);
	ll l = leaf;
	dep = -1, leaf = -1;
	dfs(l, -1);
	ll ans = dfs2(l, -1, leaf) - 1;
	cout << ans;
}

int main() {
	fast;
	cin >> N >> M;
	g = graph(N);
	for (ll i = 0; i < M; i++) {
		ll v, u;
		cin >> v >> u;
		g.insert(v, u);
	}
	solve();
	return 0;
}
