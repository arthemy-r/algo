// 149 e
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
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
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl "\n"
#define mineq(a, b) (a) = ((a)>(b))?(b):(a)
#define maxeq(a, b) (a) = ((a)<(b))?(b):(a)
#define die(cond) if (cond) for(;;){}
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

inline void solve(), read();

int main() {
	fast;
	read();
	solve();
	return 0;
}

ll n, m;
string s;
vector<string> p;

vll zet(string& s) {
	ll n = sz(s);
	vll z(n, 0);
	ll l = 0, r = -1;
	for (ll i = 1; i < n; i++) {
		z[i] = 0;
		if (i <= r) {
			z[i] = min(r - i, z[i - l]);
		}
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
			++z[i];
		}
		if (i + z[i] > r) {
			l = i, r = i + z[i];
		}
	}
	return z;
}

ll solve1(string& p) {
	ll m = sz(p);
	string tp = p + "#" + s;
	vll zp = zet(tp);
	reverse(all(p)), reverse(all(s));
	string ts = p + "#" + s;
	reverse(all(p)), reverse(all(s));
	vll zs = zet(ts);
	vll pref(m + 1, inf);
	ll j = 1;
	for (ll i = m + 1; i < sz(tp); i++) {
		while (j <= m && zp[i] >= j) {
			pref[j] = i - m - 1;
			++j;
		}
	}
	vll suff(m + 1, -inf);
	j = 1;
	for (ll i = m + 1; i < sz(ts); i++) {
		while (j <= m && zs[i] >= j) {
			suff[j] = sz(s) - 1 - (i - m - 1);
			++j;
		}
	}
	for (ll i = 1; i <= m; i++) {
		if (suff[m - i] >= pref[i] + m - 1) {
			return 1;
		}
	}
	return 0;
}

inline void solve() {
	ll ans = 0;
	for (string& k : p) {
		ans += solve1(k);
	}
	cout << ans << endl;
}

inline void read() {
	cin >> s;
	n = sz(s);
	cin >> m;
	p.resize(m);
	for (ll i = 0; i < m; i++) {
		cin >> p[i];
	}
}
