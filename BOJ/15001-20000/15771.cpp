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

int N; ll F[250010], C[250010], L[250010], D[250010];

int main() {
	scanf("%d", &N);
	for (int i=1; i<=N; i++) scanf("%lld", &F[i]);
	for (int i=1; i<=N; i++) scanf("%lld", &C[i]);
	for (int i=1; i<=N; i++) scanf("%lld", &L[i]);
	lct.init((1<<19));
	for (int i=N; i>=1; i--) {
		if (D[i+1]>=0) lct.upd(1, line(C[i], -i*C[i]+D[i+1]), 1, MAX, L[i]+i, MAX);
		D[i]=lct.get(1, F[i]+i, 1, MAX);
	}
	if (D[1]<0) puts("Impossible");
	else printf("%lld\n", D[1]);
	return 0;
}