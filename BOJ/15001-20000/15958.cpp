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
const ll MAX = 1e9;
const ll INF = (1ll<<60);

struct line {
	ll a, b;
	ll get(ll x) { return a*x+b; }
	line() { a=0, b=-INF; }
	line(ll A, ll B) { a=A, b=B; }
};

struct LiChao {
	vim l, r; int tp;
	vector<line> L;
	void init(int SIZE) {
		l.resize(SIZE+10); r.resize(SIZE+10); L.resize(SIZE+10); tp=2;
		fill(all(l), 0); fill(all(r), 0); fill(all(L), line(0, -INF));
	}
	void upd(int now, line v, ll s, ll e, ll ts, ll te) {
		if (te<s||e<ts||e<s) return ;
		if (!(ts<=s&&e<=te)) {
			ll md=(s+e)/2;
			if (ts<=md) {
				if (!l[now]) l[now]=tp++;
				upd(l[now], v, s, md, ts, te);
			}
			if (md+1<=te) {
				if (!r[now]) r[now]=tp++;
				upd(r[now], v, md+1, e, ts, te);
			}
			return ;
		}
		ll md=(s+e)/2;
		line lo=L[now], hi=v;
		if (lo.get(s)>hi.get(s)) swap(lo, hi);
		if (lo.get(e)<=hi.get(e)) { L[now]=hi; return ; }

		if (lo.get(md)>=hi.get(md)) {
			L[now]=lo;
			if (!l[now]) l[now]=tp++;
			upd(l[now], hi, s, md, ts, te);
		}
		else {
			L[now]=hi;
			if (!r[now]) r[now]=tp++;
			upd(r[now], lo, md+1, e, ts, te);
		}
	}
	ll get(int now, ll x, ll s, ll e) {
		if (!now) return -INF;
		ll md=(s+e)/2;
		if (x<=md) return max(L[now].get(x), get(l[now], x, s, md));
		else return max(L[now].get(x), get(r[now], x, md+1, e));
	}
}lct;

struct dt {
	ll x1, x2, y;
}L[500010];

pll P[500010];
ll s[500010], e[500010], ans;
int N, stk[500010], tp;

void solve() {
	lct.init((1<<23));
	int M=(N-2)/2;
	for (int i=1; i<=M; i++) L[i]={P[i*2-1].fi, P[i*2].fi, P[i*2].se};
	for (int i=1; i<=M; i++) {
		while (tp && L[stk[tp-1]].y>L[i].y) {
			e[stk[tp-1]]=L[i].x1;
			tp--;
		}
		s[i]=tp?L[stk[tp-1]].x2:0;
		stk[tp++]=i;
	}
	while (tp) {
		e[stk[tp-1]]=L[M].x2;
		tp--;
	}
	for (int i=1; i<=M; i++) {
		ans=max(ans, max(lct.get(1, s[i], 0, MAX), 0ll) + (e[i]-s[i])*L[i].y);
		lct.upd(1, line(L[i].y, -L[i].y*s[i]), 0, MAX, s[i], e[i]);
	}
}

int main() {
	scanf("%d", &N);
	for (int i=0; i<N; i++) scanf("%lld %lld", &P[i].fi, &P[i].se);
	solve();
	ll re=P[N-1].fi;
	for (int i=0; i<N; i++) P[i].fi=re-P[i].fi;
	reverse(P, P+N);
	solve();
	printf("%lld\n", ans);
	return 0;
}