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
const int MAX = (1<<30);

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
		fill(all(l), 0); fill(all(r), 0); fill(all(L), line(0, -INF));
	}
	void upd(int now, line v, ll s, ll e) {
		ll md=(s+e)/2;
		line lo=L[now], hi=v;
		if (lo.get(s)>hi.get(s)) swap(lo, hi);
		if (lo.get(e)<=hi.get(e)) { L[now]=hi; return ; }

		if (lo.get(md)>=hi.get(md)) {
			L[now]=lo;
			if (!l[now]) l[now]=tp++;
			upd(l[now], hi, s, md);
		}
		else {
			L[now]=hi;
			if (!r[now]) r[now]=tp++;
			upd(r[now], lo, md+1, e);
		}
	}
	ll get(int now, ll x, ll s, ll e) {
		if (!now) return -INF;
		ll md=(s+e)/2;
		if (x<=md) return max(L[now].get(x), get(l[now], x, s, md));
		else return max(L[now].get(x), get(r[now], x, md+1, e));
	}
}lct;

typedef struct {
	ll Dt, P, R, G;
}dt;

int N; ll C, D, ans[100010];
dt mc[100010];

void solve(int M) {
	scanf("%d %lld %lld", &N, &C, &D); if (!N) exit(0);
	for (int i=0; i<N; i++) scanf("%lld %lld %lld %lld", &mc[i].Dt, &mc[i].P, &mc[i].R, &mc[i].G);
	sort(mc, mc+N, [](dt d1, dt d2){ return d1.Dt<d2.Dt; });
	
	lct.init(N); lct.upd(1, line(0, C), 1, MAX);
	for (int i=0; i<N; i++) {
		ans[i]=lct.get(1, mc[i].Dt, 1, MAX);
		if (ans[i]>=mc[i].P) lct.upd(1, line(mc[i].G, -mc[i].G*(1+mc[i].Dt)+mc[i].R-mc[i].P+ans[i]), 1, MAX);
	}
	printf("Case %d: %lld\n", M, lct.get(1, D+1, 1, MAX));
}

int main() {
	for (int i=1; ; i++) solve(i);
	return 0;
}