#include <bits/stdc++.h>
#define mul(x, y) (1ll*x*y%MOD)
#define sum(x, y) ((1ll*x+y+MOD)%MOD)
#define eb emplace_back
using namespace std;

const int MOD = 1e9 + 7, MX = 300005;

int inv(int n) {
	int r=1;
	for (int i=30; i>=0; i--) {
		r=mul(r, r);
		if ((1<<i)&(MOD-2)) r=mul(r, n);
	}
	return r;
}

int N, K, im[MX], jm[MX];
vector<int> adj[MX];

struct dt {
	vector<int> V;
	int in, out, ss, m;
	dt() : V(2, 1), ss(2), m(1) {}
	int I(int i) {
		int r=V.size()-1-(i-in+1);
		if (r<0||r>=V.size()) return -1;
		return r;
	}
	int get(int i) {
		int r=I(i);
		if (r==-1) return 0;
		return V[r];
	}
	void upd(int i, int v) {
		int r=I(i);
		if (r==-1) return ;
		ss=sum(ss, v-V[r]); V[r]=v;
	}
}st[MX];

void merge(int p, int c) {
	st[c].upd(st[c].in+K+1, 0);
	st[p].upd(st[p].in-1, mul(st[p].get(st[p].in-1), mul(st[c].ss, st[c].m)));
	if (st[p].out<st[c].out) 
		st[c].in=st[p].in, swap(st[p].out, st[c].out),
		swap(st[p].V, st[c].V), swap(st[p].ss, st[c].ss), swap(st[p].m, st[c].m),
		st[p].V.eb(mul(st[c].get(st[p].in-1), mul(st[c].m, inv(st[p].m)))),
		st[p].upd(st[p].in+K+1, 0),
		st[p].ss+=st[p].V.back();

	if (st[c].out-st[p].in<=K/2) {
		im[st[p].in-1]=0, jm[st[p].in-1]=0;
		for (int i=st[p].in; i<=st[c].out; i++)
			im[i]=sum(im[i-1], mul(st[c].m, st[c].get(i))),
			jm[i]=sum(jm[i-1], st[p].get(i));

		int v=inv(im[st[c].out]);
		st[p].upd(st[p].in-1, mul(st[p].get(st[p].in-1), v));
		for (int i=min(st[p].out, st[p].in+K); i>=2*st[p].in+K-st[c].out; i--)
			st[p].upd(i, mul(mul(st[p].get(i), im[K-i+2*st[p].in]), v));
		for (int i=st[c].out; i>=st[p].in; i--)
			st[p].upd(i, mul(sum(mul(im[i], jm[i]), -mul(im[i-1], jm[i-1])), v));

		st[p].m=mul(st[p].m, im[st[c].out]);
		return ;
	}

	im[st[p].in-1]=0, jm[st[p].in-1]=0;
	for (int i=st[p].in; i<=st[p].out; i++)
		im[i]=sum(im[i-1], st[p].get(i)),
		jm[i]=sum(jm[i-1], mul(st[c].get(i), st[c].m));

	for (int i=st[p].out; i>=st[p].in; i--) {
		int x=im[i]-im[i-1], y=jm[i]-jm[i-1], z=im[min(i, (K+2*st[p].in-i))], w=jm[min(i, (K+2*st[p].in-i))];
		int r=sum(mul(x, w), mul(y, z));
		if (K+2*st[p].in>=2*i) r=sum(r, -mul(x, y));
		st[p].upd(i, r);
	}
}

void dfs(int n, int p) {
	st[n].in=st[n].out=st[p].in+1;
	for (auto &i:adj[n]) if (i!=p)
		dfs(i, n), merge(n, i);
	st[n].out=min(st[n].out, st[n].in+K);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N>>K; K--;
	for (int i=1, u, v; i<N; i++) cin>>u>>v, adj[u].eb(v), adj[v].eb(u);
	dfs(1, 0);
	cout<<mul(st[1].ss, st[1].m)<<'\n';
	return 0;
}