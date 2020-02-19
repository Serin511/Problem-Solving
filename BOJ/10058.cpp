#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
using namespace std;
typedef vector<int> vim;
typedef pair<int, int> pii;

int N, D, x[105], y[105];
vim adj[105]; int chk[105], con[105];

int dist(int a, int b) { return a*a+b*b; }
int ccw(int p, int q, int r) { return (x[q]-x[p])*(y[r]-y[p])-(y[q]-y[p])*(x[r]-x[p]); }

int dfs(int now) {
	if (chk[now]) return 0;
	chk[now]=1;
	for (auto &i:adj[now]) if (!con[i]||dfs(con[i])) { con[now]=i; con[i]=now; return 1; }
	return 0;
}

void dfs1(int now) {
	if (chk[now]) return ;
	chk[now]=1;
	for (auto &i:adj[now]) chk[i]=1, dfs1(con[i]);
}

void init() {
	for (int i=1; i<=N; i++) adj[i].clear();
	memset(con, 0, sizeof(con));
}

vim sol(int u, int v) {
	vim a, b, s, t;
	init(); int d=dist(x[u]-x[v], y[u]-y[v]);
	for (int i=1; i<=N; i++) if (i!=u&&i!=v&&dist(x[i]-x[u], y[i]-y[u])<=d && dist(x[i]-x[v], y[i]-y[v])<=d)
		(ccw(u, v, i)<0?s:t).eb(i);
	for (auto &i:s) for (auto &j:t) if (dist(x[i]-x[j], y[i]-y[j])>d) adj[i].eb(j);
	for (auto &i:s) { memset(chk, 0, sizeof(chk)); dfs(i); }
	memset(chk, 0, sizeof(chk));
	for (auto &i:s) if (!con[i]) dfs1(i);
	for (auto &i:s) if (chk[i]) a.eb(i);
	for (auto &i:t) if (!chk[i]) a.eb(i);
	a.eb(u); a.eb(v);
	return a;
}

int main() {
	vim a, r;
	scanf("%d %d", &N, &D);
	for (int i=1; i<=N; i++) scanf("%d %d", &x[i], &y[i]);
	for (int i=1; i<=N; i++) for (int j=i+1; j<=N; j++) if (dist(x[i]-x[j], y[i]-y[j])<=D*D) {
		r=sol(i, j);
		if (a.size()<r.size()) a=r;
	}
	if (a.size()==0) a.eb(1);
	printf("%d\n", a.size());
	sort(a.begin(), a.end());
	for (auto &i:a) printf("%d ", i); puts("");
	return 0;
}