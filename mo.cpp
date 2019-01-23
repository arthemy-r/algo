// 877 f
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

const ll SQRT = 700;
ll n, k, q;
vll t, a;
vll ls, rs;
vector<long long> p;
hash_map<long long, ll> cnt;
vll ind;
vector<long long> Ans;

bool comp(ll i, ll j) {
	if (ls[i] / SQRT != ls[j] / SQRT) {
		return ls[i] < ls[j];
	}
	return rs[i] < rs[j];
}

void Rr(ll i, long long& ans) {
	ans += cnt[p[i] - k];
	++cnt[p[i]];
}
void Rl(ll i, long long& ans) {
	--cnt[p[i]];
	ans -= cnt[p[i] - k];
}
void Lr(ll i, long long& ans) {
	--cnt[p[i]];
	ans -= cnt[p[i] + k];
}
void Ll(ll i, long long& ans) {
	ans += cnt[p[i] + k];
	++cnt[p[i]];
}

void mo() {
	Ans.assign(q, -1);
	ind.resize(q);
	iota(all(ind), 0);
	sort(all(ind), comp);
	long long ans = 0;
	ll cl = 0, cr = 0;
	cnt[0] = 1;
	for (ll i : ind) {
		ll l = ls[i], r = rs[i];
		while (cl < l) {
			Lr(cl, ans);
			++cl;
		}
		while (cr > r) {
			Rl(cr, ans);
			--cr;
		}
		while (cl > l) {
			Ll(cl - 1, ans);
			--cl;
		}
		while (cr < r) {
			Rr(cr + 1, ans);
			++cr;
		}
		Ans[i] = ans;
	}
}

inline void solve() {
//	cnt.max_load_factor(0.5);
	p.assign(n + 1, 0);
	for (ll i = 0; i <= n; i++) {
		p[i] = a[i] + (i ? p[i - 1] : 0);
	}
	mo();
	for (ll i = 0; i < q; i++) {
		cout << Ans[i] << endl;
	}
}

inline void read() {
	cin >> n >> k;
	t.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> t[i];
	}
	a.resize(n + 1);
	for (ll i = 1; i <= n; i++) {
		cin >> a[i];
		if (t[i - 1] == 2) {
			a[i] = -a[i];
		}
	}
	cin >> q;
	ls.resize(q), rs.resize(q);
	for (ll i = 0; i < q; i++) {
		cin >> ls[i] >> rs[i];
		--ls[i];
	}
}
