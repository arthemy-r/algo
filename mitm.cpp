// 839 e
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

const ll MAXN = 42;
const ll MAXK = 21;
const ll MAXT = 1ll << MAXK;
ll n;
ld k;
bitset<MAXN> adj[MAXN];
vll L, R;
ll dp[MAXT];

inline bool checkbit(ll n, ll p) {
	return n & (1ll << p);
}

void lft() {
	for (ll m = 0; m < (1ll << sz(L)); m++) {
		ll ans = 0;
		vll a;
		for (ll i = 0; i < n; i++) {
			if (checkbit(m, i)) {
				ll cur = dp[m - (1ll << i)];
				maxeq(ans, cur);
				a.pb(L[i]);
			}
		}
		bitset<MAXN> bs;
		bitset<MAXN> unite = 1;
		bs.set();
		for (ll x : a) {
			bs &= (adj[x] | (unite << x));
		}
		bs &= m;
		if (bs == bitset<MAXN>(m)) {
			ans = sz(a);
		}
		dp[m] = ans;
	}
}

ll rgt() {
	ll ans = 0;
	for (ll m = 0; m < (1ll << sz(R)); m++) {
		vll a;
		for (ll i = 0; i < n; i++) {
			if (checkbit(m, i)) {
				a.pb(R[i]);
			}
		}
		bitset<MAXN> bs;
		bitset<MAXN> unite = 1;
		bs.set();
		for (ll x : a) {
			bs &= (adj[x] | (unite << x));
		}
		ll ok = 1;
		for (ll x : a) {
			if (!bs[x]) {
				ok = 0;
				break;
			}
		}
		if (!ok) {
			continue;
		}
		bs &= ((1ll << sz(L)) - 1);
		maxeq(ans, sz(a) + dp[ll(bs.to_ullong())]);
	}
	return ans;
}

inline void solve() {
	cout << setprecision(40) << fixed;
	for (ll i = 0; i < n / 2; i++) {
		L.pb(i);
	}
	for (ll i = n / 2; i < n; i++) {
		R.pb(i);
	}
	lft();
	ld cl = rgt();
	ld ans = k / cl * k / cl * cl*(cl - 1) / 2.0;
	cout << ans << endl;
}

inline void read() {
	cin >> n >> k;
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < n; j++) {
			char c;
			cin >> c;
			adj[i][j] = c == '1';
		}
	}
}
