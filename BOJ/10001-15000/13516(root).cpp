#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;

const int MX = 100005, B = 400;

int N, Q;
vector<int> adj[MX], na[MX];

int clr[MX], val[MX], chk[MX], vis[MX];
int pr[MX], mv[MX], tp;
int get(int x) { return pr[x]?(pr[x]=get(pr[x])):x; }
void Un(int x, int y) {
	x=get(x), y=get(y);
	if (x!=y) pr[y]=x, mv[x]=max(mv[x], mv[y]);
}

int dfs(int n) {
	vis[n]=tp; int r=mv[n];
	for (auto &i:na[n]) if (vis[i]!=tp&&clr[n]==clr[i]) r=max(r, dfs(i));
	return r;
}

int q[MX], u[MX], w[MX];
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N; for (int i=1, u, v; i<N; i++) cin>>u>>v, adj[u].eb(v), adj[v].eb(u);
	for (int i=1; i<=N; i++) cin>>clr[i];
	for (int i=1; i<=N; i++) cin>>val[i];
	cin>>Q; for (int i=0; i<Q; i++) { cin>>q[i]>>u[i]; if (q[i]==3) cin>>w[i]; }
	for (int s=0; s<Q; s+=B) {
		int e=min(s+B, Q)-1;

		for (int i=1; i<=N; i++) pr[i]=chk[i]=0, mv[i]=val[i], na[i].clear();
		for (int i=s; i<=e; i++) if (q[i]==1||q[i]==3) chk[u[i]]=1;
		for (int i=1; i<=N; i++) if (!chk[i]) for (auto &j:adj[i])
			if (!chk[j]&&clr[i]==clr[j]) Un(i, j);
		for (int i=1; i<=N; i++) for (auto &j:adj[i])
			if (get(i)!=get(j)) na[get(i)].eb(get(j));

		for (int i=s; i<=e; i++) {
			if (q[i]==1) clr[u[i]]=1-clr[u[i]];
			if (q[i]==2) ++tp, cout<<dfs(get(u[i]))<<'\n';
			if (q[i]==3) mv[u[i]]=val[u[i]]=w[i];
		}
	}
	return 0;
}