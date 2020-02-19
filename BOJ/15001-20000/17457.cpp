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
}st[(1<<23)]; int nd_tp=1;
int new_node() { return nd_tp++; }

void upd(int now, int ref, line v, ll s, ll e, ll ts, ll te) {
	if (te<s||e<ts||e<s) return ;
	if (!(ts<=s&&e<=te)) {
		ll md=(s+e)/2;
		st[now].L=st[ref].L;
		if (ts<=md) {
			st[now].l=new_node();
			upd(st[now].l, st[ref].l, v, s, md, ts, te);
		}
		else st[now].l=st[ref].l;
		if (md+1<=te) {
			st[now].r=new_node();
			upd(st[now].r, st[ref].r, v, md+1, e, ts, te);
		}
		else st[now].r=st[ref].r;
		return ;
	}

	st[now].l = st[ref].l;
	st[now].r = st[ref].r;
	ll md=(s+e)/2;
	line lo=st[ref].L, hi=v;
	if (lo.get(s)<hi.get(s)) swap(lo, hi);
	if (lo.get(e)>=hi.get(e)) { st[now].L=hi; return ; }

	if (lo.get(md)<hi.get(md)) {
		st[now].L = lo;
		st[now].l = new_node();
		upd(st[now].l, st[ref].l, hi, s, md, ts, te);
	}
	else {
		st[now].L = hi;
		st[now].r = new_node();
		upd(st[now].r, st[ref].r, lo, md+1, e, ts, te);
	}
}

ll get(int now, ll x, ll s, ll e) {
	if (!now) return INF;
	ll md=(s+e)/2;
	if (x<=md) return min(st[now].L.get(x), get(st[now].l, x, s, md));
	else return min(st[now].L.get(x), get(st[now].r, x, md+1, e));
}

int N, Q;
ll A[80010], B[80010], C[80010];
vim adj[80010]; int chk[80010];
int rt[80010];

void dfs(int now, int nd) {
	chk[now]=1;
	rt[now]=new_node(); upd(rt[now], nd, line(B[now], A[now]), 0, MAX, 0, C[now]);
	for (int i:adj[now]) if (!chk[i]) dfs(i, rt[now]);
}

int main() {
	int V; ll T;
	scanf("%d %d", &N, &Q);
	for (int i=1; i<=N; i++) scanf("%lld", &A[i]);
	for (int i=1; i<=N; i++) scanf("%lld", &B[i]);
	for (int i=1; i<=N; i++) scanf("%lld", &C[i]);
	int u, v;
	for (int i=1; i<N; i++) {
		scanf("%d %d", &u, &v);
		adj[u].eb(v); adj[v].eb(u);
	}
	dfs(1, new_node());
	while (Q--) {
		scanf("%d %lld", &V, &T);
		printf("%lld\n", get(rt[V], T, 0, MAX));
	}
	return 0;
}