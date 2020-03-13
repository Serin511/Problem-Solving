#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;
typedef vector<int> vim;

const int MX = 100005;

int N, M, Q, c, X[MX], Y[MX], Z[MX], lst[MX];
int in[MX], out[MX], chk[MX];
vim adj[MX], spt[MX];

int F[MX];
void upd(int t, int v) { while (t<=N) F[t]+=v, t+=t&-t; }
int get(int t) { int r=0; while (t) r+=F[t], t-=t&-t; return r; }

void dfs(int n, int p) {
	spt[n].eb(p); in[n]=++c;
	for (int i=0; i<spt[spt[n][i]].size(); i++) spt[n].eb(spt[spt[n][i]][i]);
	for (auto &i:adj[n]) if (i!=p) dfs(i, n);
	out[n]=c+1;
}

int gp(int t) {
	int x=get(in[t]);
	for (int i=20; i>=0; i--) if (i<spt[t].size()&&x==get(in[spt[t][i]])) t=spt[t][i];
	return t;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N>>M>>Q;
	for (int i=1; i<N; i++) cin>>X[i]>>Y[i], adj[X[i]].eb(Y[i]), adj[Y[i]].eb(X[i]);
	dfs(1, 0);
	for (int i=1; i<N; i++) if (spt[X[i]][0]==Y[i]) swap(X[i], Y[i]);
	for (int i=1; i<=N; i++) Z[i]=1, upd(in[i], 1), upd(out[i], -1);
	while (M--) {
		int d, p; cin>>d; p=gp(X[d]);
		if (chk[d]==0) {
			upd(in[Y[d]], -1); upd(out[Y[d]], 1);
			Z[p]+=Z[Y[d]]-lst[d];
		}
		if (chk[d]==1) {
			upd(in[Y[d]], 1); upd(out[Y[d]], -1);
			Z[Y[d]]=lst[d]=Z[p];
		}
		chk[d]=1-chk[d];
	}
	for (int i=1; i<=N; i++) Z[i]=Z[gp(i)];
	while (Q--) cin>>c, cout<<Z[c]<<'\n';
	return 0;
}