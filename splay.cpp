// 20 c

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
const ld pi = acosl(-1);
template<typename T> inline bool mineq(T& a, T b) { return (a > b) ? (a = b, 1) : 0; }
template<typename T> inline bool maxeq(T& a, T b) { return (a < b) ? (a = b, 1) : 0; }

struct edge {
	ll u;
	ll w;
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
	inline void insert(ll v, ll u, ll w) {
		es[v].pb({ u, w });
		es[u].pb({ v, w });
	}
};
template<typename T>
struct vertex {
	T key;
	ll par = -1;
	T minn;
	ll l = -1, r = -1;
};
template<typename T>
struct splay_tree {
	vector<vertex<T>> t;
	splay_tree() {}
	ll newv(T k) {
		vertex<T> v;
		v.key = k;
		v.minn = v.key;
		t.pb(v);
		upd(sz(t) - 1);
		return sz(t) - 1;
	}
	void setpar(ll v, ll p) {
		if (v == -1) {
			return;
		}
		t[v].par = p;
	}
	void $upd(ll v) {
		if (v == -1) {
			return;
		}
		t[v].minn = t[v].key;
		if (t[v].l != -1) {
			mineq(t[v].minn, t[t[v].l].minn);
		}
		if (t[v].r != -1) {
			mineq(t[v].minn, t[t[v].r].minn);
		}
	}
	void upd(ll v) {
		if (v == -1) {
			return;
		}
		$upd(v);
		setpar(t[v].l, v);
		setpar(t[v].r, v);
	}
	ll rotate(ll v) {
		ll p = t[v].par;
		ll gp = t[p].par;
		if (gp != -1) {
			if (t[gp].l == p) {
				t[gp].l = v;
			} else {
				t[gp].r = v;
			}
		}
		if (t[p].l == v) {
			t[p].l = t[v].r;
			t[v].r = p;
		} else {
			t[p].r = t[v].l;
			t[v].l = p;
		}
		upd(v), upd(p);
		setpar(v, gp);
		return v;
	}
	ll splay(ll v) {
		if (v == -1) {
			return -1;
		}
		if (t[v].par == -1) {
			return v;
		}
		ll p = t[v].par;
		ll gp = t[p].par;
		if (gp == -1) {
			return rotate(v);
		}
		if (t[gp].l == p && t[p].l == v || t[gp].r == p && == t[p].r == v) {
			rotate(p);
			rotate(v);
		} else {
			rotate(v);
			rotate(v);
		}
		return splay(v);
	}
	ll find(ll v, T k) {
		if (v == -1) {
			return -1;
		}
		if (t[v].key == k) {
			return splay(v);
		}
		if (t[v].key > k && t[v].l != -1) {
			return find(t[v].l, k);
		}
		if (t[v].key < k && t[v].r != -1) {
			return find(t[v].r, k);
		}
		return splay(v);
	}
	pll split(ll v, T k) {
		if (v == -1) {
			return { -1, -1 };
		}
		v = find(v, k);
		if (t[v].key < k) {
			ll r = t[v].r;
			setpar(r, -1), t[v].r = -1;
			upd(v);
			return { v, r };
		} else {
			ll l = t[v].l;
			setpar(l, -1), t[v].l = -1;
			upd(v);
			return { l, v };
		}
	}
	ll merge(ll f, ll s) {
		if (f == -1) {
			return s;
		}
		if (s == -1) {
			return f;
		}
		s = find(s, t[f].key);
		t[s].l = f;
		upd(s);
		return s;
	}
	void add(ll& root, T k) {
		ll a, b;
		tie(a, b) = split(root, k);
		ll v = newv(k);
		t[v].l = a, t[v].r = b;
		upd(v);
		root = v;
	}
	void del(ll& root, T k) {
		ll v = find(root, k);
		setpar(t[v].l, -1);
		setpar(t[v].r, -1);
		root = merge(t[v].l, t[v].r);
	}
	T getans(ll& root) {
		return t[root].minn;
	}
};

graph g;

vll d;
splay_tree<pll> q;
vll path;
inline void dijkstra(ll s, ll t) {
	d.assign(g.vn + 1, inf);
	path.assign(g.vn + 1, -1);
	d[s] = 0;
	ll root = -1;
	q.add(root, { 0, s });
	while (root != -1) {
		pll p = q.getans(root);
		ll w = p.ft, v = p.sd;
		q.del(root, p);
		if (w != d[v]) {
			continue;
		}
		for (edge e : g.es[v]) {
			ll w = e.w;
			ll u = e.u;
			if (d[u] > d[v] + w) {
				d[u] = d[v] + w;
				path[u] = v;
				q.add(root, { d[u], u });
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
		ll v, u;
		ll w;
		cin >> v >> u >> w;
		g.insert(v, u, w);
	}
	dijkstra(1, N);
	return 0;
}
