// 984 d
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define _DEBUG
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

inline void solve(), read();

int main() {
	fast;
	read();
	solve();
	return 0;
}

const ll MAXS = 26;

struct edge {
	ll c = 0, word = 0, par = 0, ind = -1;
	ll subs[MAXS];
	ll go[MAXS];
	edge() {
		fill(subs, subs + MAXS, 0);
		fill(go, go + MAXS, -1);
	}
	edge(ll c_, ll p_, ll i) {
		fill(subs, subs + MAXS, 0);
		fill(go, go + MAXS, -1);
		c = c_;
		par = p_;
		ind = i;
	}
};

struct trie {
	ll n;
	vector<edge> t;
	vll mlink, mslink;
	trie() {}
	trie(vector<string>& ss) {
		t.pb({});
		for (ll i = 0; i < sz(ss); i++) {
			add(ss[i], i);
		}
		mlink.assign(sz(t), -1);
		mslink.assign(sz(t), -1);
	}
	inline ll newv(ll c, ll p, ll i) {
		t.pb({ c, p, i });
		n = sz(t);
		return n - 1;
	}
	inline void add(string& s, ll i) {
		ll v = 0;
		for (ll c : s) {
			c -= 'a';
			if (!t[v].subs[c]) {
				t[v].subs[c] = newv(c, v, i);
			}
			v = t[v].subs[c];
		}
		t[v].word = 1;
		t[v].ind = i;
	}
	ll link(ll v) {
		if (mlink[v] != -1) {
			return mlink[v];
		}
		if (v == 0) {
			mlink[v] = 0;
		} else if (t[v].par == 0) {
			mlink[v] = 0;
		} else {
			mlink[v] = go(link(t[v].par), t[v].c);
		}
		return mlink[v];
	}
	ll go(ll v, ll c) {
		if (t[v].go[c] != -1) {
			return t[v].go[c];
		}
		if (t[v].subs[c]) {
			t[v].go[c] = t[v].subs[c];
		} else if (v == 0) {
			t[v].go[c] = 0;
		} else {
			t[v].go[c] = go(link(v), c);
		}
		return t[v].go[c];
	}
	ll slink(ll v) {
		if (mslink[v] != -1) {
			return mslink[v];
		}
		if (t[link(v)].word) {
			mslink[v] = link(v);
		} else if (link(v) == 0) {
			mslink[v] = 0;
		} else {
			mslink[v] = slink(link(v));
		}
		return mslink[v];
	}
};

string s;
ll n;
vll k;
vector<string> m;
trie t;
vector<vll> in;

void find(string& s) {
	ll v = 0;
	for (ll i = 0; i < sz(s); i++) {
		ll c = s[i] - 'a';
		v = t.go(v, c);
		ll u = v;
		while (u) {
			if (t.t[u].word) {
				in[t.t[u].ind].pb(i);
			}
			u = t.slink(u);
		}
	}
}

inline void solve() {
	t = trie(m);
	in.resize(n);
	find(s);
	for (ll i = 0; i < n; i++) {
		ll ans = inf;
		--k[i];
		for (ll j = 0; j < sz(in[i]) - k[i]; j++) {
			ll p = in[i][j + k[i]] - in[i][j] + sz(m[i]);
			mineq(ans, p);
		}
		if (ans == inf) {
			ans = -1;
		}
		cout << ans << endl;
	}
}

inline void read() {
	cin >> s >> n;
	k.resize(n), m.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> k[i] >> m[i];
	}
}
