// 100246 b
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

struct fenwick {
	ll n;
	vector<vector<vll>> t;
	fenwick() {}
	fenwick(ll n_) {
		n = n_;
		t.assign(n, vector<vll>(n, vll(n, 0)));
	}
	ll f(ll i) {
		return i & (i + 1);
	}
	ll g(ll i) {
		return i | (i + 1);
	}
	void inc(ll x, ll y, ll z, ll d) {
		for (ll i = x; i < n; i = g(i)) {
			for (ll j = y; j < n; j = g(j)) {
				for (ll k = z; k < n; k = g(k)) {
					t[i][j][k] += d;
				}
			}
		}
	}
	ll sum(ll x, ll y, ll z) {
		ll ans = 0;
		for (ll i = x; i >= 0; i = f(i) - 1) {
			for (ll j = y; j >= 0; j = f(j) - 1) {
				for (ll k = z; k >= 0; k = f(k) - 1){
					ans += t[i][j][k];
				}
			}
		}
		return ans;
	}
};

ll n;
fenwick f;

inline void solve() {
	f = fenwick(n);
	while (1) {
		ll op;
		cin >> op;
		if (op == 1) {
			ll x, y, z, k;
			cin >> x >> y >> z >> k;
			f.inc(x, y, z, k);
		} else if (op == 2) {
			ll x[2], y[2], z[2];
			cin >> x[0] >> y[0] >> z[0] >> x[1] >> y[1] >> z[1];
			--x[0], --y[0], --z[0];
			ll s[2][2][2];
			for (ll i = 0; i < 2; i++) {
				for (ll j = 0; j < 2; j++) {
					for (ll k = 0; k < 2; k++) {
						s[i][j][k] = f.sum(x[i], y[j], z[k]);
					}
				}
			}
			ll s1 = s[1][1][0] + s[1][0][1] + s[0][1][1];
			ll s2 = s[0][0][1] + s[0][1][0] + s[1][0][0];
			ll s3 = s[0][0][0];
			ll ans = s[1][1][1] - (s1 - s2 + s3);
			cout << ans << endl;
		} else if (op == 3) {
			break;
		}
	}
}

inline void read() {
	cin >> n;
}

int main() {
	fast;
	freopen("stars.in", "r", stdin);
	freopen("stars.out", "w",stdout);
	read();
	solve();
	return 0;
}
