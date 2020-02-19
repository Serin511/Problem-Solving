#include <bits/stdc++.h>
#define fi first
#define se second
#define ryan bear
#define sq(X) ((X)*(X))
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef unsigned ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

const int MAXN = 500010;

struct seg {
	unsigned ar[(1<<20)], lz1[(1<<20)], lz2[(1<<20)];
	void init() { fill(lz2, lz2+(1<<20), 1); }
	inline void spread(int i, int s, int e) {
		ar[i]=(ar[i]*lz2[i]+lz1[i]*(e-s+1));
		if (i<(1<<19)) {
			lz1[i*2]=(lz1[i*2]*lz2[i]+lz1[i]);
			lz2[i*2]=lz2[i*2]*lz2[i];
			lz1[i*2+1]=(lz1[i*2+1]*lz2[i]+lz1[i]);
			lz2[i*2+1]=lz2[i*2+1]*lz2[i];
		}
		lz1[i]=0; lz2[i]=1;
	}
	inline void lazy_1(int i, int s, int e, int ts, int te, ll V) {
		spread(i, s, e);
		if (te<ts||e<ts||te<s) return ;
		if (ts<=s&&e<=te) {
			lz1[i]=(lz1[i]+V);
			spread(i, s, e);
			return ;
		}
		int md=(s+e)/2;
		lazy_1(i*2, s, md, ts, te, V);
		lazy_1(i*2+1, md+1, e, ts, te, V);
		ar[i]=(ar[i*2]+ar[i*2+1]);
	}
	inline void lazy_2(int i, int s, int e, int ts, int te, ll V) {
		spread(i, s, e);
		if (te<ts||e<ts||te<s) return ;
		if (ts<=s&&e<=te) {
			lz1[i]=(lz1[i]*V); lz2[i]=(lz2[i]*V);
			spread(i, s, e);
			return ;
		}
		int md=(s+e)/2;
		lazy_2(i*2, s, md, ts, te, V);
		lazy_2(i*2+1, md+1, e, ts, te, V);
		ar[i]=(ar[i*2]+ar[i*2+1]);
	}
	inline ll get(int i, int s, int e, int ts, int te) {
		if (te<ts||e<ts||te<s) return 0;
		spread(i, s, e);
		if (ts<=s&&e<=te) return ar[i];
		int md=(s+e)/2;
		return (get(i*2, s, md, ts, te)+get(i*2+1, md+1, e, ts, te));
	}
}S;

int N, Q;
vim adj[MAXN], ch[MAXN]; 
int sub_size[MAXN];
int in[MAXN], out[MAXN], dep[MAXN], tp;
int hld[MAXN], hld_p[MAXN], hld_c=1;
vim spt[MAXN];

int lca(int a, int b) {
	if (dep[a]>dep[b]) swap(a, b);
	int dif=dep[b]-dep[a];
	for (int i=20; i>=0; i--) if (dif&(1<<i)) b=spt[b][i];
	if (a==b) return a;
	for (int i=spt[b].size()-1; i>=0; i--) if (i<spt[b].size() && spt[a][i]!=spt[b][i]) a=spt[a][i], b=spt[b][i];
	return spt[a][0];
}

int chk[MAXN];
void dfs1(int now) {
	chk[now]=1; sub_size[now]=1;
	for (int i:adj[now]) if (!chk[i]) {
		ch[now].eb(i); dfs1(i);
		sub_size[now]+=sub_size[i];
	}
}
void dfs2(int now, int par) {
	dep[now]=dep[par]+1;
	spt[now].eb(par);
	for (int i=1; (1<<i)<dep[now]; i++) spt[now].eb(spt[spt[now][i-1]][i-1]);
	for (int i:ch[now]) dfs2(i, now);
}
void dfs3(int now) {
	in[now]=++tp;
	for (int i:ch[now]) if (sub_size[i]*2>=sub_size[now]) {
		hld[i]=hld[now];
		dfs3(i);
		break;
	}
	for (int i:ch[now]) if (sub_size[i]*2<sub_size[now]) {
		++hld_c; hld[i]=hld_c; hld_p[hld[i]]=i;
		dfs3(i);
	}
	out[now]=tp;
}

int main() {
	hld[1]=1; hld_p[1]=1; S.init();
	scanf("%d %d", &N, &Q);
	for (int i=1; i<N; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].eb(v); adj[v].eb(u);
	}
	dfs1(1); dfs2(1, 0); dfs3(1);
	while (Q--) {
		int q, X, Y, V;
		scanf("%d", &q);
		if (q==1) {
			scanf("%d %d", &X, &V);
			S.lazy_1(1, 1, N, in[X], out[X], V);
		}
		if (q==2) {
			scanf("%d %d %d", &X, &Y, &V);
			int L=lca(X, Y);
			while (hld[L]!=hld[X]) {
				S.lazy_1(1, 1, N, in[hld_p[hld[X]]], in[X], V);
				X=spt[hld_p[hld[X]]][0];
			}
			while (hld[L]!=hld[Y]) {
				S.lazy_1(1, 1, N, in[hld_p[hld[Y]]], in[Y], V);
				Y=spt[hld_p[hld[Y]]][0];
			}
			S.lazy_1(1, 1, N, in[L], in[X], V);
			S.lazy_1(1, 1, N, in[L]+1, in[Y], V);
		}
		if (q==3) {
			scanf("%d %d", &X, &V);
			S.lazy_2(1, 1, N, in[X], out[X], V);
		}
		if (q==4) {
			scanf("%d %d %d", &X, &Y, &V);
			int L=lca(X, Y);
			while (hld[L]!=hld[X]) {
				S.lazy_2(1, 1, N, in[hld_p[hld[X]]], in[X], V);
				X=spt[hld_p[hld[X]]][0];
			}
			while (hld[L]!=hld[Y]) {
				S.lazy_2(1, 1, N, in[hld_p[hld[Y]]], in[Y], V);
				Y=spt[hld_p[hld[Y]]][0];
			}
			S.lazy_2(1, 1, N, in[L], in[X], V);
			S.lazy_2(1, 1, N, in[L]+1, in[Y], V);
		}
		if (q==5) {
			scanf("%d", &X);
			printf("%lld\n", S.get(1, 1, N, in[X], out[X]));
		}
		if (q==6) {
			scanf("%d %d", &X, &Y);
			int L=lca(X, Y); ll ans=0;
			while (hld[L]!=hld[X]) {
				ans+=S.get(1, 1, N, in[hld_p[hld[X]]], in[X]);
				X=spt[hld_p[hld[X]]][0];
			}
			while (hld[L]!=hld[Y]) {
				ans+=S.get(1, 1, N, in[hld_p[hld[Y]]], in[Y]);
				Y=spt[hld_p[hld[Y]]][0];
			}
			ans+=S.get(1, 1, N, in[L], in[X]);
			ans+=S.get(1, 1, N, in[L]+1, in[Y]);
			printf("%lld\n", ans);
		}
	}
	return 0;
}