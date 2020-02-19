#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
const ll INF = (1ll<<60);

struct line {
	ll a, b;
	line() : a(0), b(INF) {}
	line(ll A, ll B) : a(A), b(B) {}
	ll get(ll x) { return a*x+b; }
};

struct LiChao {
	int l[200010], r[200010], tp=2; line L[200010];
	int new_nd() { return tp++; }
	void upd(int i, ll s, ll e, line v) {
		line hi=v, lo=L[i];
		if (hi.get(s)>lo.get(s)) swap(hi, lo);
		if (hi.get(e)<=lo.get(e)) { L[i]=hi; return ; }
		ll md=(s+e)/2;
		if (hi.get(md)<=lo.get(md)) {
			L[i]=hi;
			if (!r[i]) r[i]=new_nd();
			upd(r[i], md+1, e, lo);
		}else {
			L[i]=lo;
			if (!l[i]) l[i]=new_nd();
			upd(l[i], s, md, hi);
		}
	}
	ll get(int i, ll s, ll e, ll x) {
		if (!i) return INF;
		ll md=(s+e)/2;
		if (x<=md) return min(L[i].get(x), get(l[i], s, md, x));
		else return min(L[i].get(x), get(r[i], md+1, e, x));
	}
}lct;

int N, M;
ll X, W, T, A[200010], C[200010];
pll S[200010], P[200010];

int main() {
	scanf("%lld %d %d %lld %lld", &X, &M, &N, &W, &T);
	for (int i=1; i<=M; i++) scanf("%lld", &S[i].se), S[i].fi=S[i].se%T;
	S[M+1]=pll(X%T, X); M++;
	for (int i=1; i<=N; i++) scanf("%lld %lld", &P[i].fi, &P[i].se);
	sort(P+1, P+N+1); reverse(P+1, P+N+1);
	sort(S+1, S+M+1); reverse(S+1, S+M+1);
	for (int i=1; i<=N; i++) C[i]=P[i].se+C[i-1];
	for (int i=1, j=1; i<=N; i++) {
		for (; j<=M&&P[i].fi<S[j].fi; j++) lct.upd(1, 1, N, line(W*(S[j].se/T), -W*(S[j].se/T)*(i-1)-C[i-1]+A[i-1]));
		A[i]=min(A[i-1]+W*((X+T-P[i].fi)/T), lct.get(1, 1, N, i)+C[i]);
	}
	printf("%lld\n", A[N]+W*(X/T+1));
	return 0;
}