#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#define fi first
#define se second
#define ryan bear
#define sq(X) ((X)*(X))
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
const ll INF = (1ll<<60);
const int MAX = 1e9;

struct line {
	ll a, b;
	ll get(ll x) { return a*x+b; }
	line() {}
	line(ll A, ll B) { a=A, b=B; }
};

struct node {
	int l, r;
	line L;
	node() { L=line(0, INF); }
}st[(1<<21)]; int nd_tp=1;
int new_node() { return nd_tp++; }

void upd(int now, int ref, line v, ll s, ll e) {
	st[now].l = st[ref].l;
	st[now].r = st[ref].r;
	ll md=(s+e)/2;
	line lo=st[ref].L, hi=v;
	if (lo.get(s)<hi.get(s)) swap(lo, hi);
	if (lo.get(e)>=hi.get(e)) { st[now].L=hi; return ; }

	if (lo.get(md)<hi.get(md)) {
		st[now].L = lo;
		st[now].l = new_node();
		upd(st[now].l, st[ref].l, hi, s, md);
	}
	else {
		st[now].L = hi;
		st[now].r = new_node();
		upd(st[now].r, st[ref].r, lo, md+1, e);
	}
}

ll get(int now, ll x, ll s, ll e) {
	if (!now) return INF;
	ll md=(s+e)/2;
	if (x<=md) return min(st[now].L.get(x), get(st[now].l, x, s, md));
	else return min(st[now].L.get(x), get(st[now].r, x, md+1, e));
}

int N; vim adj[100010]; vlm dist[100010];
ll S[100010], V[100010], T[100010]; int chk[100010];

void dfs(int now, ll d, int nd) {
	chk[now]=1;
	if (now!=1) T[now]=get(nd, V[now], 0, MAX)+V[now]*d+S[now];
	int s=new_node(); upd(s, nd, line(-d, T[now]), 0, MAX);
	for (int i=0; i<adj[now].size(); i++) if (!chk[adj[now][i]]) dfs(adj[now][i], d+dist[now][i], s);
}

int main() {
	scanf("%d", &N);
	int u, v; ll d;
	for (int i=1; i<N; i++) {
		scanf("%d %d %lld", &u, &v, &d);
		adj[u].eb(v); adj[v].eb(u);
		dist[u].eb(d); dist[v].eb(d);
	}
	for (int i=2; i<=N; i++) scanf("%lld %lld", &S[i], &V[i]);
	int rt=new_node(); dfs(1, 0, rt);
	for (int i=2; i<=N; i++) printf("%lld ", T[i]); puts("");
	return 0;
}