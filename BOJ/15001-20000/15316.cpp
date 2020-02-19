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
int a[200010], b[200010], on[200010], ans[200010];
int q[200010], x[200010], y[200010];

vim V[(1<<19)]; vector<pii> s1[(1<<19)]; vim s2[(1<<19)];
void spread(int i, int s, int e, int ts, int te, int val) {
	if (te<s||e<ts) return ;
	if (ts<=s&&e<=te) { V[i].eb(val); return ; }
	int md=(s+e)/2;
	spread(i*2, s, md, ts, te, val); spread(i*2+1, md+1, e, ts, te, val);
}

int par[(1<<18)], rnk[(1<<18)];
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
	if (s==e) { ans[s]=(get(x[s])==get(y[s])?1:0); dissolve(i); return ; }
	int md=(s+e)/2;
	solve(i*2, s, md); solve(i*2+1, md+1, e);
	dissolve(i);
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i=1; i<=M; i++) scanf("%d %d", &a[i], &b[i]);
	for (int i=1; i<=M; i++) scanf("%d", &on[i]);
	int Q; scanf("%d", &Q);
	for (int i=1; i<=Q; i++) {
		scanf("%d", &q[i]);
		if (q[i]==1) {
			scanf("%d", &x[i]);
			if (on[x[i]]) spread(1, 1, Q, on[x[i]], i, x[i]), on[x[i]]=0;
			else on[x[i]]=i;
		}
		if (q[i]==2) scanf("%d %d", &x[i], &y[i]);
	}
	for (int i=1; i<=M; i++) if (on[i]) spread(1, 1, Q, on[i], Q, i);
	solve(1, 1, Q);
	for (int i=1; i<=Q; i++) if (q[i]==2) printf("%s\n", ans[i]?"YES":"NO");
	return 0;
}