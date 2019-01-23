949 f
// I love meowmur
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast", "unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
#define die(cond) if (cond) for (;;){}
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

const ll MAXN = 5200 + 10;
const ll C = 1e6;

struct vect {
	ll x = 0, y = 0;
	vect() {}
	vect(ll x1, ll y1) {
		x = x1, y = y1;
	}
	vect operator + (vect a) {
		return vect(x + a.x, y + a.y);
	}
	vect operator - (vect a) {
		return vect(x - a.x, y - a.y);
	}
	ll operator * (vect a) {
		return x * a.x + y * a.y;
	}
	ll operator % (vect a) {
		return x * a.y - y * a.x;
	}
	vect operator * (ll k) {
		return vect(x*k, y*k);
	}
	vect rotate(ll a) {
		return vect(x*cos(a) - y * sin(a), x*sin(a) + y * cos(a));
	}
	bool operator == (vect b) {
		return pll(x, y) == pll(b.x, b.y);
	}
	void norm() {
		if (pll(-x, -y) < pll(x, y)) {
			x = -x;
			y = -y;
		}
	}
	ll angle() {
		if (x == 0) {
			return C * C * C + 13;
		}
		return ll(1.0 * y / x * C * C);
	}
};

struct line {
	ll a, b, c;
	line() {}
	line(vect P, vect Q) {
		a = Q.y - P.y;
		b = P.x - Q.x;
		c = -a * P.x - b * P.y;
	}
};

ll n;
vect a[MAXN];
set<pair<int, int>> q;
pair<ll, int> ls[MAXN][MAXN];
vect bad = { C + 1, C + 1 };
int used[MAXN];

inline ll det(ll a, ll b, ll c, ll d) {
	return a * d - b * c;
}

inline vect inter(line a, line b) {
	ll d = det(a.a, a.b, b.a, b.b);
	ll dx = det(-a.c, a.b, -b.c, b.b);
	ll dy = det(a.a, -a.c, b.a, -b.c);
	if (d == 0) {
		return bad;
	}
	if (dx % d != 0 || dy % d != 0) {
		return bad;
	}
	vect O(dx / d, dy / d);
	if (O.x > C || O.x < -C || O.y > C || O.y < -C) {
		return bad;
	}
	return O;
}

inline bool collinear(vect A, vect B, vect C) {
	vect AB = B - A, AC = C - A;
	return AB % AC == 0;
}

inline void solve() {
	for (int i = 0; i < n; i++) {
		int ptr = 0;
		for (int j = 0; j < n; j++) {
			if (i == j) {
				continue;
			}
			vect v = a[j] - a[i];
			v.norm();
			ls[i][ptr++] = { v.angle(), j };
		}
		sort(ls[i], ls[i] + n - 1);
	}
	int A = 0;
	int mark = 0;
	for (int B = 0; B < n; B++) {
		ll C = 1;
		if (B == 1) {
			C = 2;
		}
		for (int D = 0; D < n; D++) {
			if (D == A || D == B || D == C) {
				continue;
			}
			line AB(a[A], a[B]), CD(a[C], a[D]);
			vect O = inter(AB, CD);
			if (O == bad) {
				continue;
			}
			if (q.count({ O.x, O.y })) {
				continue;
			}
			++mark;
			used[A] = used[B] = used[C] = used[D] = mark;
			bool ok = 1;
			for (int E = 0; E < n; E++) {
				if (used[E] == mark) {
					continue;
				}
				vect v = a[E] - O;
				v.norm();
				auto it = lower_bound(ls[E], ls[E] + n - 1, pair<ll, int>(v.angle(), -1));
				if (it - ls[E] == n-1) {
					ok = 0;
					break;
				}
				int F = it->sd;
				if (used[F] == mark) {
					ok = 0;
					break;
				}
				if (!collinear(a[E], O, a[F])) {
					ok = 0;
					break;
				}
				used[E] = used[F] = mark;
			}
			if (ok) {
				cout << "Yes" << endl;
				cout << O.x << " " << O.y << endl;
				return;
			}
		}
	}
	cout << "No" << endl;
}

inline void read() {
	cin >> n;
	n *= 2;
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
		q.insert({ a[i].x, a[i].y });
	}
}
