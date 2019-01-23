// 1027 f
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

ll n, mark = 0;
vll a, b, cd;
graph g;
vll used, mt;

inline void reduce() {
	vll v;
	for (ll i = 0; i < n; i++) {
		v.pb(a[i]);
		v.pb(b[i]);
	}
	unique(all(v));
	sort(all(v));
	for (ll p : v) {
		cd.pb(p);
	}
	for (ll i = 0; i < n; i++) {
		a[i] = lower_bound(all(v), a[i]) - v.begin();
		b[i] = lower_bound(all(v), b[i]) - v.begin();
	}
}

inline void build() {
	g = graph(4 * n);
	for (ll i = 0; i < n; i++) {
		g.insert(a[i], sz(cd) + i);
		g.insert(b[i], sz(cd) + i);
	}
}

inline bool kuhn(ll v) {
	if (used[v] == mark) {
		return 0;
	}
	used[v] = mark;
	for (ll u : g.adj[v]) {
		if (mt[u] == -1) {
			mt[u] = v, mt[v] = u;
			return 1;
		}
	}
	for (ll u : g.adj[v]) {
		if (kuhn(mt[u])) {
			mt[u] = v, mt[v] = u;
			return 1;
		}
	}
	return 0;
}

inline void solve() {
	build();
	++mark;
	used.assign(g.n, 0), mt.assign(g.n, -1);
	ll ans = 0;
	ll last = -1;
	for (ll v = 0; v < sz(cd); v++) {
		if (ans >= n) {
			break;
		}
		for (ll u : g.adj[v]) {
			if (mt[u] == -1) {
				continue;
			}
			mt[u] = v;
			mt[v] = u;
			++ans;
			if (ans >= n) {
				last = v;
			}
			break;
		}
	}
	for (ll i = 0; i < sz(cd); i++) {
		if (ans >= n) {
			break;
		}
		if (kuhn(i)) {
			++mark;
			++ans;
			if (ans == n) {
				last = cd[i];
				break;
			}
		}
	}
	cout << last << endl;
}

inline void read() {
	cin >> n;
	a.resize(n), b.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i] >> b[i];
	}
	reduce();
}

int main() {
	fast;
	read();
	solve();
	return 0;
}
