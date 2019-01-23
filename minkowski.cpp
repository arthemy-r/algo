// 87 e
#pragma GCC optimize("O3", "unroll-loops")
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
typedef long long ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vector<ll> vll;
typedef set<ll> sll;
typedef map<ll, ll> mll;
const ll inf = numeric_limits<ll>::max() / 2;
const ld eps = 1e-9;
const ld pi = acos(-1);

struct vect {
	ll x, y;
	vect() {}
	vect(ll x1, ll y1) {
		x = x1, y = y1;
	}
	vect operator + (vect &a) {
		return vect(x + a.x, y + a.y);
	}
	vect operator - (vect &a) {
		return vect(x - a.x, y - a.y);
	}
	ll operator * (vect &a) {
		return x * a.x + y * a.y;
	}
	ll operator % (vect &a) {
		return x * a.y - y * a.x;
	}
	vect operator * (ll k) {
		return vect(x*k, y*k);
	}
	vect rotate(ld a) {
		return vect(x*cos(a) - y * sin(a), x*sin(a) + y * cos(a));
	}
	bool operator == (vect a) {
		return pll(x, y) == pll(a.x, a.y);
	}
	bool operator < (vect &a) {
		return pll(y, x) < pll(a.y, a.x);
	}
};

bool comp(vect &a, vect &b) {
	if (a.y >= 0 && b.y < 0) {
		return true;
	}
	if (a.y < 0 && b.y >= 0) {
		return false;
	}
	if (a.y == 0 && b.y == 0) {
		if (a.x > 0 && b.x < 0) {
			return true;
		} else if (a.x < 0 && b.x > 0) {
			return false;
		}
		return a.x < b.x;
	}
	ll p = a % b;
	if (p == 0) {
		return a * a < b * b;
	}
	return p > 0;
}

vector<vect> x1, x2, x3;
vector<vect> mink;
vect O;

vector<vect> get(vector<vect> &a, vector<vect> &b, vector<vect> &c) {
	vector<vect> d;
	
	a.pb(a[0]);
	for (ll i = 0; i < sz(a) - 1; i++) {
		d.pb(a[i + 1] - a[i]);
	}
	a.popb();
	sort(all(a));
	
	b.pb(b[0]);
	for (ll i = 0; i < sz(b) - 1; i++) {
		d.pb(b[i + 1] - b[i]);
	}
	b.popb();
	sort(all(b));
	
	c.pb(c[0]);
	for (ll i = 0; i < sz(c) - 1; i++) {
		d.pb(c[i + 1] - c[i]);
	}
	c.popb();
	sort(all(c));
	
	sort(all(d), comp);

	vect A = a[0] + b[0] + c[0];

	vector<vect> res;
	res.pb(A);
	res.pb(res.back() + d[0]);
	for (ll i = 1; i < sz(d); i++) {
		if (d[i] == vect(0, 0)) {
			continue;
		}
		vect v1 = (res.back() + d[i]) - res.back();
		vect v2 = res.back() - res[sz(res) - 2];
		ll p = v1 % v2;
		if (p == 0) {
			res[sz(res) - 1] = res.back() + d[i];
			continue;
		}
		res.pb(res.back() + d[i]);
	}
	return res;
}

int sign(ll a) {
	if (a > 0) {
		return 1;
	} else if (a < 0) {
		return -1;
	} else {
		return 0;
	}
}

bool check(vect P, vect A, vect B) {
	vect OP = P - O, OA = A - O, OB = B - O;
	ll p1 = OP % OA, p2 = OA % OB;
	return sign(p1) != sign(p2);
}

bool triangle(vect P, vect A, vect B, vect C) {
	vect PA = A - P, PB = B - P, PC = C - P, AB = B - A, AC = C - A;
	ull s1 = ull(abs(PA % PB)) + ull(abs(PB % PC)) + ull(abs(PC % PA));
	ull s2 = abs(AB % AC);
	return s1 == s2;
}

bool solve(vect P) {
	ll n = sz(mink);
	ll l = -1, r = n - 1;
	while (r - l > 1) {
		ll m = (l + r) / 2;
		if (check(P, mink[m], mink[m + 1])) {
			l = m;
		} else {
			r = m;
		}
	}
	if (l == -1) {
		return false;
	}
	return triangle(P, O, mink[l], mink[l + 1]);
}

void solve() {
	ll m;
	cin >> m;
	mink = get(x1, x2, x3);
	mink.popb();
	O = mink.back();
	mink.popb();
	for (ll i = 0; i < m; i++) {
		vect P;
		cin >> P.x >> P.y;
		P.x *= 3, P.y *= 3;
		bool ans = solve(P);
		if (ans) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
}

void change(vector<vect> &a) {
	ll n;
	cin >> n;
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
	}
}

void read() {
	change(x1);
	change(x2);
	change(x3);
}

int main() {
	fast;
	read();
	solve();
	return 0;
}
