// 420 d
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast", "unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
#define pb push_back
#define pf push_front
#define popb pop_back
#define pop_front popf
#define sz(a) ll(a.size())
#define all(a) (a).begin(), (a).end()
#define die(cond) if (cond) for (;;) {}
#define ft first
#define sd second
#define hash_set unordered_set
#define hash_map unordered_map
#define heap priority_queue
#define mineq(a, b) (a)=((a)<(b))?(a):(b)
#define maxeq(a, b) (a)=((a)>(b))?(a):(b)
#define fast ios_base::sync_with_stdio(0), cout.tie(0), cin.tie(0)
#define endl "\n"
#define y1 y_1
using namespace std;
typedef int ll;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<ll> vll;
typedef set<ll> sll;
typedef map<ll, ll> mll;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
const ll inf = numeric_limits<ll>::infinity();
const ld pi = acos(-1);
const ld eps = 1e-9;

inline void solve(), read();

int main() {
	fast;
	read();
	solve();
	return 0;
}

struct vertex {
	ll val = -1, prior = rand()*rand();
	ll l = -1, r = -1;
	ll sz = 1;
};

struct treap {
	vector<vertex> t;
	treap() {}
	inline ll newv(vertex v) {
		return t.pb(v), sz(t) - 1;
	}
	inline ll getsz(ll v) {
		if (v == -1) {
			return 0;
		}
		return t[v].sz;
	}
	inline void upd(ll v) {
		if (v == -1) {
			return;
		}
		t[v].sz = getsz(t[v].l) + getsz(t[v].r) + 1;
	}
	inline pll split(ll v, ll k) {
		if (v == -1) {
			return { -1, -1 };
		}
		ll l = getsz(t[v].l);
		pll p;
		if (l < k) {
			p = split(t[v].r, k - l - 1);
			t[v].r = p.ft;
			p.ft = v;
		} else {
			p = split(t[v].l, k);
			t[v].l = p.sd;
			p.sd = v;
		}
		upd(v);
		return p;
	}
	inline ll merge(ll f, ll s) {
		if (f == -1) {
			return s;
		}
		if (s == -1) {
			return f;
		}
		if (t[f].prior > t[s].prior) {
			t[f].r = merge(t[f].r, s);
			upd(f);
			return f;
		} else {
			t[s].l = merge(f, t[s].l);
			upd(s);
			return s;
		}
	}
	inline ll push_back(ll root, ll val) {
		vertex v; v.val = val;
		root = merge(root, newv(v));
		return root;
	}
	inline ll add(ll root, ll ind, ll v) {
		ll a, b, c;
		tie(a, b) = split(root, ind);
		tie(b, c) = split(b, 0);
		upd(v);
		root = merge(merge(a, v), c);
		return root;
	}
	inline ll del(ll root, ll ind, ll& v) {
		ll a, b, c;
		tie(a, b) = split(root, ind);
		tie(b, c) = split(b, 1);
		v = b;
		root = merge(a, c);
		return root;
	}
	inline ll move(ll root, ll from, ll to, ll val) {
		ll v = 0;
		root = del(root, from, v);
		if (t[v].val != -1 && t[v].val != val) {
			cout << -1 << endl;
			exit(0);
		}
		t[v].val = val;
		root = add(root, to, v);
		return root;
	}
	inline void trav(ll v, vll& ans) {
		if (v == -1) {
			return;
		}
		trav(t[v].l, ans);
		ans.pb(t[v].val);
		trav(t[v].r, ans);
	}
};

const ll MAXN = 1e6 + 10;
ll n, m;
treap tr;
ll root = -1;
vll vs, pos;
bool used[MAXN];

inline void solve() {
	for (ll i = 0; i < n; i++) {
		root = tr.pb(root, -1);
	}
	for (ll i = m - 1; i >= 0; i--) {
		root = tr.move(root, 0, pos[i], vs[i]);
	}
	vll ans;
	tr.trav(root, ans);
	ll j = 1;
	for (ll i = 0; i < sz(ans); i++) {
		if (ans[i] == -1) {
			while (j <= n && used[j]) {
				++j;
			}
			if (j > n) {
				cout << -1 << endl;
				return;
			}
			ans[i] = j;
			used[j] = 1;
			++j;
		}
	}
	while (j <= n && used[j]) {
		++j;
	}
	if (j <= n) {
		cout << -1 << endl;
		return;
	}
	for (ll x : ans) {
		cout << x << " ";
	}
}

inline void read() {
	cin >> n >> m;
	vs.resize(m), pos.resize(m);
	for (ll i = 0; i < m; i++) {
		cin >> vs[i] >> pos[i];
		used[vs[i]] = 1;
		--pos[i];
	}
}
