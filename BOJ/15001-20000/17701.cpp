#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF=(1<<30);

struct Seg {
	int ar[(1<<17)];
	void upd(int i, int s, int e, int t, int v) {
		if (s==e) { ar[i]=v; return ; }
		int md=(s+e)/2;
		if (t<=md) upd(i*2, s, md, t, v);
		else upd(i*2+1, md+1, e, t, v);
		ar[i]=max(ar[i*2], ar[i*2+1]);
	}
	int lo(int i, int s, int e, int t, int v) {
		if (t<=s||ar[i]<v) return INF;
		if (s==e) return s;
		int md=(s+e)/2, ret;
		ret=lo(i*2+1, md+1, e, t, v);
		if (ret<t) return ret;
		return lo(i*2, s, md, t, v);
	}
	int hi(int i, int s, int e, int t, int v) {
		if (e<=t||ar[i]<v) return -1;
		if (s==e) return s;
		int md=(s+e)/2, ret;
		ret=hi(i*2, s, md, t, v);
		if (ret>t) return ret;
		return hi(i*2+1, md+1, e, t, v);
	}
}S1, S2;

ll sol1(int u, int v);
ll sol2(int u, int v);

int H, W, Q, A[50010], B[50010];

int main() {
	scanf("%d %d %d", &H, &W, &Q);
	for (int i=1; i<=H; i++) scanf("%d", &A[i]), S1.upd(1, 1, H, i, A[i]);
	for (int i=1; i<=W; i++) scanf("%d", &B[i]), S2.upd(1, 1, W, i, B[i]);
	while (Q--) {
		int u, v; scanf("%d %d", &u, &v);
		printf("%lld\n", max(sol1(u, v), sol2(u, v)));
	}
	return 0;
}

ll hsh(int x, int y) { return x*50001ll+y; }
map<ll, ll> M1, M2;

ll sol1(int u, int v) {
	if (M1[hsh(u, v)]) return M1[hsh(u, v)];
	ll a1, a2; int im;
	im=S1.lo(1, 1, H, u, B[v]);
	a1=(im<u?sol2(im, v)+u-im:u-1);
	im=S1.hi(1, 1, H, u, B[v]);
	a2=(im>u?sol2(im, v)+im-u:H-u);
	return M1[hsh(u, v)]=max(a1, a2);
}

ll sol2(int u, int v) {
	if (M2[hsh(u, v)]) return M2[hsh(u, v)];
	ll a1, a2; int im;
	im=S2.lo(1, 1, W, v, A[u]);
	a1=(im<v?sol1(u, im)+v-im:v-1);
	im=S2.hi(1, 1, W, v, A[u]);
	a2=(im>v?sol1(u, im)+im-v:W-v);
	return M2[hsh(u, v)]=max(a1, a2);
}