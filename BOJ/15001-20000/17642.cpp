#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
using namespace std;
typedef long long ll;

const int MX = 100005;

int N, Q, U[MX], V[MX], in[MX], out[MX];
ll W, C[MX];
vector<pair<int, ll> > adj[MX];

struct nd {
	ll lz, T[3][3];
	nd() { lz=0; memset(T, 0, sizeof(T)); }
	void sp() {
		T[0][0]+=lz; T[2][2]+=lz;
		T[0][1]-=lz; T[1][2]-=lz;
		T[1][1]-=2*lz;
	}
}St[1<<19];

nd operator +(nd n1, nd n2) {
	nd r;
	for (int i=0; i<3; i++) for (int j=i; j<3; j++) {
		r.T[i][j]=max(n1.T[i][j], n2.T[i][j]);
		for (int k=i; k<j; k++) r.T[i][j]=max(r.T[i][j], n1.T[i][k]+n2.T[k+1][j]);
	}
	return r;
}

void sp(int i) {
	St[i].sp(); ll x=St[i].lz; St[i].lz=0;
	if (i<(1<<18)) St[i*2].lz+=x, St[i*2+1].lz+=x;
}

void upd(int i, int s, int e, int ts, int te, ll v) {
	sp(i);
	if (e<ts||te<s) return ;
	if (ts<=s&&e<=te) { St[i].lz+=v; sp(i); return ; }
	int md=(s+e)/2;
	upd(i*2, s, md, ts, te, v); upd(i*2+1, md+1, e, ts, te, v);
	St[i]=St[i*2]+St[i*2+1];
}

int tp;
void dfs(int n, int p) {
	in[n]=++tp;
	for (auto &i:adj[n]) if (i.fi!=p) {
		upd(1, 1, 2*N, tp+1, 2*N, i.se);
		dfs(i.fi, n);
		upd(1, 1, 2*N, ++tp, 2*N, -i.se);
	}
	out[n]=tp;
}

int main() {
	cin.tie(0)->sync_with_stdio();
	cin>>N>>Q>>W;
	for (int i=0; i<N-1; i++) cin>>U[i]>>V[i]>>C[i], adj[U[i]].eb(V[i], C[i]), adj[V[i]].eb(U[i], C[i]);
	dfs(1, 0);
	ll lst=0;
	while (Q--) {
		int d; ll e; cin>>d>>e;
		d=(d+lst)%(N-1); e=(e+lst)%W;
		int l=max(in[U[d]], in[V[d]]), r=min(out[U[d]], out[V[d]]);
		upd(1, 1, 2*N, l, r, e-C[d]); C[d]=e;
		cout<<(lst=St[1].T[0][2])<<'\n';
	}
	return 0;
}