// 1080 f
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

struct vertex {
	ll minn = inf;
	ll l = -1, r = -1;
};
struct segment {
	ll n;
	vll rs;
	vector<vertex> t;
	segment() {}
	segment(ll n_) {
		n = n_;
		rs.pb(newv());
		build(rs[0], 0, n - 1);
	}
	inline ll newv() {
		return t.pb({}), sz(t) - 1;
	}
	ll build(ll v, ll tl, ll tr) {
		if (v == -1) {
			v = newv();
		}
		if (tl == tr) {
			t[v].minn = inf;
			return v;
		}
		ll tm = (tl + tr) / 2;
		t[v].l = build(t[v].l, tl, tm);
		t[v].r = build(t[v].r, tm + 1, tr);
		return v;
	}
	ll upd(ll v, ll tl, ll tr, ll pos, ll x) {
		if (v == -1) {
			v = newv();
		}
		if (tl == tr) {
			ll i = newv();
			t[i] = t[v];
			mineq(t[i].minn, x);
			return i;
		}
		ll tm = (tl + tr) / 2;
		ll i = newv();
		t[i] = t[v];
		if (pos <= tm) {
			t[i].l = upd(t[v].l, tl, tm, pos, x);
		} else {
			t[i].r = upd(t[v].r, tm + 1, tr, pos, x);
		}
		ll maxx = -inf;
		if (t[i].l != -1) {
			maxeq(maxx, t[t[i].l].minn);
		}
		if (t[i].r != -1) {
			maxeq(maxx, t[t[i].r].minn);
		}
		t[i].minn = maxx;
		return i;
	}
	ll get(ll v, ll tl, ll tr, ll l, ll r) {
		if (tl > r || tr < l) {
			return -inf;
		}
		if (v == -1) {
			return inf;
		}
		if (l <= tl && tr <= r) {
			return t[v].minn;
		}
		ll tm = (tl + tr) / 2;
		ll v1 = get(t[v].l, tl, tm, l, r);
		ll v2 = get(t[v].r, tm + 1, tr, l, r);
		return max(v1, v2);
	}
};

struct node {
	ll l, r, p;
	bool operator < (node n) {
		return l < n.l;
	}
};

ll n, m, k;
vector<node> a;
segment st;

inline void solve() {
	sort(all(a));
	st = segment(n);
	vll pos(k, -1);
	for (ll i = k - 1; i >= 0; i--) {
		ll r = st.upd(st.rs.back(), 0, n - 1, a[i].p, a[i].r);
		st.rs.pb(r);
		pos[i] = r;
	}
	for (ll i = 0; i < m; i++) {
		ll A, B, x, y;
		cin >> A >> B >> x >> y;
		--A, --B;
		node no;
		no.l = x;
		no.r = -inf;
		no.p = -inf;
		ll j = lower_bound(all(a), no) - a.begin();
		if (j == k) {
			cout << "no" << endl << flush;
			continue;
		}
		ll ans = st.get(pos[j], 0, n - 1, A, B);
		if (ans > y) {
			cout << "no" << endl << flush;
		} else {
			cout << "yes" << endl << flush;
		}
	}
}

inline void read() {
	cin >> n >> m >> k;
	a.resize(k);
	for (ll i = 0; i < k; i++) {
		cin >> a[i].l >> a[i].r >> a[i].p;
		--a[i].p;
	}
}
