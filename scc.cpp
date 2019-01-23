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

struct graph {
	ll n;
	vector<vll> adj, radj;
	graph() {}
	graph(ll n_) {
		n = n_;
		adj.resize(n);
		radj.resize(n);
	}
	void add(ll v, ll u) {
		adj[v].pb(u);
		radj[u].pb(v);
	}
};

const ll R = 1e9 + 7;

ll n, m;
vll a;
graph g;
vll order;
vll used;
vector<vll> comp;

void tsort(ll v) {
	used[v] = 1;
	for (ll u : g.adj[v]) {
		if (used[u]) {
			continue;
		}
		tsort(u);
	}
	order.pb(v);
}
void revdfs(ll v) {
	comp.back().pb(v);
	used[v] = 1;
	for (ll u : g.radj[v]) {
		if (used[u]) {
			continue;
		}
		revdfs(u);
	}
}

void scc() {
	used.assign(n, 0);
	for (ll i = 0; i < n; i++) {
		if (!used[i]) {
			tsort(i);
		}
	}
	reverse(all(order));
	used.assign(n, 0);
	for (ll i : order) {
		if (!used[i]) {
			comp.pb({});
			revdfs(i);
		}
	}
}

inline void solve() {
	scc();
	ll ans = 0;
	ll tot = 1;
	for (vll& c : comp) {
		ll minn = inf;
		for (ll v : c) {
			mineq(minn, a[v]);
		}
		ll cnt = 0;
		for (ll v : c) {
			if (a[v] == minn) {
				++cnt;
			}
		}
		ans += minn;
		tot *= cnt;
		tot %= R;
	}
	cout << ans << " " << tot << endl;
}

inline void read() {
	cin >> n;
	g = graph(n);
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	cin >> m;
	for (ll i = 0; i < m; i++) {
		ll v, u;
		cin >> v >> u;
		--v, --u;
		g.add(v, u);
	}
}
