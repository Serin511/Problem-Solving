#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair<int, int> pii;

int F, K, MOD, H[1<<19], I[1<<19];
pii A[1<<19], MX[1<<19];

int mul(int a, int b) { return a*b%MOD; }
int sum(int a, int b) { return (a+b)%MOD; }

struct Seg {
	int S[1<<20];
	void upd(int i, int s, int e, int t) {
		if (s==e) { S[i]=sum(S[i], 1); return ; }
		int md=(s+e)/2;
		if (t<=md) upd(i*2, s, md, t);
		else upd(i*2+1, md+1, e, t);
		S[i]=mul(S[i*2], S[i*2+1]);
	}
	int get(int i, int s, int e, int ts, int te) {
		if (e<ts||te<s||te<ts) return 1;
		if (ts<=s&&e<=te) return S[i];
		int md=(s+e)/2;
		return mul(get(i*2, s, md, ts, te), get(i*2+1, md+1, e, ts, te));
	}
	void upd(int t) { upd(1, 1, K, t); }
	int get(int ts, int te) { return get(1, 1, K, ts, te); }
}ST;

int main() {
	scanf("%d %d %d", &F, &K, &MOD);
	for (int i=1; i<=F; i++)
		scanf("%d %d", &A[i].fi, &A[i].se), MX[A[i].se].fi=max(MX[A[i].se].fi, A[i].fi);
	fill(H+1, H+K+1, (1<<30));
	for (int i=1; i<=F; i++) if (MX[A[i].se].fi<A[i].fi*2) H[A[i].se]=min(H[A[i].se], A[i].fi);
	for (int i=1; i<=K; i++) MX[i].se=i;
	sort(MX+1, MX+K+1); sort(A+1, A+F+1);
	for (int i=1; i<=K; i++) I[MX[i].se]=i, ST.upd(i);
	int S=0;
	for (int i=1, j=1; i<=K; i++) {
		for (; j<=F&&A[j].fi*2<=MX[i].fi; j++) ST.upd(I[A[j].se]);
		int t=lower_bound(MX+1, MX+K+1, pii(H[MX[i].se]*2, 0))-MX;
		S=sum(S, sum(mul(ST.get(1, i-1), ST.get(i, i)-1), mul(ST.get(1, i-1), ST.get(i+1, t-1))));
	}
	printf("%d\n", S);
	return 0;
}