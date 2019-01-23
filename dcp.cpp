// 817 f
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
#define y1 y_1
using namespace std;
typedef int ll;
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

int main() {
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

struct dsu {
	ll n;
	vector<pll> t;
	vll rk;
	vector<pair<ll&, ll>> st;
	ll ok = 1;
	dsu() {}
	dsu(ll n_) {
		n = n_;
		t.resize(n);
		for (ll i = 0; i < n; i++) {
			t[i] = { i, 0 };
		}
		rk.assign(n, 0);
	}
	pll find(ll v) { // You should also use path euristic
		if (t[v].ft == v) {
			return t[v];
		}
		pll ans = find(t[v].ft);
	    st.pb({t[v].ft, t[v].ft});
	    st.pb({t[v].sd, t[v].sd});
	    t[v].ft = ans.ft;
	    t[v].sd = ans.sd ^ t[v].sd;
		return t[v];
	}
	ll join(ll v, ll u) {
		if (!ok) {
			return 0;
		}
		pll V = find(v), U = find(u);
		if (V.ft == U.ft) {
			if (V.sd == U.sd) {
				st.pb({ ok, ok });
				ok = 0;
			}
			return 0;
		}
		ll d1 = V.sd, d2 = U.sd;
		v = V.ft, u = U.ft;
		if (rk[v] > rk[u]) {
			swap(v, u);
		}
		st.pb({ t[u].ft, t[u].ft });
		t[u].ft = v;
		st.pb({ t[u].sd, t[u].sd });
		t[u].sd = d1 ^ d2 ^ 1;
		if (rk[v] == rk[u]) {
			st.pb({ rk[v], rk[v] });
			++rk[v];
		}
		return 1;
	}
	void restore(ll h) {
		while (sz(st) > h) {
			st.back().ft = st.back().sd;
			st.popb();
		}
	}
};
struct edge {
	ll l, r;
	pll p;
};

ll n, q;
dsu d;
vector<edge> es;
map<pll, ll> ms;
vll used;

void solve(ll l, ll r, ll dep = 0) {
	if (l == r) {
		cout << (d.ok ? "YES" : "NO") << endl;
		return;
	}
	ll h = sz(d.st);
	ll m = (l + r) / 2;
	for (ll i = m; i <= r; i++) {
		edge e = es[i];
		if (e.l <= l && m <= e.r) {
			d.join(e.p.ft, e.p.sd);
		}
	}
	solve(l, m, dep + 1);
	d.restore(h);
	for (ll i = l; i <= m + 1; i++) {
		edge e = es[i];
		if (e.l <= m + 1 && r <= e.r) {
			d.join(e.p.ft, e.p.sd);
		}
	}
	solve(m + 1, r, dep + 1);
	d.restore(h);
}

inline void solve() {
	d = dsu(n);
	used.assign(sz(es), 0);
	solve(0, q - 1);
}

inline void read() {
	cin >> n >> q;
	es.resize(q);
	for (ll i = 0; i < q; i++) {
		ll x, y;
		cin >> x >> y;
		--x, --y;
		if (x > y) {
			swap(x, y);
		}
		if (ms.count({ x, y })) {
			es[ms[{x, y}]] = { ms[{x, y}], i - 1, { x, y } };
			es[i] = es[ms[{x, y}]];
			ms.erase({ x, y });
		} else {
			ms[{x, y}] = i;
		}
	}
	for (auto p : ms) {
		es[p.sd] = { p.sd, q, p.ft };
	}
}
