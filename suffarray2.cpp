// 802 i
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
	return 0;
}

struct suffarray {
	ll n;
	vll sa, rsa, lcp;
	string s;
	suffarray() {}
	suffarray(string& s_) {
		s = s_;
		n = sz(s);
		s.pb('$');
		++n;
		sa.resize(n);
	}
	void build() {
		vector<pll> cur(n);
		for (ll i = 0; i < n; i++) {
			cur[i] = { s[i], i };
		}
		sort(all(cur));
		ll cid = 0;
		for (ll i = 0; i < n; i++) {
			if (i && cur[i - 1].ft != cur[i].ft) {
				++cid;
			}
			sa[cur[i].sd] = cid;
		}
		vector<pair<pll, ll>> nxt(n);
		for (ll k = 1; k < n; k *= 2) {
			for (ll i = 0; i < n; i++) {
				nxt[i] = { {sa[i], sa[(i + k) % n]}, i };
			}
			sort(all(nxt));
			ll cid = 0;
			for (ll i = 0; i < n; i++) {
				if (i && nxt[i - 1].ft != nxt[i].ft) {
					++cid;
				}
				sa[nxt[i].sd] = cid;
			}
		}
		sa.popb();
		s.popb();
		--n;
		for (ll i = 0; i < n; i++) {
			--sa[i];
		}
		rsa.resize(n);
		for (ll i = 0; i < n; i++) {
			rsa[sa[i]] = i;
		}
		swap(rsa, sa);
	}
	void build_lcp() {
		lcp.resize(n);
		ll k = 0;
		for (ll i = 0; i < n; i++) {
			if (k > 0) {
				--k;
			}
			if (rsa[i] == n - 1) {
				lcp[rsa[i]] = -1;
				k = 0;
			} else {
				ll j = sa[rsa[i] + 1];
				while (max(i + k, j + k) < n && s[i + k] == s[j + k]) {
					++k;
				}
				lcp[rsa[i]] = k;
			}
		}
	}
};

ll n;
string s;
suffarray sa;

inline void solve() {
	sa = suffarray(s);
	sa.build();
	sa.build_lcp();
	vector<pll> ps;
	for (ll i = 0; i < n - 1; i++) {
		ps.pb({ sa.lcp[i], i + 1 });
	}
	sort(all(ps));
	sll q = { 0, n };
	ll ans = 0;
	for (ll i = 0; i < sz(ps); i++) {
		ll k, x;
		tie(k, x) = ps[i];
		q.insert(x);
		auto i1 = q.find(x);
		auto i2 = i1;
		--i1, ++i2;
		ll cur = (*i2 - x)*(x - *i1) * 2 * k;
		ans += cur;
	}
	ans += n * (n + 1) / 2;
	cout << ans << endl;
}

inline void read() {
	ll t;
	cin >> t;
	for (ll i = 0; i < t; i++) {
		cin >> s;
		n = sz(s);
		solve();
	}
}
