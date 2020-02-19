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

int N; ll H[100010], W[100010];

int main() {
	scanf("%d", &N);
	for (int i=1; i<=N; i++) scanf("%lld", &H[i]);
	for (int i=1; i<=N; i++) scanf("%lld", &W[i]), W[i]+=W[i-1];
	lct.init(N); lct.upd(1, line(-2*H[1], H[1]*H[1]-W[1]), 1, 1e6);
	for (int i=2; i<N; i++) 
		lct.upd(1, line(-2*H[i], 2*H[i]*H[i]-W[i]+W[i-1]+lct.get(1, H[i], 1, 1e6)), 1, 1e6);
	printf("%lld\n", lct.get(1, H[N], 1, 1e6)+H[N]*H[N]+W[N-1]);
	return 0;
}