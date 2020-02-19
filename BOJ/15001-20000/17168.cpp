#include <bits/stdc++.h>
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

struct SegTree {
	ll st[(1<<20)], lz[(1<<20)];
	inline void spread(int i, int s, int e) {
		st[i]+=lz[i]*(e-s+1);
		if (i<(1<<19)) lz[i*2]+=lz[i], lz[i*2+1]+=lz[i];
		lz[i]=0;
	}
	inline void upd(int i, int s, int e, int ts, int te, ll V) {
		spread(i, s, e);
		if (te<s||e<ts||te<ts) return ;
		if (ts<=s&&e<=te) {
			lz[i]+=V;
			spread(i, s, e);
			return ;
		}
		int md=(s+e)/2;
		upd(i*2, s, md, ts, te, V); upd(i*2+1, md+1, e, ts, te, V);
		st[i]=st[i*2]+st[i*2+1];
	}
	inline ll get(int i, int s, int e, int t) {
		spread(i, s, e);
		if (s==e) return st[i];
		int md=(s+e)/2;
		if (t<=md) return get(i*2, s, md, t);
		else return get(i*2+1, md+1, e, t);
	}
}Sa, Sb;

struct line {
	ll a, b;
	ll get(ll x) { return a*x+b; }
	line() {}
	line(ll A, ll B) { a=A, b=B; }
};

struct LiChao {
	vim l, r; int tp;
	vector<line> L;
	void init(int SIZE) {
		l.resize(SIZE+10); r.resize(SIZE+10); L.resize(SIZE+10); tp=2;
		fill(all(l), 0); fill(all(r), 0); fill(all(L), line(0, INF));
	}
	void upd(int now, line v, ll s, ll e) {
		ll md=(s+e)/2;
		line lo=L[now], hi=v;
		if (lo.get(s)<hi.get(s)) swap(lo, hi);
		if (lo.get(e)>=hi.get(e)) { L[now]=hi; return ; }

		if (lo.get(md)<=hi.get(md)) {
			L[now]=lo;
			if (!l[now]) { l[now]=tp; tp++; }
			upd(l[now], hi, s, md);
		}
		else {
			L[now]=hi;
			if (!r[now]) { r[now]=tp; tp++; }
			upd(r[now], lo, md+1, e);
		}
	}
	ll get(int now, ll x, ll s, ll e) {
		if (!now) return INF;
		ll md=(s+e)/2;
		if (x<=md) return min(L[now].get(x), get(l[now], x, s, md));
		else return min(L[now].get(x), get(r[now], x, md+1, e));
	}
}lct;

int N, M;
vector<pll> B; vlm cp;
ll ans;

int Find(int x) { return lower_bound(all(cp), x)-cp.begin()+1; }

int main() {
	scanf("%d", &N); B.resize(N);
	for (auto &i:B) {
		scanf("%lld %lld", &i.fi, &i.se);
		if (i.fi<i.se) swap(i.fi, i.se);
		cp.eb(i.fi); cp.eb(i.se);
	}
	sort(all(cp)); unq(cp); M=cp.size();
	sort(all(B), [](pll p1, pll p2){ return p1.fi==p2.fi?p1.se>p2.se:p1.fi>p2.fi; });
	for (auto &i:B) {
		Sa.upd(1, 1, M, Find(i.se), M, i.fi);
		Sb.upd(1, 1, M, Find(i.se), M, -i.fi*i.se);
	}
	lct.init(N); lct.upd(1, line(B[0].fi, -B[0].fi*B[0].se), 1, cp.back()); ll mx=B[0].se;
	for (int i=1; i<N; i++) {
		if (mx>=B[i].fi) {
			ll a=Sa.get(1, 1, M, Find(B[i].fi))-B[i].fi, b=Sb.get(1, 1, M, Find(B[i].fi))+B[i].fi*B[i].se;
			ans=max(ans, a*B[i].fi+b);
		}
		else {
			ll a=Sa.get(1, 1, M, Find(B[i].fi))-B[i].fi, b=Sb.get(1, 1, M, Find(B[i].fi))+B[i].fi*B[i].se;
			ll im=lct.get(1, B[i].fi, 1, cp.back());
			ans=max(ans, a*B[i].fi+b-im);
			lct.upd(1, line(B[i].fi, -B[i].fi*B[i].se), 1, cp.back());
		}
		mx=max(mx, B[i].se);
	}
	printf("%lld\n", ans);
	return 0;
}