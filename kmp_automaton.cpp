// 346 b
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

struct step {
	ll a, b, c;
};

const ll MAXN = 100 + 10;
ll n, m, v;
string s, t, virus;
vll p;
vector<vll> aut;
ll dp[MAXN][MAXN][MAXN];
step par[MAXN][MAXN][MAXN];

void prefix(string& s, vll& p) {
	ll n = sz(s);
	p.resize(n);
	for (ll i = 1; i < n; i++) {
		ll j = p[i - 1];
		while (j && s[i] != s[j]) {
			j = p[j - 1];
		}
		if (s[i] == s[j]) {
			++j;
		}
		p[i] = j;
	}
}
void automaton(string& s, vll& p) {
	ll n = sz(s);
	aut.assign(n, vll(26, 0));
	for (ll i = 0; i < n; i++) {
		for (ll c = 'A'; c <= 'Z'; c++) {
			if (i && c != s[i]) {
				aut[i][c - 'A'] = aut[p[i - 1]][c - 'A'];
			} else {
				aut[i][c - 'A'] = i + (c == s[i]);
			}
		}
	}
}
string ans;
void restore(ll i, ll j, ll k) {
	if (dp[i][j][k] == 0) {
		return;
	}
	if (i && dp[i][j][k] == dp[i - 1][j][k]) {
		restore(i - 1, j, k);
		return;
	}
	if (j && dp[i][j][k] == dp[i][j - 1][k]) {
		restore(i, j - 1, k);
		return;
	}
	if (i && j) {
		for (ll z = 0; z < v; z++) {
			if (dp[i][j][k] == dp[i - 1][j - 1][z] + 1 && aut[z][s[i] - 'A'] == k) {
				ans += s[i];
				restore(i - 1, j - 1, z);
				return;
			}
		}
	}
}
void calcdp() {
	dp[0][0][0] = 0;
	ll cur = 0;
	ll I = 0, J = 0, K = 0;
	for (ll i = 0; i <= n; i++) {
		for (ll j = 0; j <= m; j++) {
			for (ll k = 0; k < v; k++) {
				if (maxeq(cur, dp[i][j][k])) {
					I = i, J = j, K = k;
				}
				if (i != n && j != m && s[i + 1] == t[j + 1]) {
					ll val = aut[k][s[i + 1] - 'A'];
					if (val < v) {
						if (maxeq(dp[i + 1][j + 1][val], dp[i][j][k] + 1)) {
							par[i + 1][j + 1][val] = { i, j, k };
						}
					}
				}
				if (i != n) {
					if (maxeq(dp[i + 1][j][k], dp[i][j][k])) {
						par[i + 1][j][k] = { i, j, k };
					}
				}
				if (j != m) {
					if (maxeq(dp[i][j + 1][k], dp[i][j][k])) {
						par[i][j + 1][k] = { i, j, k };
					}
				}
			}
		}
	}
	restore(I, J, K);
	reverse(all(ans));
}

inline void solve() {
	prefix(virus, p);
	automaton(virus, p);
	s.insert(s.begin(), '$');
	t.insert(t.begin(), '$');
	calcdp();
	if (ans == "") {
		cout << 0 << endl;
		return;
	}
	cout << ans << endl;
}

inline void read() {
	cin >> s >> t >> virus;
	n = sz(s), m = sz(t), v = sz(virus);
}
