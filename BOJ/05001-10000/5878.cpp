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

struct SegTree {
	ll a1[(1<<18)], a2[(1<<18)], a3[(1<<18)];
	void init() { fill(a1, a1+(1<<18), (1ll<<60)); }
	void spread(int i) { a2[i*2]=max(a2[i*2], a2[i]); a2[i*2+1]=max(a2[i*2+1], a2[i]); a3[i]=max(a3[i], a1[i]+a2[i]); }
	void upd1(int i, int s, int e, int t, ll v) {
		spread(i);
		if (s==e) {
			a1[i]=v; a3[i]=a1[i]+a2[i];
			return ;
		}
		int md=(s+e)/2;
		if (t<=md) upd1(i*2, s, md, t, v);
		else upd1(i*2+1, md+1, e, t, v);
		a1[i]=min(a1[i*2], a1[i*2+1]);
		a3[i]=min(a3[i*2], a3[i*2+1]);
	}
	void upd2(int i, int s, int e, int ts, int te, ll v) {
		spread(i);
		if (e<s||e<ts||te<s||te<ts) return ;
		if (ts<=s&&e<=te) {
			a2[i]=v; a3[i]=a1[i]+a2[i];
			return ;
		}
		int md=(s+e)/2;
		upd2(i*2, s, md, ts, te, v); upd2(i*2+1, md+1, e, ts, te, v);
		a3[i]=min(a3[i*2], a3[i*2+1]);
	}
	ll get(int i, int s, int e, int ts, int te) {
		spread(i);
		if (e<s||e<ts||te<s||te<ts) return (1ll<<60);
		if (ts<=s&&e<=te) return a3[i];
		int md=(s+e)/2;
		return min(get(i*2, s, md, ts, te), get(i*2+1, md+1, e, ts, te));
	}
}S;

int N, L;
ll h[100010]; int w[100010], s=1, sum;
ll D[100010], s1[100010]; int s2[100010], tp;

int main() {
	scanf("%d %d", &N, &L);
	for (int i=1; i<=N; i++) scanf("%lld %d", &h[i], &w[i]);
	S.upd1(1, 1, N, 1, 0);
	s1[0]=(1<<30); tp=1;
	for (int i=1; i<=N; i++) {
		sum+=w[i];
		while (sum>L) sum-=w[s++];
		while (tp && s1[tp-1]<h[i]) tp--;
		S.upd2(1, 1, N, s2[tp-1]+1, i, h[i]);
		s1[tp]=h[i]; s2[tp]=i; tp++;
		D[i]=S.get(1, 1, N, s, i);
		S.upd1(1, 1, N, i+1, D[i]);
	}
	printf("%lld\n", D[N]);
	return 0;
}
