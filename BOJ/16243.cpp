#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
using namespace std;
typedef vector<int> vim;
typedef pair<int, int> pii;

struct Edge {
	int u, v, c;
	Edge(int U, int V) : u(U), v(V), c(0) {}
};
vector<Edge> E;

int L, R, M, tp;

vector<pii> adj[200010]; int st[200010], dg[200010], chk[500010];
void dfs(int n, int D, vim &s, vim &e) {
	while (st[n]<adj[n].size()) {
		auto k=adj[n][st[n]++];
		if (chk[k.se]) continue; chk[k.se]=1;
		dg[n]--, dg[k.fi]--;
		(D%2?s:e).eb(k.se);
		dfs(k.fi, D+1, s, e);
		return ;
	}
}

void clear(vim &V) {
	for (auto &i:V)
		adj[E[i].u].clear(), adj[E[i].v].clear(),
		chk[i]=dg[E[i].u]=dg[E[i].v]=st[E[i].u]=st[E[i].v]=0;
}
void sol(vim &V) {
	bool im=false; vim v;
	for (auto &i:V) {
		auto &j=E[i];
		if (dg[j.u]||dg[j.v]) im=true;
		if (!dg[j.u]) v.eb(j.u);
		if (!dg[j.v]) v.eb(j.v);
		adj[j.u].eb(j.v, i), adj[j.v].eb(j.u, i);
		dg[j.u]++; dg[j.v]++;
	}
	if (!im) {
		++tp; for (auto &i:V) E[i].c=tp;
		clear(V); return ;
	}
	vim s, e;
	for (auto &i:v) if (dg[i]%2) dfs(i, 0, s, e);
	for (auto &i:v) while (dg[i]) dfs(i, 0, s, e);
	clear(V); sol(s); sol(e);
}

int main() {
	vim V;
	scanf("%d %d %d", &L, &R, &M);
	for (int i=0, u, v; i<M; i++) scanf("%d %d", &u, &v), E.eb(u, v+L), V.eb(i);
	sol(V);
	printf("%d\n", tp);
	for (auto &i:E) printf("%d\n", i.c);
	return 0;
}