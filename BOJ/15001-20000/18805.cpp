#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
using namespace std;
typedef long long ll;

const int MX = 150005;
const ll INF = 10000000000000000ll;

int N, Q, U[MX], V[MX], in[MX], out[MX];
ll W, C[MX];
vector<pair<int, ll> > adj[MX];

struct ChildOnly {
	int in[1<<18], out[1<<18], ord[1<<18], tp; vector<int> spt[1<<18];
	ll mx[1<<19], lz[1<<19], H[1<<18]; int mxi[1<<19];
	ChildOnly() : tp(0) {}
	void init(int i, int s, int e) {
		if (s==e) { mx[i]=H[ord[s]], mxi[i]=ord[s]; return ; }
		int md=(s+e)/2; init(i*2, s, md); init(i*2+1, md+1, e);
		tie(mx[i], mxi[i])=max(tie(mx[i*2], mxi[i*2]), tie(mx[i*2+1], mxi[i*2+1]));
	}
	void dfs(int n, int p) {
		spt[n].eb(p);
		for (int i=0; i<spt[spt[n][i]].size(); i++) spt[n].eb(spt[spt[n][i]][i]);
		in[n]=++tp; ord[tp]=n;
		for (auto &i:adj[n]) if (i.fi!=p) {
			H[i.fi]=H[n]+i.se;
			dfs(i.fi, n);
		}out[n]=tp;
		if (n==1) init(1, 1, N);
	}
	void spread(int i) {
		mx[i]+=lz[i]; if (i<(1<<18)) lz[i*2]+=lz[i], lz[i*2+1]+=lz[i];
		lz[i]=0;
	}
	void upd(int i, int s, int e, int ts, int te, ll v) {
		spread(i);
		if (e<ts||te<s) return ;
		if (ts<=s&&e<=te) { lz[i]+=v; spread(i); return ; }
		int md=(s+e)/2;
		upd(i*2, s, md, ts, te, v); upd(i*2+1, md+1, e, ts, te, v);
		tie(mx[i], mxi[i])=max(tie(mx[i*2], mxi[i*2]), tie(mx[i*2+1], mxi[i*2+1]));
	}
	pair<ll, int> get(int i, int s, int e, int ts, int te) {
		spread(i);
		if (e<ts||te<s||te<ts) return {0, 0};
		if (ts<=s&&e<=te) return {mx[i], mxi[i]};
		int md=(s+e)/2;
		return max(get(i*2, s, md, ts, te), get(i*2+1, md+1, e, ts, te));
	}
	int gpd(int p, int n) {
		for (int i=spt[n].size()-1; i>=0; i--) if (i<spt[n].size()&&H[spt[n][i]]>H[p]) n=spt[n][i];
		return n;
	}
	ll getsub(int p) {
		auto k1=get(1, 1, N, in[p], in[p]), k2=get(1, 1, N, in[p], out[p]);
		if (k1.fi==k2.fi) return 0;
		int pd=gpd(p, k2.se);
		auto k3=max(get(1, 1, N, in[p], in[pd]-1), get(1, 1, N, out[pd]+1, out[p]));
		return k2.fi+k3.fi-2*k1.fi;
	}
}CO;

struct nd {
	ll lz, T[3][3];
	nd() { lz=0; memset(T, 0, sizeof(T)); }
	void sp() {
		T[0][0]+=lz; T[2][2]+=lz;
		T[0][1]-=lz; T[1][2]-=lz;
		T[1][1]-=2*lz;
	}
}St[1<<20];

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
	if (i<(1<<19)) St[i*2].lz+=x, St[i*2+1].lz+=x;
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
	cin>>N>>Q;
	for (int i=0; i<N-1; i++) cin>>U[i]>>V[i]>>C[i], adj[U[i]].eb(V[i], C[i]), adj[V[i]].eb(U[i], C[i]);
	CO.dfs(1, 0);
	dfs(1, 0);
	while (Q--) {
		int q, k, x;
		cin>>q;
		if (q==1) {
			cin>>k>>x; k--;
			int l=max(in[U[k]], in[V[k]]), r=min(out[U[k]], out[V[k]]);
			upd(1, 1, 2*N, l, r, x-C[k]);
			int p=(in[U[k]]<in[V[k]]?V[k]:U[k]);
			CO.upd(1, 1, N, CO.in[p], CO.out[p], x-C[k]);
			C[k]=x;
		}
		if (q==2) {
			cin>>k;
			upd(1, 1, 2*N, in[k], out[k], INF);
			cout<<max(St[1].T[0][2]-INF, CO.getsub(k))<<'\n';
			upd(1, 1, 2*N, in[k], out[k], -INF);
		}
	}
	return 0;
}