#include <bits/stdc++.h>
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef vector<int> vim;
typedef pair<int, int> pii;

const int MX = 200005;

int N, M, Q, lev[MX], sz[MX], chk[MX], dep[MX], P[MX];
vim adj[MX], ca[MX], spt[MX];
vim st[MX], ds[MX]; unordered_map<int, vim> ch[MX];

pii dfs(int n, int p, int lv) {
	sz[n]=1; chk[n]=lv; pii r(0, 0);
	for (auto &i:adj[n]) if (i!=p) {
		if (lev[i]) r=max(r, pii(lev[i], i));
		else r=max(r, dfs(i, n, lv)), sz[n]+=sz[i];
	}
	return r;
}

int get_cent(int n, int p, int s) {
	for (auto &i:adj[n]) if (i!=p&&!lev[i]&&sz[i]>s) return get_cent(i, n, s);
	return n;
}

void cent(int lv) {
	for (int i=1; i<=N; i++) if (!lev[i]&&chk[i]!=lv) {
		int p=dfs(i, 0, lv).second;
		int c=get_cent(i, 0, sz[i]/2);
		lev[c]=lv; P[c]=p; ca[p].eb(c);
	}
	for (int i=1; i<=N; i++) if (!lev[i]) { cent(lv+1); break; }
}

void dfs(int n, int p) {
	dep[n]=dep[p]+1; spt[n].eb(p);
	for (int i=0; i<spt[spt[n][i]].size(); i++) spt[n].eb(spt[spt[n][i]][i]);
	for (auto &i:adj[n]) if (i!=p) dfs(i, n);
}

int dist(int a, int b) {
	if (dep[a]>dep[b]) swap(a, b);
	int r, t; r=t=dep[b]-dep[a];
	for (int i=20; i>=0; i--) if ((1<<i)&t) b=spt[b][i];
	if (a==b) return r;
	for (int i=spt[b].size()-1; i>=0; i--) 
		if (i<spt[b].size()&&spt[a][i]!=spt[b][i]) a=spt[a][i], b=spt[b][i], r+=(1<<i)*2;
	return r+2;
}

int kth(int n, int k) {
	for (int i=20; i>=0; i--) if ((1<<i)&k) n=spt[n][i];
	return n;
}

void dfs1(int n, int p) {
	if (n<=M) st[n].eb(n);
	for (auto &i:ca[n]) {
		dfs1(i, n);
		for (auto &j:st[i]) st[n].eb(j), ch[n][i].eb(dist(n, j));
		sort(all(ch[n][i]));
	}
	for (auto &i:st[n]) ds[n].eb(dist(n, i));
	sort(all(ds[n]));
}

struct node {
	int v, d;
	node(int V, int D) : v(V), d(D) {}
};

node operator + (const node n1, const node n2) {
	if (!n1.v) return n2;
	if (!n2.v) return n1;
	if (n1.v==-1||n2.v==-1) return node(-1, 0);
	int x=dist(n1.v, n2.v);
	if (x>n1.d+n2.d) return node(-1, 0);
	if (n1.d>=n2.d+x) return n2;
	if (n2.d>=n1.d+x) return n1;
	int d=(n1.d+x-n2.d)/2;
	if (dep[n1.v]-d<dep[n2.v]-(x-d)) return node(kth(n2.v, x-d), (n1.d+n2.d-x)/2);
	else return node(kth(n1.v, d), (n1.d+n2.d-x)/2);
}

int f(int v, int d) {
	if (v<=0) return 0;
	int r=0;
	for (int i=v, l=0; i; l=i, i=P[i]) {
		int dd=d-dist(i, v); if (dd<0) continue;
		r+=upper_bound(all(ds[i]), dd)-ds[i].begin();
		if (l) r-=upper_bound(all(ch[i][l]), dd)-ch[i][l].begin();
	}
	return r;
}

void sol() {
	int K; node A(0, 0);
	vector<node> V;
	cin>>K;
	for (int i=0, j, k; i<K; i++) cin>>j>>k, V.eb(j, 2*k), A=A+V.back();
	vector<node> l, r;
	l.eb(0, 0); for (int i=0; i<K-1; i++) l.eb(l.back()+V[i]);
	r.eb(0, 0); for (int i=K-1; i; i--) r.eb(r.back()+V[i]); reverse(all(r));
	for (int i=0; i<K; i++) l[i]=l[i]+r[i];
	long long X=0;
	for (auto &i:l) X+=f(i.v, i.d);
	X-=1ll*f(A.v, A.d)*(K-1);
	cout<<X<<'\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>M; N=M*2-1;
	for (int i=1, u, v; i<M; i++) cin>>u>>v,
		adj[u].eb(M+i), adj[M+i].eb(u),
		adj[v].eb(M+i), adj[M+i].eb(v);
	cent(1); dfs(1, 0); dfs1(ca[0].back(), 0);
	cin>>Q;
	while (Q--) sol();
	return 0;
}