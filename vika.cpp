// 610 d
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
#define y1 y_1
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

typedef pll seg;

struct fenwick {
	ll n;
	vll t;
	fenwick() {}
	fenwick(ll n_) {
		n = n_;
		t.resize(n);
	}
	inline ll f(ll i) {
		return i & (i + 1);
	}
	inline ll h(ll i) {
		return i | (i + 1);
	}
	void inc(ll ind, ll x) {
		for (ll i = ind; i < n; i = h(i)) {
			t[i] += x;
		}
	}
	ll sum(ll ind) {
		ll ans = 0;
		for (ll i = ind; i >= 0; i = f(i) - 1) {
			ans += t[i];
		}
		return ans;
	}
	ll get(ll l, ll r) {
		return sum(r) - sum(l - 1);
	}
};

struct event {
	ll x1, x2;
	ll y;
	ll t;
};

ll n;
map<ll, vector<seg>> mx, my;
vector<event> es;
vll coord;
fenwick f;

void merge(vector<seg>& vec) {
	vector<pll> es;
	for (seg s : vec) {
		es.pb({ s.ft, 0 });
		es.pb({ s.sd, 1 });
	}
	vec.clear();
	sort(all(es));
	ll open = -inf;
	ll cnt = 0;
	for (pll e : es) {
		if (e.sd == 0) {
			if (cnt == 0) {
				open = e.ft;
			}
			++cnt;
		} else {
			--cnt;
			if (cnt == 0) {
				vec.pb({ open, e.ft });
			}
		}
	}
}

bool comp(event i, event j) {
	if (i.y != j.y) {
		return i.y < j.y;
	}
	return i.t < j.t;
}

void prepare() {
	for (auto& p : mx) {
		merge(p.sd);
		for (seg s : p.sd) {
			ll x = p.ft, y1 = s.ft, y2 = s.sd;
			event e1; e1.x1 = x, e1.x2 = x, e1.y = y1, e1.t = 0;
			event e2; e2.x1 = x, e2.x2 = x, e2.y = y2, e2.t = 2;
			es.pb(e1), es.pb(e2);
			coord.pb(x);
		}
	}
	for (auto& p : my) {
		merge(p.sd);
		for (seg s : p.sd) {
			ll y = p.ft, x1 = s.ft, x2 = s.sd;
			event e1; e1.x1 = x1, e1.x2 = x2, e1.y = y, e1.t = 1;
			es.pb(e1);
			coord.pb(x1), coord.pb(x2);
		}
	}
	sort(all(coord));
	coord.resize(unique(all(coord)) - coord.begin());
	for (event& e : es) {
		e.x1 = lower_bound(all(coord), e.x1) - coord.begin();
		e.x2 = lower_bound(all(coord), e.x2) - coord.begin();
	}
	sort(all(es), comp);
}

inline void solve() {
	prepare();
	ll ans = 0;
	for (auto p : mx) {
		for (seg s : p.sd) {
			ans += s.sd - s.ft + 1;
		}
	}
	for (auto p : my) {
		for (seg s : p.sd) {
			ans += s.sd - s.ft + 1;
		}
	}
	f = fenwick(sz(coord));
	for (event e : es) {
		if (e.t == 0) {
			f.inc(e.x1, +1);
		} else if (e.t == 2) {
			f.inc(e.x1, -1);
		} else {
			ans -= f.get(e.x1, e.x2);
		}
	}
	cout << ans << endl;
}

inline void read() {
	cin >> n;
	for (ll i = 0; i < n; i++) {
		ll x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if (x1 == x2) {
			mx[x1].pb({ min(y1, y2), max(y1, y2) });
		} else {
			my[y1].pb({ min(x1, x2), max(x1, x2) });
		}
	}
}
