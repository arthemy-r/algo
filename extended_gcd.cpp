// 1055 c
#define _CRT_SECURE_NO_WARNINGS
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
#define die(cond) if (cond) for (;;){}
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

int main() {
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

ll la, ra, ta;
ll lb, rb, tb;

inline ll gcd(ll a, ll b) {
	while (b != 0) {
		a %= b;
		swap(a, b);
	}
	return a;
}

inline pll extgcd(ll a, ll b) {
	if (a == 0) {
		return { 0, 1 };
	}
	ll x0, y0;
	tie(x0, y0) = extgcd(b%a, a);
	ll x = y0 - b / a * x0;
	ll y = x0;
	return { x,  y };
}

pll equ(ll a, ll b, ll c) {
	ll g = gcd(a, b);
	ll x, y;
	tie(x, y) = extgcd(a, b);
	x = x * c / g;
	y = y * c / g;
	return { x, y };
}

inline void solve() {
	ll k, m;
	ll a = ta, b = -tb, c0 = lb - la;
	ll g = abs(gcd(a, b));
	c0 = c0 / g * g;
	ll ans = 0;
	for (ll c = c0 - 1000 * g; c < c0 + 1000 * g; c += g) {
		tie(k, m) = equ(a, b, c);
		ll a1 = min(ra + k * ta, rb + m * tb) - max(la + k * ta, lb + m * tb) + 1;
		maxeq(ans, a1);
	}
	cout << ans << endl;
}

inline void read() {
	cin >> la >> ra >> ta >> lb >> rb >> tb;
}
