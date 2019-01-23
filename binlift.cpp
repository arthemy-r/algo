// 519 e
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
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
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl "\n"
#define mineq(a, b) (a) = ((a)>(b))?(b):(a)
#define maxeq(a, b) (a) = ((a)<(b))?(b):(a)
#define istrop template <typename T> inline istream& operator >>
#define ostrop template <typename T> inline ostream& operator <<
using namespace std;
typedef int ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vector<ll> vll;
typedef set<ll> sll;
typedef map<ll, ll> mll;
istrop(istream& in, pair<T, T>& v) {
	in >> v.ft >> v.sd; return in;
}
ostrop(ostream& out, pair<T, T> v) {
	out << v.ft << " " << v.sd; return out;
}
istrop(istream& in, vector<T>& v) {
	for (ll i = 0; i < sz(v); i++) in >> v[i]; return in;
}
ostrop(ostream& out, vector<T>& v) {
	for (ll i = 0; i < sz(v); i++) out << v[i] << " "; return out;
}
istrop(istream& in, pair<vector<T>*, vector<T>*> v) {
	for (ll i = 0; i < sz(*v.ft); i++) in >> (*v.ft)[i] >> (*v.sd)[i]; return in;
}
const ll inf = numeric_limits<ll>::max() / 2;
const ld eps = 1e-9;
const ld pi = acos(-1);

const ll LOG = 18;

struct graph {
	ll n;
	vector<vll> adj;
	graph() {}
	graph(ll n_) {
		n = n_;
		adj.resize(n);
	}
	inline void insert(ll v, ll u) {
		adj[v].pb(u);
		adj[u].pb(v);
	}
};

ll n, m, timer = 0;
graph g;
vll d, sub, tin, tout;
vector<vll> up;

inline void dfs(ll v, ll p) {
	up[v][0] = v;
	up[v][1] = p;
	for (ll i = 2; i < LOG; i++) {
		up[v][i] = up[up[v][i - 1]][i - 1];
	}
	d[v] = d[p] + 1;
	sub[v] = 1;
	tin[v] = timer++;
	for (ll u : g.adj[v]) {
		if (u == p) {
			continue;
		}
		dfs(u, v);
		sub[v] += sub[u];
	}
	tout[v] = timer++;
}

inline bool upper(ll a, ll b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

inline ll lca(ll a, ll b) {
	if (upper(a, b)) {
		return a;
	}
	if (upper(b, a)) {
		return b;
	}
	for (ll i = LOG - 1; i >= 1; i--) {
		if (!upper(up[a][i], b)) {
			a = up[a][i];
		}
 	}
	return up[a][1];
}

inline bool checkbit(ll n, ll p) {
	return n & (1ll << p);
}

inline ll get(ll v, ll d) {
	for (ll i = LOG - 1; i >= 1; i--) {
		if (checkbit(d, i - 1)) {
			v = up[v][i];
		}
	}
	return v;
}

inline ll process(ll a, ll b) {
	if (a == b) {
		return n;
	}
	ll c = lca(a, b);
	if (d[a] == d[b]) {
		ll g = get(a, d[a] - d[c] - 1), h = get(b, d[b] - d[c] - 1);
		return n - sub[g] - sub[h];
	}
	ll dist = d[a] - d[c] + d[b] - d[c];
	if (dist % 2 == 1) {
		return 0;
	}
	if (2 * (d[a] - d[c]) < dist) {
		swap(a, b);
	}
	ll d2 = dist >> 1;
	ll g = get(a, d2);
	ll h = get(a, d2 - 1);
	return sub[g] - sub[h];
}

inline void solve() {
	up.assign(n, vll(LOG, 0));
	d.resize(n), sub.resize(n);
	tin.assign(n, 0), tout.assign(n, 0);
	d[0] = -1;
	dfs(0, 0);
	for (ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		--a, --b;
		ll ans = process(a, b);
		cout << ans << endl;
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
	cin >> m;
}

int main() {
	fast;
	read();
	solve();
	return 0;
}
//
