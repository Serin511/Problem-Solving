#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;

const int MX = 100005, INF = 1<<28;

struct node {
	int v[2][2];
	node() { for (int i=0; i<2; i++) v[i][i]=0, v[i][i^1]=INF; }
	node(int c, int d) { v[0][0]=c, v[0][1]=v[1][0]=INF, v[1][1]=d; }
};

node operator + (const node &n1, const node &n2) {
	node r;
	for (int i=0; i<2; i++) for (int j=0; j<2; j++) {
		r.v[i][j]=INF;
		for (int k=0; k<2; k++) for (int l=0; l<2; l++)
			r.v[i][j]=min(r.v[i][j], n1.v[i][k]+n2.v[l][j]+(k^l));
	}
	return r;
}

int N, Q, sz[MX];
int P[MX], C[MX], D[MX], T[MX];
int in[MX], out[MX], hld[MX], hla[MX];
vector<int> adj[MX];

node st[1<<18];
void upd(int i, int s, int e, int t, int c, int d) {
	if (s==e) { st[i]=node(c, d); return ; }
	int md=(s+e)/2;
	if (t<=md) upd(i*2, s, md, t, c, d);
	else upd(i*2+1, md+1, e, t, c, d);
	st[i]=st[i*2]+st[i*2+1];
}
node get(int i, int s, int e, int ts, int te) {
	if (e<ts||te<s) return node();
	if (ts<=s&&e<=te) return st[i];
	int md=(s+e)/2;
	return get(i*2, s, md, ts, te)+get(i*2+1, md+1, e, ts, te);
}

void dfs(int n, int p) {
	sz[n]=1; P[n]=p;
	for (auto &i:adj[n]) if (i!=p) dfs(i, n), sz[n]+=sz[i];
}
int t1, t2;
void bhld(int n, int p) {
	in[n]=++t1;
	if (!hld[n]) hld[n]=++t2, hla[n]=n;
	out[hld[n]]=max(out[hld[n]], in[n]);
	for (auto &i:adj[n]) if (i!=p&&sz[n]<sz[i]*2) hld[i]=hld[n], hla[i]=hla[n], bhld(i, n);
	for (auto &i:adj[n]) if (i!=p&&sz[n]>=sz[i]*2) bhld(i, n);
}

void upd(int v, int c, int d) {
	if (!v) return ;

	int hla=::hla[v], hlp=P[hla];
	node nd; int cc, dd;

	nd=get(1, 1, N, in[hla], out[hld[v]]);
	cc=min(nd.v[0][0], nd.v[0][1]), dd=min(nd.v[1][0], nd.v[1][1]);
	C[hlp]-=min(cc, dd+1), D[hlp]-=min(cc+1, dd);

	upd(1, 1, N, in[v], c, d);

	nd=get(1, 1, N, in[hla], out[hld[v]]);
	cc=min(nd.v[0][0], nd.v[0][1]), dd=min(nd.v[1][0], nd.v[1][1]);
	C[hlp]+=min(cc, dd+1), D[hlp]+=min(cc+1, dd);

	upd(hlp, T[hlp]&1?C[hlp]:INF, T[hlp]&2?D[hlp]:INF);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N;
	for (int i=1, u, v; i<N; i++) cin>>u>>v, adj[u].eb(v), adj[v].eb(u);
	dfs(1, 0); bhld(1, 0); fill(T+1, T+N+1, 3);
	cin>>Q; while (Q--) {
		int q, v; cin>>q>>v; T[v]=q;
		upd(v, q&1?C[v]:INF, q&2?D[v]:INF);

		node nd=get(1, 1, N, 1, out[1]);
		int c=min(nd.v[0][0], nd.v[0][1]), d=min(nd.v[1][0], nd.v[1][1]);
		cout<<min(T[1]&1?c:INF, T[1]&2?d:INF)<<'\n';
	}
	return 0;
}