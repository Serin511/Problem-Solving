#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MX = 100005;

struct UF {
	int pr[MX];
	void init(int X) { fill(pr, pr+X+1, 0); }
	int gp(int x) { return pr[x]?(pr[x]=gp(pr[x])):x; }
	bool Un(int x, int y) {
		x=gp(x), y=gp(y);
		if (x!=y) pr[y]=x;
		return x!=y;
	}
}U;

int N, M, K, T, in[MX], chk[50], D[50], P[50], Mn[50];
ll C[MX], sz[50], Pp[50], A;
vector<pair<int, pii> > Ei, Eu, Ep, Eq;
vector<pii> New, adj[50]; vector<int> im[MX];

void dfs1(int n, int m) {
	in[n]=m; sz[m]+=C[n];
	for (auto &i:im[n]) if (!in[i]) dfs1(i, m);
}

void dfs2(int n, int p) {
	Pp[n]=sz[n], D[n]=D[p]+1, P[n]=p;
	for (auto &i:adj[n]) if (i.fi!=p)
		chk[i.fi]=i.se, dfs2(i.fi, n), Pp[n]+=Pp[i.fi];
}

void cpr() {
	U.init(N);
	for (auto &i:New) U.Un(i.fi, i.se);
	for (auto &i:Eu) {
		if (U.Un(i.se.fi, i.se.se)) im[i.se.fi].eb(i.se.se), im[i.se.se].eb(i.se.fi);
		else Ep.eb(i);
	}
	for (int i=1; i<=N; i++) if (!in[i]) dfs1(i, ++T);
	for (auto &i:New) i.fi=in[i.fi], i.se=in[i.se];
	for (auto &i:Ep) i.se.fi=in[i.se.fi], i.se.se=in[i.se.se];
}

void sol(int B) {
	U.init(T);
	for (int i=1; i<=T; i++) adj[i].clear(), Mn[i]=3<<29;
	for (int i=0; i<K; i++) if ((1<<i)&B) {
		if (!U.Un(New[i].fi, New[i].se)) return ;
		adj[New[i].fi].eb(New[i].se, 1), adj[New[i].se].eb(New[i].fi, 1);
	}
	Eq.clear();
	for (auto &i:Ep) {
		if (U.Un(i.se.fi, i.se.se))
			adj[i.se.fi].eb(i.se.se, 0), adj[i.se.se].eb(i.se.fi, 0);
		else Eq.eb(i);
	}
	dfs2(1, 0);
	for (auto &i:Eq) {
		int f, s; f=i.se.fi, s=i.se.se;
		if (D[f]>D[s]) swap(f, s);
		while (D[f]<D[s]) Mn[s]=min(Mn[s], i.fi), s=P[s];
		while (f!=s) Mn[f]=min(Mn[f], i.fi), Mn[s]=min(Mn[s], i.fi), f=P[f], s=P[s];
	}
	ll E=0; for (int i=1; i<=T; i++) if (chk[i]) E+=Pp[i]*Mn[i];
	A=max(A, E);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N>>M>>K; Ei.resize(M);
	for (auto &i:Ei) cin>>i.se.fi>>i.se.se>>i.fi; 
	sort(all(Ei));
	for (auto &i:Ei) if (U.Un(i.se.fi, i.se.se)) Eu.eb(i);
	New.resize(K); for (auto &i:New) cin>>i.fi>>i.se;
	for (int i=1; i<=N; i++) cin>>C[i]; cpr();
	for (int i=0; i<(1<<K); i++) sol(i);
	cout<<A<<'\n';
	return 0;
}