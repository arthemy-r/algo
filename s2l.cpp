// 600 e
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
#define die(cond) if (cond) for(;;){}
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vector<ll> vll;
typedef set<ll> sll;
typedef map<ll, ll> mll;
template <typename T> inline istream& operator >> (istream& in, pair<T, T>& v) {
	in >> v.ft >> v.sd; return in;
}
template <typename T> inline ostream& operator <<(ostream& out, pair<T, T> v) {
	out << v.ft << " " << v.sd; return out;
}
template <typename T> inline istream& operator >> (istream& in, vector<T>& v) {
	for (ll i = 0; i < sz(v); i++) in >> v[i]; return in;
}
template <typename T> inline ostream& operator <<(ostream& out, vector<T>& v) {
	for (ll i = 0; i < sz(v); i++) out << v[i] << " "; return out;
}
const ll inf = numeric_limits<ll>::max() / 2;
const ld eps = 1e-9;
const ld pi = acos(-1);

inline void solve(), read();

int main() {
	fast;
	read();
	solve();
	return 0;
}

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

struct node {
	mll s;
	ll ans;
	ll max;
};

ll n;
graph g;
vll c, ans;
vector<node> s2l;

ll merge(ll i, ll j) {
	if (sz(s2l[i].s) < sz(s2l[j].s)) {
		swap(i, j);
	}
	for (pll p : s2l[j].s) {
		s2l[i].s[p.ft] += p.sd;
		ll v = s2l[i].s[p.ft];
		if (v > s2l[i].max) {
			s2l[i].max = v;
			s2l[i].ans = p.ft;
		} else if (v == s2l[i].max) {
			s2l[i].ans += p.ft;
		}
	}
	return i;
}

ll dfs(ll v, ll p) {
	ll i = v;
	s2l[i].ans = c[v];
	s2l[i].max = 1;
	s2l[i].s[c[v]] = 1;
	for (ll u : g.adj[v]) {
		if (u == p) {
			continue;
		}
		ll j = dfs(u, v);
		i = merge(i, j);
	}
	ans[v] = s2l[i].ans;
	return i;
}

inline void solve() {
	ans.resize(n);
	s2l.resize(n);
	dfs(0, 0);
	cout << ans << endl;
}

inline void read() {
	cin >> n;
	c.resize(n);
	cin >> c;
	g = graph(n);
	for (ll i = 0; i < n - 1; i++) {
		ll v, u;
		cin >> v >> u;
		--v, --u;
		g.insert(v, u);
	}
}
