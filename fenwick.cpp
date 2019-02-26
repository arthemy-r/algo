// 100246 a
// meow-meow
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
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
#define mineq(a, b) (a) = min((a), (b))
#define maxeq(a, b) (a) = max((a), (b))
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

struct segment {
	ll n;
	vll t;
	segment() {}
	segment(ll n_) {
		ll l = log2(n_);
		n = 1 << l;
		t.assign(2 * n, 0);
	}
	void build(vll &a) {
		for (ll i = 0; i < n; i++) {
			upd(i, a[i]);
		}
	}
	void upd(ll v, ll x) {
		v += n;
		t[v] = x;
		v /= 2;
		while (v > 0) {
			t[v] = t[2 * v] + t[2 * v + 1];
			v /= 2;
		}
	}
	ll get(ll v, ll tl, ll tr, ll l, ll r) {
		if (tl > r || tr < l) {
			return 0;
		}
		if (l <= tl && tr <= r) {
			return t[v];
		}
		ll tm = (tl + tr) / 2;
		ll v1 = get(2 * v, tl, tm, l, r);
		ll v2 = get(2 * v + 1, tm + 1, tr, l, r);
		return v1 + v2;
	}
};

struct fenwick {
	ll n;
	vll t;
	fenwick() {}
	fenwick(ll n_) {
		n = n_;
		t.resize(n, 0);
	}
	void build(vll& a) {
		for (ll i = 0; i < n; i++) {
			inc(i, a[i]);
		}
	}
	ll f(ll i) {
		return i & (i + 1);
	}
	ll g(ll i) {
		return i | (i + 1);
	}
	void inc(ll ind, ll d) {
		for (ll i = ind; i < n; i = g(i)) {
			t[i] += d;
		}
	}
	ll sum(ll ind) {
		ll ans = 0;
		for (ll i = ind; i >= 0; i = f(i) - 1) {
			ans += t[i];
		}
		return ans;
	}
};

ll n, k;
vll a;
//segment st;
fenwick f;

inline void solve() {
//	st = segment(n);
	f = fenwick(n);
//	st.build(a);
	f.build(a);
	for (ll i = 0; i < k; i++) {
		ll op;
		cin >> op;
		if (op == 1) {
			ll i, x;
			cin >> i >> x;
			--i;
		//	st.upd(i, x);
			f.inc(i, x - a[i]), a[i] = x;
		} else if (op == 0) {
			ll l, r;
			cin >> l >> r;
			--l, --r;
		//	ll s = st.get(1, 0, st.n - 1, l, r);
			ll s = f.sum(r) - f.sum(l - 1);
			cout << s << endl;
		}
	}
}

inline void read() {
	cin >> n >> k;
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
}

int main() {
	freopen("rsq.in", "r", stdin);
	freopen("rsq.out", "w", stdout);
	fast;
	read();
	solve();
	return 0;
}
