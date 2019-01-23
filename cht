// 319 c
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(a) (ll)((a).size())
#define heap priority_queue
#define hash_map unordered_map
#define hash_set unordered_set
#define ft first
#define sd second
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl "\n"
#define mineq(a, b) (a) = min((a), (b))
#define maxeq(a, b) (a) = max((a), (b))
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

ll n;
vll a, b, dp, id;
vector<pll> lines;

ld inter(pll a, pll b) {
	// k1*x+b1=k2*x+b2
	// x*(k1-k2)=b2-b1
	// x = (b2-b1)/(k1-k2)
	return ld(b.sd - a.sd) / ld(a.ft - b.ft);
}

void cht(pll line, ll ind) {
	while (sz(lines) >= 2) {
		ld xnew = inter(line, lines[sz(lines) - 1]);
		ld xold = inter(lines[sz(lines) - 1], lines[sz(lines) - 2]);
		if (xnew > xold) {
			break;
		}
		id.popb();
		lines.popb();
	}
	lines.pb(line);
	id.pb(ind);
}

bool check(ll ind, ld x) {
	if (ind == 0) {
		return true;
	}
	ld xold = inter(lines[ind], lines[ind - 1]);
	return xold <= x;
}

inline void solve() {
	dp.resize(n);
	dp[0] = 0;
	cht({ b[0], dp[0] }, 0);
	for (ll i = 1; i < n; i++) {
		ll l = -1, r = sz(lines);
		while (r - l > 1) {
			ll m = (l + r) / 2;
			if (check(m, a[i])) {
				l = m;
			} else {
				r = m;
			}
		}
		dp[i] = dp[id[l]] + b[id[l]] * a[i];
		cht({ b[i], dp[i] }, i);
	}
	cout << dp[n - 1] << endl;
}

inline void read() {
	cin >> n;
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	b.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> b[i];
	}
}

int main() {
	fast;
	read();
	solve();
	return 0;
}
