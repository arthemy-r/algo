#pragma GCC optimize ("O3", "unroll-loops")
#include <bits/stdc++.h>
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

const ll LOG = 23;
const ll MAXN = 1e5 + 10;

struct edge {
	ll u, i;
	edge() {}
	edge(ll u, ll i): u(u), i(i) {}
};

struct graph {
	ll vn;
	vector<edge> es[MAXN];
	graph() {}
	graph(ll v) {
		vn = v;
	}
	void insert(ll v, ll u, ll i) {
		es[v].pb({ u, i });
		es[u].pb({ v, i });
	}
};

ll N, K;
graph g;

ll lift[MAXN][LOG];
ll tin[MAXN], tout[MAXN];
ll timer = 0;
void bin_lift(ll v, ll p) {
	tin[v] = timer++;
	lift[v][0] = p;
	for (ll i = 1; i < LOG; i++) {
		lift[v][i] = lift[lift[v][i - 1]][i - 1];
	}
	for (edge e : g.es[v]) {
		if (e.u == p) {
			continue;
		}
		bin_lift(e.u, v);
	}
	tout[v] = timer++;
}

inline bool upper(ll a, ll b) {
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
		if (!upper(lift[a][i], b)) {
			a = lift[a][i];
		}
	}
	return lift[a][0];
}

ll add[MAXN];
ll ans[MAXN];

ll dfs(ll v, ll p) {
	ll res = add[v];
	for (edge e : g.es[v]) {
		if (e.u == p) {
			continue;
		}
		ll cur = dfs(e.u, v);
		ans[e.i] = cur;
		res += cur;
	}
	return res;
}

void solve() {
	bin_lift(1, 1);
	cin >> K;
	for (ll i = 0; i < K; i++) {
		ll a, b;
		cin >> a >> b;
		ll l = lca(a, b);
		add[l] -= 2;
		++add[a], ++add[b];
	}
	dfs(1, 1);
	for (ll i = 0; i < N - 1; i++) {
		cout << ans[i] << " ";
	}
}

int main() {
	fast;
	cin >> N;
	g = graph(N);
	for (ll i = 0; i < N - 1; i++) {
		ll v, u;
		cin >> v >> u;
		g.insert(v, u, i);
	}
	solve();
	return 0;
}
