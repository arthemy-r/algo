// 1054 f
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
#define y0 y_0
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
	vector<vll> adj;
	graph() {}
	graph(ll n_) {
		n = n_;
		adj.resize(n);
	}
	void add(ll v, ll u) {
		adj[v].pb(u);
		adj[u].pb(v);
	}
};
struct segment {
	ll x0, y0, x1, y1;
	ll left = 0;
};

ll n;
vector<pll> a;
vll coord;
ll MAXC = 1e9;
vector<vll> xs, ys;
vector<segment> vs;
graph g;
vll used, mt;
ll mark = 0;
vector<vll> dx, dy;
vector<segment> hor, vert;

bool inter(segment s1, segment s2) {
	if (s1.left == s2.left) {
		return 0;
	}
	if (s2.y0 == s2.y1) {
		swap(s1, s2);
	}
	ll x = s2.x0, y = s1.y0;
	if (!(s1.x0 <= x && x <= s1.x1 && s2.y0 <= y && y <= s2.y1)) {
		return 0;
	}
	if (x != s1.x0 && x != s1.x1 || y != s2.y0 && y != s2.y1) {
		return 1;
	}
	return 0;
}
void reduce() {
	for (ll i = 0; i < n; i++) {
		coord.pb(a[i].ft);
		coord.pb(a[i].sd);
	}
	sort(all(coord));
	coord.resize(unique(all(coord)) - coord.begin());
	for (ll i = 0; i < n; i++) {
		a[i].ft = lower_bound(all(coord), a[i].ft) - coord.begin();
		a[i].sd = lower_bound(all(coord), a[i].sd) - coord.begin();
	}
	MAXC = sz(coord);
}
void build() {
	xs.resize(MAXC), ys.resize(MAXC);
	for (ll i = 0; i < n; i++) {
		ys[a[i].ft].pb(a[i].sd);
		xs[a[i].sd].pb(a[i].ft);
	}
	for (ll x = 0; x < MAXC; x++) {
		sort(all(ys[x]));
		for (ll y = 1; y < sz(ys[x]); y++) {
			vs.pb({ x, ys[x][y - 1], x, ys[x][y], 1 });
		}
	}
	for (ll y = 0; y < MAXC; y++) {
		sort(all(xs[y]));
		for (ll x = 1; x < sz(xs[y]); x++) {
			vs.pb({ xs[y][x - 1], y, xs[y][x], y, 0 });
		}
	}
	g = graph(sz(vs));
	for (ll i = 0; i < g.n; i++) {
		for (ll j = i + 1; j < g.n; j++) {
			if (inter(vs[i], vs[j])) {
				g.add(i, j);
			}
		}
	}
}
ll kuhn(ll v) {
	if (used[v] == mark) {
		return 0;
	}
	used[v] = mark;
	for (ll u : g.adj[v]) {
		if (mt[u] == -1) {
			mt[v] = u;
			mt[u] = v;
			return 1;
		}
	}
	for (ll u : g.adj[v]) {
		if (kuhn(mt[u])) {
			mt[v] = u;
			mt[u] = v;
			return 1;
		}
	}
	return 0;
}
void matching() {
	used.assign(g.n, 0);
	mt.assign(g.n, -1);
	++mark;
	for (ll v = 0; v < g.n; v++) {
		if (vs[v].left) {
			if (kuhn(v)) {
				used.assign(g.n, 0);
			}
		}
	}
}
void dfs(ll v) {
	used[v] = 1;
	for (ll u : g.adj[v]) {
		if (used[u]) {
			continue;
		}
		if (vs[v].left && mt[v] == u) {
			continue;
		}
		if (!vs[v].left && mt[v] != u) {
			continue;
		}
		dfs(u);
	}
}
void min_vc() {
	used.assign(g.n, 0);
	for (ll i = 0; i < g.n; i++) {
		if (vs[i].left && mt[i] == -1) {
			if (!used[i]) {
				dfs(i);
			}
		}
	}
	for (ll i = 0; i < g.n; i++) {
		if (vs[i].left && !used[i]) {
			dy[vs[i].x0].pb(vs[i].y0);
			dy[vs[i].x0].pb(vs[i].y1);
		} else if (!vs[i].left && used[i]) {
			dx[vs[i].y0].pb(vs[i].x0);
			dx[vs[i].y0].pb(vs[i].x1);
		}
	}
}

inline void solve() {
	reduce();
	build();
	matching();
	dx.resize(MAXC);
	dy.resize(MAXC);
	for (ll x = 0; x < MAXC; x++) {
		if (sz(ys[x])) {
			dy[x].pb(ys[x][0]);
		}
	}
	for (ll y = 0; y < MAXC; y++) {
		if (sz(xs[y])) {
			dx[y].pb(xs[y][0]);
		}
	}
	min_vc();
	for (ll x = 0; x < MAXC; x++) {
		if (sz(ys[x])) {
			dy[x].pb(ys[x].back());
		}
	}
	for (ll y = 0; y < MAXC; y++) {
		if (sz(xs[y])) {
			dx[y].pb(xs[y].back());
		}
	}
	for (ll y = 0; y < MAXC; y++) {
		for (ll x = 0; x < sz(dx[y]) - 1; x += 2) {
			hor.pb({ dx[y][x], y, dx[y][x + 1], y });
		}
	}
	for (ll x = 0; x < MAXC; x++) {
		for (ll y = 0; y < sz(dy[x]) - 1; y += 2) {
			vert.pb({ x, dy[x][y], x, dy[x][y + 1] });
		}
	}
	cout << sz(hor) << endl;
	for (segment s : hor) {
		cout << coord[s.x0] << " " << coord[s.y0] << " " << coord[s.x1] << " " << coord[s.y1] << endl;
	}
	cout << sz(vert) << endl;
	for (segment s : vert) {
		cout << coord[s.x0] << " " << coord[s.y0] << " " << coord[s.x1] << " " << coord[s.y1] << endl;
	}
}

inline void read() {
	cin >> n;
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i].ft >> a[i].sd;
	}
}
