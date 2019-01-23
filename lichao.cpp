// 319 c
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
const ll inf = numeric_limits<ll>::max();
const ld eps = 1e-9;
const ld pi = acos(-1);

inline void solve(), read();

int main() {
	fast;
	read();
	solve();
	return 0;
}

const ll MAXN = 1e9 + 10;

ll n;
vll a, b;
vll dp;

struct point {
	ll x, y;
};
struct line {
	ll k = 0, b = inf;
};
struct vertex {
	ll l = -1, r = -1;
	line ln;
};

inline ll f(line l, ll x) {
	return l.k * x + l.b;
}

struct lichao {
	ll n;
	vector<vertex> t;
	lichao() {}
	lichao(ll n_) {
		n = n_;
		t.pb({});
	}
	ll newv() {
		return t.pb({}), sz(t) - 1;
	}
	void add(ll v, ll tl, ll tr, line w) {
		ll tm = (tl + tr) / 2;
		ll lf = f(w, tl) < f(t[v].ln, tl);
		ll mf = f(w, tm) < f(t[v].ln, tm);
		if (mf) {
			swap(t[v].ln, w);
		}
		if (tl == tr) {
			return;
		}
		if (lf != mf) {
			if (t[v].l == -1) t[v].l = newv();
			add(t[v].l, tl, tm, w);
		} else {
			if (t[v].r == -1) t[v].r = newv();
			add(t[v].r, tm + 1, tr, w);
		}
	}
	ll get(ll v, ll tl, ll tr, ll x) {
		if (v == -1) {
			return inf;
		}
		if (tl == tr) {
			return f(t[v].ln, x);
		}
		ll tm = (tl + tr) / 2;
		ll v1 = f(t[v].ln, x);
		ll v2 = inf;
		if (x <= tm) {
			v2 = get(t[v].l, tl, tm, x);
		} else {
			v2 = get(t[v].r, tm + 1, tr, x);
		}
		return min(v1, v2);
	}
};

lichao st;

inline void solve() {
	st = lichao(MAXN);
	dp.resize(n);
	dp[0] = 0;
	st.add(0, 0, st.n - 1, { b[0], dp[0] });
	// dp[i] = a[i]*b[j] + dp[j]
	for (ll i = 1; i < n; i++) {
		dp[i] = st.get(0, 0, st.n - 1, a[i]);
		st.add(0, 0, st.n - 1, { b[i], dp[i] });
	}
	cout << dp[n - 1] << endl;
}

inline void read() {
	cin >> n;
	a.resize(n), b.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (ll i = 0; i < n; i++) {
		cin >> b[i];
	}
}
