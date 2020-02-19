#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).resize(unique(all(V))-(V).begin())
using namespace std;
typedef pair<int, int> pii;

struct node {
	int V, lz, len, l, r, d; 
	node() : V(0), lz(0), len(0), l(0), r(0), d(0) {}
};

node operator +(node &n1, node &n2) {
	node ret; ret.len=n1.len+n2.len;
	int m;
	m=ret.V=min(n1.V, n2.V);
	if (n1.V==m) {
		ret.l=n1.l;
		if (n2.V==m&&n1.l==n1.len) ret.l+=n2.l;
	}
	if (n2.V==m) {
		ret.r=n2.r;
		if (n1.V==m&&n2.r==n2.len) ret.r+=n1.r;
	}
	if (n1.V==m) ret.d=max(ret.d, n1.d);
	if (n2.V==m) ret.d=max(ret.d, n2.d);
	if (n1.V==n2.V) ret.d=max(ret.d, n1.r+n2.l);
	return ret;
}

struct Seg {
	node st[1<<21];
	void init(int i, int s, int e) {
		if (s==e) { st[i].len=st[i].l=st[i].r=st[i].d=1; return ; }
		int md=(s+e)/2;
		init(i*2, s, md); init(i*2+1, md+1, e);
		st[i]=st[i*2]+st[i*2+1];
	}
	void spread(int i) {
		st[i].V+=st[i].lz;
		if (i<(1<<20)) st[i*2].lz+=st[i].lz, st[i*2+1].lz+=st[i].lz;
		st[i].lz=0;
	}
	void upd(int i, int s, int e, int ts, int te, int v) {
		spread(i);
		if (e<ts||te<s) return ;
		if (ts<=s&&e<=te) { st[i].lz+=v; spread(i); return ; }
		int md=(s+e)/2;
		upd(i*2, s, md, ts, te, v); upd(i*2+1, md+1, e, ts, te, v);
		st[i]=st[i*2]+st[i*2+1];
	}
	int get() {
		spread(1);
		if (st[1].V==0) return st[1].d;
		return 0;
	}
}S;

int M, N, P, X1[400010], X2[400010], Y1[400010], Y2[400010], B, C[400010];
vector<pii> in[1000010], out[1000010];

int main() {
	scanf("%d %d %d %d", &N, &M, &B, &P);
	for (int i=1; i<=P; i++)
		scanf("%d %d %d %d %d", &X1[i], &Y1[i], &X2[i], &Y2[i], &C[i]),
		in[Y1[i]].eb(X1[i], X2[i]),
		out[Y2[i]+1].eb(X1[i], X2[i]);
	S.init(1, 1, N);
	int mx=0;
	for (auto &i:in[1]) S.upd(1, 1, N, i.fi, i.se, 1);
	for (int i=1, j=2; i<=M; i++) {
		for (auto &k:out[i]) S.upd(1, 1, N, k.fi, k.se, -1);
		for (; j<=M&&j-i<=S.get(); j++) {
			mx=max(mx, j-i);
			for (auto &k:in[j]) S.upd(1, 1, N, k.fi, k.se, 1);
		}
		mx=max(mx, min(j-i, S.get()));
	}
	printf("%d\n", mx);
	return 0;
}