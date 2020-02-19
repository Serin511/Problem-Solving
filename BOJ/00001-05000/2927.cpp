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

const int MAXN = 30010;

struct seg {
	int ar[(1<<20)];
	inline void upd(int i, int s, int e, int t, int val) {
		if (s==e) { ar[i]=val; return ; }
		int md=(s+e)/2;
		if (t<=md) upd(i*2, s, md, t, val);
		else upd(i*2+1, md+1, e, t, val);
		ar[i]=ar[i*2]+ar[i*2+1];
	}
	inline int get(int i, int s, int e, int ts, int te) {
		if (te<ts||e<ts||te<s) return 0;
		if (ts<=s&&e<=te) return ar[i];
		int md=(s+e)/2;
		return get(i*2, s, md, ts, te)+get(i*2+1, md+1, e, ts, te);
	}
}S;

int N, Q; int P[MAXN];
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

struct Query {
	int ty, a, b;
}qu[300010];

int par[MAXN];
int get(int x) { return par[x]?(par[x]=get(par[x])):x; }
bool Union(int x, int y) {
	x=get(x); y=get(y);
	if (x==y) return false;
	par[y]=x; return true;
}

int main() {
	hld[1]=1; hld_p[1]=1;
	scanf("%d", &N);
	for (int i=1; i<=N; i++) scanf("%d", &P[i]);
	scanf("%d", &Q);
	char im[15];
	for (int i=1; i<=Q; i++) {
		scanf("%s %d %d", im, &qu[i].a, &qu[i].b);
		if (im[0]=='b') {
			qu[i].ty=1;
			if (Union(qu[i].a, qu[i].b)) adj[qu[i].a].eb(qu[i].b), adj[qu[i].b].eb(qu[i].a); 
		}
		if (im[0]=='p') qu[i].ty=2;
		if (im[0]=='e') qu[i].ty=3;
	}
	for (int i=1; i<=N; i++) if (Union(1, i)) {
		adj[1].eb(i); adj[i].eb(1);
	}
	memset(par, 0, sizeof(par));
	hld[1]=hld_p[1]=1; dfs1(1); dfs2(1, 0); dfs3(1);
	for (int i=1; i<=N; i++) S.upd(1, 1, N, in[i], P[i]);
	for (int i=1; i<=Q; i++) {
		if (qu[i].ty==1) {
			if (Union(qu[i].a, qu[i].b)) puts("yes");
			else puts("no");
		}
		if (qu[i].ty==2) S.upd(1, 1, N, in[qu[i].a], qu[i].b);
		if (qu[i].ty==3) {
			int X=qu[i].a, Y=qu[i].b, L=lca(X, Y), ans=0;
			if (get(X)!=get(Y)) { puts("impossible"); continue; }
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
			printf("%d\n", ans);
		}
	}
	return 0;
}