// 1185
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
#define istrop template <typename T> inline istream& operator >>
#define ostrop template <typename T> inline ostream& operator <<
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vector<ll> vll;
typedef set<ll> sll;
typedef map<ll, ll> mll;
istrop(istream& in, pair<T, T>& v) {
	in >> v.ft >> v.sd; return in;
}
ostrop(ostream& out, pair<T, T> v) {
	out << v.ft << " " << v.sd; return out;
}
istrop(istream& in, vector<T>& v) {
	for (ll i = 0; i < sz(v); i++) in >> v[i]; return in;
}
ostrop(ostream& out, vector<T>& v) {
	for (ll i = 0; i < sz(v); i++) out << v[i] << " "; return out;
}
istrop(istream& in, pair<vector<T>*, vector<T>*> v) {
	for (ll i = 0; i < sz(*v.ft); i++) in >> (*v.ft)[i] >> (*v.sd)[i]; return in;
}
const ll inf = numeric_limits<ll>::max() / 2;
const ld eps = 1e-9;
const ld pi = acos(-1);

struct vect {
	ld x, y;
	vect() {}
	vect(ll x_, ll y_) {
		x = x_, y = y_;
	}
	ld operator * (vect a) {
		return x * a.x + y * a.y;
	}
	ld operator % (vect a) {
		return x * a.y - y * a.x;
	}
	vect operator - (vect a) {
		return vect(x - a.x, y - a.y);
	}
	vect operator + (vect a) {
		return vect(x + a.x, y + a.y);
	}
	bool operator < (vect a) {
		return pld(x, y) < pld(a.x, a.y);
	}
	bool operator == (vect a) {
		return pld(x, y) == pld(a.x, a.y);
	}
	bool operator != (vect a) {
		return pld(x, y) != pld(a.x, a.y);
	}
};

vect O;

bool lrot(vect A, vect B) {
	vect OA = A - O, OB = B - O;
	ld p = OA % OB;
	if (p == 0) {
		return OA * OA > OB * OB;
	}
	return p > 0;
}

void convex_hull(vector<vect>& a, vector<vect>& ans) {
	sort(all(a));
	O = a[0];
	sort(a.begin() + 1, a.end(), lrot);
	a.pb(a[0]);
	ans.pb(a[0]);
	for (ll i = 1; i < sz(a); i++) {
		vect K = a[i];
		ll line2 = 0;
		while (sz(ans) >= 2) {
			vect M = ans[sz(ans) - 1];
			vect N = ans[sz(ans) - 2];
			vect MK = K - M, NM = N - M;
			ld p = MK % NM;
			if (p < 0) {
				ans.popb();
			} else if (p == 0) {
				if (sz(ans) == 2) {
					line2 = 1;
					break;
				}
				ans.popb();
			} else {
				break;
			}
		}
		if (!line2) {
			ans.pb(a[i]);
		}
	}
	if (ans.back() != O) {
		ans.pb(O);
	}
}

ld per(vector<vect>& a) {
	ld ans = 0;
	for (ll i = 0; i < sz(a) - 1; i++) {
		ans += sqrt((a[i + 1] - a[i])*(a[i + 1] - a[i]));
	}
	return ans;
}

ll n;
ld d;
vector<vect> a, res;

inline void solve() {
	convex_hull(a, res);
	ld len = per(res);
	ld ans = len + 2 * pi*d;
	cout << setprecision(0) << fixed << ans << endl;
}

inline void read() {
	cin >> n >> d;
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
	}
}

int main() {
	fast;
	read();
	solve();
	return 0;
}
