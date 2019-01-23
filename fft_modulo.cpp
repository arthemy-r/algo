// 1096 g
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

const ll R = 998244353;

ll binpow(ll n, ll p) {
	n %= R;
	if (p == 0) {
		return 1;
	}
	if (p == 1) {
		return n;
	}
	ll ans = binpow(n, p / 2);
	ans = ans * ans % R;
	if (p % 2 == 1) {
		ans = ans * n % R;
	}
	return ans;
}
ll inv(ll n) {
	return binpow(n, R - 2);
}

struct fourier {
	ll n;
	vll rev;
	vll ws;
	ll LOG;
	ll INV;
	fourier() {}
	fourier(ll n_) {
		LOG = log2(n_) + 1;
		n = 1ll << LOG;
		precalc();
	}
	void precalc() {
		rev.resize(n);
		ll last = 0;
		for (ll i = 1; i < n; i++) {
			if (i == (1ll << last + 1)) {
				++last;
			}
			rev[i] = rev[i ^ (1ll << last)] | (1ll << (LOG - 1 - last));
		}
		ws.resize(n);
		INV = inv(n);
		ll g = 3;
		g = binpow(g, (R - 1) / n);
		ll p = 1;
		for (ll i = 0; i < n; i++) {
			ws[i] = p;
			p = p * g % R;
		}
	}
	void fft(vll& a) {
		a.resize(n);
		for (ll i = 0; i < n; i++) {
			if (i < rev[i]) {
				swap(a[i], a[rev[i]]);
			}
		}
		for (ll k = 0; k < LOG; k++) {
			ll len = 1ll << k;
			for (ll st = 0; st < n; st += 2 * len) {
				for (ll i = 0; i < len; i++) {
					ll f = a[st + i];
					ll s = a[st + len + i] * ws[i * (1ll << LOG - 1 - k)] % R;
					a[st + i] = (f + s) % R;
					a[st + i + len] = (f - s + R) % R;
				}
			}
		}
	}
	void inv_fft(vll& a) {
		fft(a);
		for (ll i = 0; i < n; i++) {
			a[i] = a[i] * INV % R;
		}
		reverse(a.begin() + 1, a.end());
	}
};

ll n, k;
vll a;
fourier fft;

inline void solve() {
	fft = fourier(5 * n);
	vll f(5 * n, 0);
	for (ll i = 0; i < k; i++) {
		f[a[i]] = 1;
	}
	fft.fft(f);
	for (ll i = 0; i < sz(f); i++) {
		f[i] = binpow(f[i], n / 2);
	}
	fft.inv_fft(f);
	ll sum = 0;
	for (ll i = 0; i < sz(f); i++) {
		sum += f[i] * f[i] % R;
		sum %= R;
	}
	cout << sum << endl;
}

inline void read() {
	cin >> n >> k;
	a.resize(k);
	for (ll i = 0; i < k; i++) {
		cin >> a[i];
	}
}
