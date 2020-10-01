// 903 f
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
const ll inf = numeric_limits<ll>::max() / 10;
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

const ll MAXN = 1e3 + 11;
const ll MAXT = 1ll << 12;
ll n;
ll a1, a2, a3, a4;
ll a[5][MAXN];
ll dp[MAXN][5][MAXT];

inline bool checkbit(ll n, ll p) {
	return n & (1ll << p);
}
inline void setbit(ll& n, ll p) {
	n |= (1ll << p);
}
inline ll shift(ll n) {
	return n >> 1ll;
}

inline void solve() {
	for (ll i = 0; i <= n + 10; i++) {
		for (ll j = 0; j <= 4; j++) {
			for (ll k = 0; k < MAXT; k++) {
				dp[i][j][k] = inf;
			}
		}
	}
	dp[3][4][0] = 0;
	for (ll i = 0; i <= n + 3; i++) {
		for (ll j = 1; j <= 4; j++) {
			ll v = (i - 1) * 4 + (j - 1);
			ll u = v - 11;
			if (u < 0) {
				continue;
			}
			ll pi = u / 4 + 1, pj = u % 4 + 1;
			if (pi > MAXT || pj > 4) {
				continue;
			}
			for (ll m = 0; m < MAXT; m++) {
				if (!a[pj][pi] || checkbit(m, 0)) {
					ll ni = i, nj = j + 1;
					if (j == 4) {
						ni = i + 1, nj = 1;
					}
					mineq(dp[ni][nj][shift(m)], dp[i][j][m]);
				}
				if (pj <= 4) {
					ll m1 = m;
					setbit(m1, 0);
					mineq(dp[i][j][m1], dp[i][j][m] + a1);
				}
				if (pj <= 3) {
					ll m2 = m;
					setbit(m2, 0);
					setbit(m2, 1);
					setbit(m2, 4);
					setbit(m2, 5);
					mineq(dp[i][j][m2], dp[i][j][m] + a2);
				}
				if (pj <= 2) {
					ll m3 = m;
					setbit(m3, 0);
					setbit(m3, 1);
					setbit(m3, 2);
					setbit(m3, 4);
					setbit(m3, 5);
					setbit(m3, 6);
					setbit(m3, 8);
					setbit(m3, 9);
					setbit(m3, 10);
					mineq(dp[i][j][m3], dp[i][j][m] + a3);
				}
				if (pj <= 1) {
					ll m4 = MAXT - 1;
					mineq(dp[i + 1][j][m4], dp[i][j][m] + a4);
				}
			}
		}
	}
	ll ans = dp[n + 3][4][0];
	cout << ans << endl;
}

inline void read() {
	cin >> n;
	cin >> a1 >> a2 >> a3 >> a4;
	for (ll i = 1; i <= 4; i++) {
		for (ll j = 1; j <= n; j++) {
			char c;
			cin >> c;
			if (c == '*') {
				a[i][j] = 1;
			}
		}
	}
}
