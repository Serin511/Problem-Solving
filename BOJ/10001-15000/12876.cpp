#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define sq(X) ((X)*(X))
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
const ll INF = (1ll<<60);
const ll MAX = 1e9;

struct line {
	ll a, b;
	ll get(ll x) { return a*x+b; }
	line() {}
	line(ll A, ll B) { a=A, b=B; }
};

struct node {
	int l, r;
	line L;
	node() { L=line(0, -INF); }
}st[(1<<22)]; int nd_tp=1;
int new_node() { return nd_tp++; }

void upd(int now, int ref, line v, ll s, ll e) {
	st[now].l = st[ref].l;
	st[now].r = st[ref].r;
	ll md=(s+e)/2;
	line lo=st[ref].L, hi=v;
	if (lo.get(s)>hi.get(s)) swap(lo, hi);
	if (lo.get(e)<=hi.get(e)) { st[now].L=hi; return ; }

	if (lo.get(md)>hi.get(md)) {
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
	if (!now) return -INF;
	ll md=(s+e)/2;
	if (x<=md) return max(st[now].L.get(x), get(st[now].l, x, s, md));
	else return max(st[now].L.get(x), get(st[now].r, x, md+1, e));
}

int N, out[300010], qu[300010];
ll a[300010], b[300010], ans[300010];
vim V[(1<<20)];

void spread(int i, int s, int e, int ts, int te, int val) {
	if (te<s||e<ts) return ;
	if (ts<=s&&e<=te) { V[i].eb(val); return ; }
	int md=(s+e)/2;
	spread(i*2, s, md, ts, te, val); spread(i*2+1, md+1, e, ts, te, val);
}

void solve(int i, int s, int e, int nd) {
	int now=nd;
	for (auto &j:V[i]) {
		int im=new_node();
		upd(im, now, line(a[j], b[j]), -MAX, MAX);
		now=im;
	}
	if (s==e) { ans[s]=get(now, a[s], -MAX, MAX); return ; }
	int md=(s+e)/2;
	solve(i*2, s, md, now); solve(i*2+1, md+1, e, now);
}

int main() {
	scanf("%d", &N);
	for (int i=1; i<=N; i++) {
		scanf("%d", &qu[i]);
		if (qu[i]==1) scanf("%lld %lld", &a[i], &b[i]);
		if (qu[i]==2) {
			int im; scanf("%d", &im);
			out[im]=i;
		}
		if (qu[i]==3) scanf("%lld", &a[i]);
	}
	for (int i=1; i<=N; i++) if (qu[i]==1) {
		if (!out[i]) spread(1, 1, N, i, N, i);
		else spread(1, 1, N, i, out[i], i);
	}
	solve(1, 1, N, new_node());
	for (int i=1; i<=N; i++) if (qu[i]==3) {
		if (ans[i]==-INF) puts("EMPTY");
		else printf("%lld\n", ans[i]);
	}
	return 0;
}