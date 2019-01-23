// 18 d
#define _CRT_SECURE_NO_WARNINGS
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
#define die(cond) if (cond) for (;;){}
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
const ll inf = numeric_limits<ll>::max() / 2;
const ld eps = 1e-9;
const ld pi = acos(-1);
template<typename T> inline bool mineq(T& a, T b) { return (a > b) ? (a = b, 1) : 0; }
template<typename T> inline bool maxeq(T& a, T b) { return (a < b) ? (a = b, 1) : 0; }

inline void solve(), read();
const string file = "";

int main() {
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

struct query {
	ll t, x;
};
struct bigint {
	ll n;
	vll t;
	const ll R = 1e9;
	const ll S = 9;
	bigint() {}
	bigint(string s) {
		for (ll i = sz(s); i > 0; i -= S) {
			if (i < S) {
				string r = s.substr(0, i);
				t.pb(atoi(r.c_str()));
			} else {
				string r = s.substr(i - S, S);
				t.pb(atoi(r.c_str()));
			}
		}
		n = sz(t);
	}
	bigint(ll x) : bigint(to_string(x)) {}
	void resize(ll n_) {
		t.resize(n_, 0);
		n = sz(t);
	}
	void del0() {
		while (sz(t) > 1 && t.back() == 0) {
			t.popb();
		}
		n = sz(t);
	}
	bool operator == (bigint& a) {
		del0();
		a.del0();
		return this->t == a.t;
	}
	bool operator < (bigint& a) {
		if (*this == a) {
			return 0;
		}
		if (n < a.n) {
			return 1;
		}
		for (ll i = n - 1; i >= 0; i--) {
			if (t[i] == a.t[i]) {
				continue;
			}
			return t[i] < a.t[i];
		}
		return 0;
	}
	bool operator > (bigint& a) {
		if (*this == a) {
			return 0;
		}
		return a < *this;
	}
	void print() {
		del0();
		cout << t.back();
		for (ll i = n - 2; i >= 0; i--) {
			string s = to_string(t[i]);
			for (ll i = 0; i < S - sz(s); i++) {
				cout << 0;
			}
			cout << s;
		}
	}
	bigint operator + (bigint& a) {
		ll s = n + a.n + 1;
		bigint c;
		resize(s), a.resize(s), c.resize(s);
		ll carry = 0;
		for (ll i = 0; i < s; i++) {
			c.t[i] = carry + t[i] + a.t[i];
			carry = c.t[i] / R;
			if (carry) {
				c.t[i] %= R;
			}
		}
		del0(), a.del0(), c.del0();
		return c;
	}
	bigint operator - (bigint& a) {
		bigint(c);
		ll s = n + a.n + 1;
		resize(s), a.resize(s), c.resize(s);
		ll carry = 0;
		for (ll i = 0; i < s; i++) {
			c.t[i] = t[i] - a.t[i] - carry;
			carry = c.t[i] < 0;
			if (carry) {
				c.t[i] += R;
			}
		}
		del0(), a.del0(), c.del0();
		return c;
	}
	bigint operator * (bigint& a) {
		ll s = n + a.n + 1;
		bigint c;
		resize(2 * s), a.resize(2 * s), c.resize(2 * s);
		for (ll i = 0; i < s; i++) {
			ll carry = 0;
			for (ll j = 0; j < s; j++) {
				c.t[i + j] = c.t[i + j] + t[i] * a.t[j] + carry;
				carry = c.t[i + j] / R;
				if (carry) {
					c.t[i + j] %= R;
				}
			}
		}
		del0(), a.del0(), c.del0();
		return c;
	}
	bigint operator / (ll a) {
		bigint c;
		c.resize(n);
		ll carry = 0;
		for (ll i = n - 1; i >= 0; i--) {
			ll cur = t[i] + carry * R;
			carry = cur % a;
			c.t[i] = cur / a;
		}
		c.del0();
		return c;
	}
	ll operator % (ll a) {
		bigint c = *this / a;
		bigint A(a);
		bigint d = c * A;
		bigint ans = *this - d;
		return ans.t[0];
	}
	bigint& operator = (bigint a) {
		t = a.t;
		n = a.n;
		return *this;
	}
	bigint operator ^ (ll p) {
		if (p == 0) {
			return 1;
		}
		if (p == 1) {
			return *this;
		}
		bigint a = (*this) ^ (p / 2);
		a = a * a;
		if (p % 2 == 1) {
			a = a * (*this);
		}
		return a;
	}
};
const ll MAXN = 5e3 + 10;
ll n;
vector<query> a;
vll ans, good;

inline void solve() {
	good.assign(n, -1);
	for (ll x = MAXN; x >= 0; x--) {
		ll ok = -1;
		for (ll i = 0; i < n; i++) {
			if (good[i] != -1) {
				ok = -1;
				continue;
			} else if (a[i].t == 0 && a[i].x == x) {
				ok = i;
			} else if (a[i].t == 1 && a[i].x == x && ok != -1) {
				if (ok != -1) {
					for (ll j = ok; j <= i; j++) {
						good[j] = x;
					}
					ok = -1;
					ans.pb(x);
				}
			}
		}
	}
	bigint res(0);
	for (ll x : ans) {
		bigint y(2);
		y = y ^ x;
		res = res + y;
	}
	res.print();
}

inline void read() {
	cin >> n;
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		string s;
		ll x;
		cin >> s >> x;
		if (s == "sell") {
			a[i].t = 1;
		} else if (s == "win") {
			a[i].t = 0;
		}
		a[i].x = x;
	}
}
