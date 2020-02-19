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
		if (!now) return -INF;
		ll md=(s+e)/2;
		if (x<=md) return max(L[now].get(x), get(l[now], x, s, md));
		else return max(L[now].get(x), get(r[now], x, md+1, e));
	}
}lct;

int N; ll A[200010], B[200010], S[200010]; ll ans;

int main() {
	scanf("%d", &N); lct.init(N);
	for (int i=1; i<=N; i++) {
		scanf("%lld", &A[i]);
		B[i]=B[i-1]+A[i]*i;
		S[i]=S[i-1]+A[i];
	}
	for (int i=N; i>=1; i--) {
		lct.upd(1, line(-S[i], B[i]), 0, N);
		ans=max(ans, lct.get(1, i-1, 0, N)-B[i-1]+S[i-1]*(i-1));
	}
	printf("%lld\n", ans);
	return 0;
}