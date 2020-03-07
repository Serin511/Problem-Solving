#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;

const int MX = 100005, B = 400;

int N, Q;
vector<int> adj[MX], na[MX];

int clr[MX], chk[MX], vis[MX];
int pr[MX], sz[MX], tp;
int get(int x) { return pr[x]?(pr[x]=get(pr[x])):x; }
void Un(int x, int y) {
	x=get(x), y=get(y);
	if (x!=y) pr[y]=x, sz[x]+=sz[y];
}

int dfs(int n) {
	vis[n]=tp; int r=sz[n];
	for (auto &i:na[n]) if (vis[i]!=tp&&clr[n]==clr[i]) r+=dfs(i);
	return r;
}

int q[MX], u[MX];
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N; for (int i=1, u, v; i<N; i++) cin>>u>>v, adj[u].eb(v), adj[v].eb(u);
	cin>>Q; for (int i=0; i<Q; i++) cin>>q[i]>>u[i];
	for (int s=0; s<Q; s+=B) {
		int e=min(s+B, Q)-1;

		for (int i=1; i<=N; i++) pr[i]=chk[i]=0, sz[i]=1, na[i].clear();
		for (int i=s; i<=e; i++) if (q[i]==1) chk[u[i]]=1;
		for (int i=1; i<=N; i++) if (!chk[i]) for (auto &j:adj[i])
			if (!chk[j]&&clr[i]==clr[j]) Un(i, j);
		for (int i=1; i<=N; i++) for (auto &j:adj[i])
			if (get(i)!=get(j)) na[get(i)].eb(get(j));

		for (int i=s; i<=e; i++) {
			if (q[i]==1) clr[u[i]]=1-clr[u[i]];
			if (q[i]==2) ++tp, cout<<dfs(get(u[i]))<<'\n';
		}
	}
	return 0;
}