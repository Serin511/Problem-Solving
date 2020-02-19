#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define sq(X) ((X)*(X))
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

int N, M;
int q[100010], a[100010], b[100010], out[100010], ans[100010];
map<int, int> mp[100010];

vim V[(1<<18)]; vector<pii> s1[(1<<18)]; vim s2[(1<<18)];
void spread(int i, int s, int e, int ts, int te, int val) {
	if (te<s||e<ts) return ;
	if (ts<=s&&e<=te) { V[i].eb(val); return ; }
	int md=(s+e)/2;
	spread(i*2, s, md, ts, te, val); spread(i*2+1, md+1, e, ts, te, val);
}

int par[(1<<17)], rnk[(1<<17)];
int get(int u) { return par[u]?get(par[u]):u; }
void Union(int i, int u, int v) {
	u=get(u); v=get(v);
	if (u==v) return ;
	if (rnk[u]<rnk[v]) swap(u, v);
	s1[i].eb(u, rnk[u]); s2[i].eb(v);
	rnk[u]=max(rnk[u], rnk[v]+1); par[v]=u;
}
void dissolve(int i) {
	for (auto &j:s1[i]) rnk[j.fi]=j.se;
	for (auto &j:s2[i]) par[j]=0;
}
void solve(int i, int s, int e) {
	for (auto &j:V[i]) Union(i, a[j], b[j]);
	if (s==e) { ans[s]=(get(a[s])==get(b[s])?1:0); dissolve(i); return ; }
	int md=(s+e)/2;
	solve(i*2, s, md); solve(i*2+1, md+1, e);
	dissolve(i);
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i=1; i<=M; i++) {
		scanf("%d %d %d", &q[i], &a[i], &b[i]);
		if (q[i]==1) mp[a[i]][b[i]]=mp[b[i]][a[i]]=i;
		if (q[i]==2) out[mp[a[i]][b[i]]]=i;
	}
	for (int i=1; i<=M; i++) if (q[i]==1) {
		if (out[i]) spread(1, 1, M, i, out[i], i);
		else spread(1, 1, M, i, M, i);
	}
	solve(1, 1, M);
	for (int i=1; i<=M; i++) if (q[i]==3) printf("%d\n", ans[i]);
	return 0;
}