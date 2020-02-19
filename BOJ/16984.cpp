#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define sq(X) ((X)*(X))
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

int st[200010], sum;
void ins(int i, int t) {
	if (!st[i]) sum++;
	st[i]+=t;
	if (!st[i]) sum--;
}

int N, M, C[200010], D[200010], E[200010], chk[200010], A[200010];
vim adj[200010], dia, V[200010];

struct Seg {
	int ar[1<<19], fl[1<<19];
	void init1(int i, int s, int e, int t) {
		if (s==e) { ar[i]=s; return ; }
		int md=(s+e)/2;
		if (t<=md) init1(i*2, s, md, t);
		else init1(i*2+1, md+1, e, t);
		ar[i]=max(ar[i*2], ar[i*2+1]);
	}
	void init() {
		memset(ar, 0, sizeof(ar));
		memset(fl, 0, sizeof(fl));
		for (int i=1; i<=M; i++) init1(1, 1, M, i);
	}
	void upd(int i, int s, int e, int ts, int te, int v) {
		if (te<s||e<ts||te<ts) return ;
		if (ts<=s&&e<=te) {
			fl[i]+=v;
			if (fl[i]) ar[i]=0;
			else ar[i]=(s==e?s:max(ar[i*2], ar[i*2+1]));
			return ;
		}
		int md=(s+e)/2;
		upd(i*2, s, md, ts, te, v); upd(i*2+1, md+1, e, ts, te, v);
		ar[i]=fl[i]?0:max(ar[i*2], ar[i*2+1]);
	}
	int get(int i, int s, int e, int ts, int te) {
		if (te<s||e<ts||te<ts||!ar[i]) return 0;
		if (ts<=s&&e<=te) return ar[i];
		int md=(s+e)/2;
		return max(get(i*2, s, md, ts, te), get(i*2+1, md+1, e, ts, te));
	}
}S;

void dfs1(int now, int par) {
	D[now]=D[par]+1;
	for (auto &i:adj[now]) if (i!=par) dfs1(i, now);
}

void dfs2(int now) {
	dia.eb(now);
	for (auto &i:adj[now]) if (D[i]==D[now]-1) dfs2(i);
}

void dfs3(int now, int par, int lev) {
	V[lev].eb(now);
	for (auto &i:adj[now]) if (i!=par) dfs3(i, now, lev+1);
}

void dfs4(int now, int par, int lev) {
	D[now]=E[now]=lev;
	for (auto &i:adj[now]) if (i!=par&&!chk[i]) dfs4(i, now, lev-1), E[now]=min(E[now], E[i]);
}

void dfs5(int now, int par, int tp) {
	vim use;
	while (tp>2*D[now]-E[now]) {
		if (S.get(1, 1, M, tp, tp)==tp && V[tp].size()==1) { use.eb(V[tp][0]), ins(C[V[tp][0]], 1); }
		tp=S.get(1, 1, M, 1, tp-1);
	}
	A[now]=sum;
	V[D[now]].eb(now);
	for (auto &i:adj[now]) if (i!=par&&!chk[i]) S.upd(1, 1, M, D[now]+1, 2*D[now]-E[i], 1);
	for (auto &i:adj[now]) if (i!=par&&!chk[i]) {
		S.upd(1, 1, M, D[now]+1, 2*D[now]-E[i], -1);
		dfs5(i, now, tp);
		S.upd(1, 1, M, D[now]+1, 2*D[now]-E[i], 1);
	}
	for (auto &i:adj[now]) if (i!=par&&!chk[i]) S.upd(1, 1, M, D[now]+1, 2*D[now]-E[i], -1);
	for (auto &i:use) ins(C[i], -1);
	V[D[now]].pop_back();
}

void solve(int st, int lst) {
	S.init();
	for (int i=1; i<=N; i++) V[i].clear();
	dfs3(lst, st, M/2+1);
	memset(chk, 0, sizeof(chk)); chk[lst]=1;
	dfs4(st, 0, M/2), dfs5(st, 0, M);
}

void solve1(int st, vim lst) {
	S.init(); S.upd(1, 1, M, M/2+2, M, 1);
	for (int i=1; i<=N; i++) V[i].clear();
	memset(chk, 0, sizeof(chk)); for (auto &i:lst) chk[i]=1;
	dfs4(st, 0, M/2+1), dfs5(st, 0, M/2+1);
}

int main() {
	int im;
	scanf("%d %d", &N, &im);
	for (int i=1, u, v; i<N; i++) scanf("%d %d", &u, &v), adj[u].eb(v), adj[v].eb(u);

	for (int i=1; i<=N; i++) scanf("%d", &C[i]);
	dfs1(1, 0);
	int mx=0; for (int i=1; i<=N; i++) mx=max(mx, D[i]);
	dia.eb(0);
	for (int i=1; i<=N; i++) if (mx==D[i]) {
		memset(D, 0, sizeof(D));
		dfs1(i, 0);
		mx=0;
		for (int j=1; j<=N; j++) mx=max(mx, D[j]);
		for (int j=1; j<=N; j++) if (mx==D[j]) { dfs2(j); break; }
		break;
	}
	
	M=dia.size()-1;
	solve(dia[M/2], dia[M/2+1]);
	solve(dia[M+1-M/2], dia[M-M/2]);
	if (M%2) solve1(dia[(M+1)/2], {dia[(M+1)/2+1], dia[(M+1)/2-1]});
	for (int i=1; i<=N; i++) printf("%d\n", A[i]);
	return 0;
}