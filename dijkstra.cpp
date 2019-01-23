// 20 c
#pragma GCC optimize ("O3", "unroll-loops")
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

struct edge {
	ll u, w;
	edge() {}
	edge(ll u, ll w) : u(u), w(w) {}
};

struct graph {
	ll vn;
	vector<vector<edge>> es;
	graph() {}
	graph(ll v) {
		vn = v;
		es.resize(vn + 1);
	}
	void insert(ll v, ll u, ll w) {
		es[v].pb({ u, w });
		es[u].pb({ v, w });
	}
};

graph g;

vll d;
heap<pll> q;
vll path;
void dijkstra(ll s, ll t) {
	d.assign(g.vn + 1, inf);
	path.assign(g.vn + 1, -1);
	d[s] = 0;
	q.push({ 0, s });
	while (!q.empty()) {
		ll v, w;
		tie(w, v) = q.top();
		q.pop();
		if (-w != d[v]) {
			continue;
		}
		for (edge e : g.es[v]) {
			ll w = e.w, u = e.u;
			if (d[u] > d[v] + w) {
				d[u] = d[v] + w;
				path[u] = v;
				q.push({ -d[u], u });
			}
		}
	}
	if (d[t] == inf) {
		cout << -1 << endl;
		return;
	}
	vll way;
	for (ll p = t; p != -1; p = path[p]) {
		way.pb(p);
	}
	reverse(all(way));
	for_each(all(way), [](ll el) {cout << el << " "; });
}

int main() {
	fast;
	ll N, M;
	cin >> N >> M;
	g = graph(N);
	for (ll i = 0; i < M; i++) {
		ll v, u, w;
		cin >> v >> u >> w;
		g.insert(v, u, w);
	}
	dijkstra(1, N);
	return 0;
}
//
