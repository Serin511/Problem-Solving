#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<ll, ll> pll;
const ll INF = (1ll<<60);

struct line {
	ll a, b;
	ll get(ll x) { return a*x+b; }
	db getd(db x) { return a*x+b; }
	line() { a=0, b=-INF; }
	line(ll A, ll B) { a=A, b=B; }
};

struct LiChao {
	ll l[50005], r[50005]; int tp; line L[50005];
	void init() {
		memset(l, 0, sizeof(l));
		memset(r, 0, sizeof(r));
		fill(L, L+50005, line()); tp=2;
	}
	int new_line() { return tp++; }
	void upd(int now, line v, ll s, ll e) {
		ll md=(s+e)/2;
		line lo=L[now], hi=v;
		if (lo.get(s)>hi.get(s)) swap(lo, hi);
		if (lo.get(e)<=hi.get(e)) { L[now]=hi; return ; }

		if (lo.get(md)>=hi.get(md)) {
			L[now]=lo;
			if (!l[now]) { l[now]=new_line(); }
			upd(l[now], hi, s, md);
		}
		else {
			L[now]=hi;
			if (!r[now]) { r[now]=new_line(); }
			upd(r[now], lo, md, e);
		}
	}
	double get(int now, db x, ll s, ll e) {
		if (!now) return -(double)INF;
		ll md=(s+e)/2;
		if (ceil(x)<=md) return max(L[now].getd(x), get(l[now], x, s, md));
		else return max(L[now].getd(x), get(r[now], x, md, e));
	}
}lct;

int N;
double D1[50010], D2[50010];
ll ST[50010], SP[50010];
pll C[50010];

int main() {
	scanf("%d", &N);
	for (int i=1; i<=N; i++) scanf("%lld %lld", &C[i].fi, &C[i].se);
	sort(C+1, C+1+N, [](pll &p1, pll &p2){ return p1.fi*p2.se<p1.se*p2.fi; });
	for (int i=N; i>1; i--) ST[i]=ST[i+1]+C[i].fi, SP[i]=SP[i+1]+C[i].se;
	lct.init();
	for (int i=1; i<N; i++)
		lct.upd(1, line(-C[i].se, C[i].fi), 0, 100000), D1[i]=lct.get(1, (double)ST[i+1]/SP[i+1], 0, 100000);
	lct.init();
	for (int i=N; i>1; i--)
		lct.upd(1, line(C[i].se, -C[i].fi), 0, 100000), D2[i-1]=-lct.get(1, (double)ST[i]/SP[i], 0, 100000);
	int c=0;
	for (int i=1; i<N; i++) if (D1[i]>D2[i]) c++;
	printf("%d\n", c);
	for (int i=1; i<N; i++) if (D1[i]>D2[i]) printf("%d\n", i);
	return 0;
}