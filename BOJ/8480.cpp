#include <bits/stdc++.h>
#define eb emplace_back
#define new_node (nd_tp++)
using namespace std;
typedef long long ll;
typedef vector<int> vim;
const ll INF = (1ll<<60);
const ll MAX = 1e9;
const int SZ=(1<<21);

struct line {
	ll a, b;
	ll get(ll x) { return a*x+b; }
	line() { a=0, b=INF; }
	line(ll A, ll B) { a=A, b=B; }
};

int l[SZ], r[SZ]; line L[SZ];
int nd_tp=1, rt[(1<<18)];

void upd(int now, line v, ll s, ll e) {
	ll md=(s+e)/2;
	line lo=L[now], hi=v;
	if (lo.get(s)<hi.get(s)) swap(lo, hi);
	if (lo.get(e)>=hi.get(e)) { L[now]=hi; return ; }

	if (lo.get(md)<=hi.get(md)) {
		L[now]=lo;
		if (!l[now]) { l[now]=new_node; }
		upd(l[now], hi, s, md);
	}
	else {
		L[now]=hi;
		if (!r[now]) { r[now]=new_node; }
		upd(r[now], lo, md+1, e);
	}
}

ll get(int now, ll x, ll s, ll e) {
	if (!now) return INF;
	ll md=(s+e)/2;
	if (x<=md) return min(L[now].get(x), get(l[now], x, s, md));
	else return min(L[now].get(x), get(r[now], x, md+1, e));
}

int N, D;
ll S[100010], W[100010], A[100010], ub[100010];
line li[100010];

void spread(int i, int s, int e, int ts, int te, int v) {
	if (te<s||e<ts||te<ts) return ;
	if (ts<=s&&e<=te) { upd(rt[i], li[v], -MAX, MAX); return ; }
	int md=(s+e)/2;
	spread(i*2, s, md, ts, te, v); spread(i*2+1, md+1, e, ts, te, v);
}

void solve(int i, int s, int e) {
	if (s==e) {
		A[s]=INF;
		for (int j=i; j; j/=2) A[s]=min(A[s], get(rt[j], W[s], -MAX, MAX));
		A[s]+=W[s]*W[s];
		li[s] = line(-2*W[s], A[s]+W[s]*W[s]);
		if (s<N) spread(1, 1, N, s+1, ub[s], s);
		return ;
	}
	int md=(s+e)/2;
	solve(i*2, s, md); solve(i*2+1, md+1, e);
}

int main() {
	scanf("%d %d", &N, &D);
	for (int i=1; i<(1<<18); i++) rt[i]=new_node;
	for (int i=1; i<=N; i++) scanf("%lld %lld", &S[i], &W[i]), S[i]+=S[i-1], W[i]+=W[i-1];
	for (int i=0; i<N; i++) ub[i]=upper_bound(S+1, S+1+N, S[i]+D)-S-1;
	li[0]=line(0, 0);
	spread(1, 1, N, 1, ub[0], 0);
	solve(1, 1, N);
	printf("%lld\n", A[N]);
	return 0;
}