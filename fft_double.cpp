// 993 e
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
typedef double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vector<ll> vll;
typedef set<ll> sll;
typedef map<ll, ll> mll;
const ll inf = numeric_limits<ll>::max() / 2;
const ld eps = 1e-9;
const ld pi = acosl(-1);
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

struct cld {
	ld x = 0, y = 0;
	cld() {}
	cld(ld x_) {
		x = x_;
	}
	cld(ld x_, ld y_) {
		x = x_, y = y_;
	}
	cld operator + (cld a) {
		return { x + a.x, y + a.y };
	}
	cld operator - (cld a) {
		return { x - a.x, y - a.y };
	}
	cld operator * (cld a) {
		return { x * a.x - y * a.y, x * a.y + y * a.x };
	}
	cld operator / (cld v) {
		ld a = x, b = y, c = v.x, d = v.y;
		return { (a * c + b * d) / (c * c + d * d), (b * c - a * d) / (c * c + d * d) };
	}
};

struct fourier {
	ll n;
	vll rev;
	vector<cld> ws;
	ll LOG;
	fourier() {}
	fourier(ll n_) {
		LOG = log2l(n_) + 1;
		n = 1ll << LOG;
		precalc();
	}
	void precalc() {
		rev.resize(n);
		ll last = 0;
		for (ll i = 1; i < n; i++) {
			if (i == (2ll << last)) {
				++last;
			}
			rev[i] = rev[i - (1ll << last)] | (1ll << LOG - 1 - last);
		}
		ws.resize(n);
		for (ll i = 0; i < n; i++) {
			ws[i] = cld(cos(2.0*pi*i / n), sin(2.0*pi*i / n));
		}
	}
	void fft(vector<cld>& a) {
		for (ll i = 0; i < n; i++) {
			if (i < rev[i]) {
				swap(a[i], a[rev[i]]);
			}
		}
		for (ll k = 0; k < LOG; k++) {
			ll len = 1ll << k;
			for (ll st = 0; st < n; st += 2 * len) {
				for (ll i = 0; i < len; i++) {
					cld f = a[i + st];
					cld s = a[i + st + len] * ws[i * (1ll << (LOG - 1 - k))];
					a[i + st] = f + s;
					a[i + st + len] = f - s;
				}
			}
		}
	}
	void inv_fft(vector<cld>& a) {
		fft(a);
		for (ll i = 0; i < n; i++) {
			a[i] = a[i] / ld(n);
		}
		reverse(a.begin() + 1, a.end());
	}
	vll mult(vll& a, vll& b) {
		vector<cld> A(n), B(n);
		for (ll i = 0; i < sz(a); i++) {
			A[i] = a[i];
		}
		for (ll i = 0; i < sz(b); i++) {
			B[i] = b[i];
		}
		fft(A);
		fft(B);
		for (ll i = 0; i < n; i++) {
			A[i] = A[i] * B[i];
		}
		inv_fft(A);
		vll c(n);
		for (ll i = 0; i < n; i++) {
			c[i] = round(A[i].x);
		}
		return c;
	}
};

ll n, x;
vll a;
fourier fft;
vll s;
vll r;

ll get0() {
	ll ans = 0;
	ll j = 0;
	for (ll i = 0; i < n; i++) {
		while(j < i) {
			++j;
		}
		while (j < n && a[j] >= x) {
			++j;
		}
		ans += j - i;
	}
	return ans;
}

inline void solve() {
	fft = fourier(3 * n);
	s.resize(2 * n + 1);
	s[0] = 0;
	for (ll i = 1; i <= n; i++) {
		s[i] = s[i - 1] + (a[i - 1] < x);
	}
	r.resize(n + 1, 0);
	for (ll i = 0; i <= n; i++) {
		++r[s[i]];
	}
	ll ans0 = get0();
	cout << ans0 << " ";
	vll v = r;
	for (ll i = 0; i <= n; i++) {
		v[i] = r[n - i];
	}
	vll ans = fft.mult(r, v);
	for (ll i = 1; i <= n; i++) {
		cout << ans[n + i] << " ";
	}
}

inline void read() {
	cin >> n >> x;
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
}
