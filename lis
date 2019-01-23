// G from Open Olympiad
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

ll n, m;
vll a;
vector<vll> adj;
vll dp;
vector<vll> comp;
vll used;

void dfs(ll v, ll i) {
	used[v] = i;
	comp[i].pb(a[v]);
	for (ll u : adj[v]) {
		if (used[u] != -1) {
			continue;
		}
		dfs(u, i);
	}
}

ll lis() {
	dp.assign(n + 1, inf);
	dp[0] = -inf;
	vll u;
	for (ll i = 0; i < n; i++) {
		vector<pll> pot;
		ll k = 0;
		for (ll x : comp[used[i]]) {
			while (dp[k] < x) {
				++k;
			}
			if (k <= n && dp[k - 1] < x && x < dp[k]) {
				pot.pb({ k, x });
			}
		}
		for (pll p : pot) {
			mineq(dp[p.ft], p.sd);
		}
	}
	ll len = 0;
	for (ll i = 0; i <= n; i++) {
		if (dp[i] != inf) {
			len = i;
		}
	}
	return len;
}

inline void solve() {
	ll ans = lis();
	cout << ans << endl;
}

inline void read() {
	cin >> n >> m;
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	adj.resize(n);
	for (ll i = 0; i < m; i++) {
		ll v, u;
		cin >> v >> u;
		--v, --u;
		adj[v].pb(u);
		adj[u].pb(v);
	}
	used.assign(n, -1);
	for (ll i = 0; i < n; i++) {
		if (used[i] == -1) {
			comp.pb({});
			dfs(i, sz(comp) - 1);
			sort(all(comp.back()));
		}
	}
}
