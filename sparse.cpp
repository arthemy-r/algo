// 191 c
#pragma GCC optimize ("O3", "unroll-loops")
#include <bits/stdc++.h>
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

const ll LOG = 23;
const ll MAXN = 1e5 + 10;

struct edge {
	ll u, i;
	edge() {}
	edge(ll u, ll i): u(u), i(i) {}
};

struct graph {
	ll vn;
	vector<edge> es[MAXN];
	graph() {}
	graph(ll v) {
		vn = v;
	}
	void insert(ll v, ll u, ll i) {
		es[v].pb({ u, i });
		es[u].pb({ v, i });
	}
};

struct sparse {
	vector<vector<pll>> t;
	vll logs;
	sparse() {}
	sparse(vll& a) {
		ll N = sz(a);
		logs.resize(N + 1);
		for (ll i = 0; i <= N; i++) {
			logs[i] = log2(i);
		}
		t.assign(N, vector<pll>(logs[N] + 1, { inf, -1 }));
		for (ll i = 0; i < sz(a); i++) {
			t[i][0] = { a[i], i };
		}
		for (ll j = 1; j <= logs[N]; j++) {
			for (ll i = 0; i < N; i++) {
				if (i + (1 << j - 1) >= N) {
					break;
				}
				t[i][j] = min(t[i][j - 1], t[i + (1 << j - 1)][j - 1]);
			}
		}
	}
	ll rmq(ll L, ll R) {
		ll l = logs[R - L + 1];
		pll ans = min(t[L][l], t[R - (1 << l) + 1][l]);
		return ans.second;
	}
};

ll N, K;
graph g;
sparse st;

vll order, ds;
ll first[MAXN];
void precalc(ll v, ll p, ll d = 0) {
	order.pb(v);
	ds.pb(d);
	if (!first[v]) {
		first[v] = order.size() - 1;
	}
	for (edge e : g.es[v]) {
		if (e.u == p) {
			continue;
		}
		precalc(e.u, v, d + 1);
		order.pb(v);
		ds.pb(d);
	}
}

ll lca(ll a, ll b) {
	if (first[a] > first[b]) {
		swap(a, b);
	}
	ll ind = st.rmq(first[a], first[b]);
	return order[ind];
}

ll add[MAXN];
ll ans[MAXN];

ll dfs(ll v, ll p) {
	ll res = add[v];
	for (edge e : g.es[v]) {
		if (e.u == p) {
			continue;
		}
		ll cur = dfs(e.u, v);
		ans[e.i] = cur;
		res += cur;
	}
	return res;
}

void solve() {
	order.pb({}), ds.pb({});
	precalc(1, 1);
	st = sparse(ds);
	cin >> K;
	for (ll i = 0; i < K; i++) {
		ll a, b;
		cin >> a >> b;
		ll l = lca(a, b);
		add[l] -= 2;
		++add[a], ++add[b];
	}
	dfs(1, 1);
	for (ll i = 0; i < N - 1; i++) {
		cout << ans[i] << " ";
	}
}

int main() {
	fast;
	cin >> N;
	g = graph(N);
	for (ll i = 0; i < N - 1; i++) {
		ll v, u;
		cin >> v >> u;
		g.insert(v, u, i);
	}
	solve();
	return 0;
}
