#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).resize(unique(all(V))-(V).begin())
using namespace std;
typedef pair<int, int> pii;

const int MX = 1<<21;

struct Seg {
	int mn[MX], lz[MX], sz[MX], l[MX], r[MX], d[MX];
	void merge(int i, int s, int e) {
		mn[i]=min(mn[s], mn[e]); sz[i]=sz[s]+sz[e]; int m=mn[i];
		if (mn[s]==m) {
			l[i]=l[s];
			if (mn[e]==m&&l[s]==sz[s]) l[i]+=l[e];
		}else l[i]=0;
		if (mn[e]==m) {
			r[i]=r[e];
			if (mn[s]==m&&r[e]==sz[e]) r[i]+=r[s];
		}else r[i]=0;
		d[i]=0;
		if (mn[s]==m) d[i]=max(d[i], d[s]);
		if (mn[e]==m) d[i]=max(d[i], d[e]);
		if (mn[s]==mn[e]) d[i]=max(d[i], r[s]+l[e]);
	}
	void init(int i, int s, int e) {
		if (s==e) { sz[i]=l[i]=r[i]=d[i]=1; return ; }
		int md=(s+e)/2;
		init(i*2, s, md); init(i*2+1, md+1, e);
		merge(i, i*2, i*2+1);
	}
	void spread(int i) {
		mn[i]+=lz[i];
		if (i<(1<<20)) lz[i*2]+=lz[i], lz[i*2+1]+=lz[i];
		lz[i]=0;
	}
	void upd(int i, int s, int e, int ts, int te, int v) {
		spread(i);
		if (e<ts||te<s) return ;
		if (ts<=s&&e<=te) { lz[i]+=v; spread(i); return ; }
		int md=(s+e)/2;
		upd(i*2, s, md, ts, te, v); upd(i*2+1, md+1, e, ts, te, v);
		merge(i, i*2, i*2+1);
	}
	int get() { return mn[1]==0?d[1]:0; }
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