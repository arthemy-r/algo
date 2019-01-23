// 1080 e
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

const ll P = 31;
const ll R = 1e7 + 7;
const ll MAXS = 26;

ll n, m;
vector<vll> a;
ll ans = 0;
vector<vll> cnt;
vll equ;

ll good(vll& c) {
	ll cnt = 0;
	for (ll i = 0; i < MAXS; i++) {
		cnt += c[i] % 2 == 1;
	}
	return cnt <= 1;
}

ll manacher(vll& a) {
	ll n = sz(a);
	ll l = -1, r = -1;
	ll ans = 0;
	vll d1(n, 0), d2(n, 0);
	for (ll i = 0; i < n; i++) {
		ll k = 1;
		if (i <= r) {
			ll j = l + r - i;
			k = min(d1[j], r - i);
		}
		while (i - k >= 0 && i + k < n && a[i - k] == a[i + k]) {
			++k;
		}
		d1[i] = k;
		if (i + k - 1 > r) {
			l = i - k + 1;
			r = i + k - 1;
		}
	}
	l = -1, r = -1;
	for (ll i = 0; i < n; i++) {
		ll k = 0;
		if (i <= r) {
			ll j = l + r - i + 1;
			k = min(d2[j], r - i + 1);
		}
		while (i - k - 1 >= 0 && i + k < n && a[i - k - 1] == a[i + k]) {
			++k;
		}
		d2[i] = k;
		if (i + k - 1 > r) {
			l = i - k;
			r = i + k - 1;
		}
	}
	for (ll i = 0; i < n; i++) {
		ans += d1[i] + d2[i];
	}
	return ans;
}

ll get(ll j1, ll j2) {
	vector<vll> gs;
	gs.pb({});
	for (ll i = 0; i < n; i++) {
		if (!good(cnt[i])) {
			gs.pb({});
			continue;
		}
		gs.back().pb(equ[i]);
	}
	ll ans = 0;
	for (vll& v : gs) {
		if (v.empty()) {
			continue;
		}
		ans += manacher(v);
	}
	return ans;
}

inline void solve() {
	ll ans = 0;
	vll ps(MAXS);
	ps[0] = 1;
	for (ll i = 1; i < MAXS; i++) {
		ps[i] = ps[i - 1] * P % R;
	}
	for (ll j1 = 0; j1 < m; j1++) {
		cnt.assign(n, vll(MAXS, 0));
		equ.assign(n, 0);
		for (ll j2 = j1; j2 < m; j2++) {
			for (ll i = 0; i < n; i++) {
				++cnt[i][a[i][j2]];
				equ[i] += cnt[i][a[i][j2]] * ps[a[i][j2]] % R;
				equ[i] %= R;
			}
			ans += get(j1, j2);
		}
	}
	cout << ans << endl;
}

inline void read() {
	cin >> n >> m;
	a.resize(n, vll(m, 0));
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < m; j++) {
			char c;
			cin >> c;
			a[i][j] = c - 'a';
		}
	}
}
