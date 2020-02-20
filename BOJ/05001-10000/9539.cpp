#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef vector<int> vim;
const ll INF = 1ll<<60;

struct node {
	int p, n; ll a, b;
	bool operator <(const node &r)const {
		bool i1=(a+b>=0), i2=(r.a+r.b>=0);
		if (i1&&i2) return tie(a, n)<tie(r.a, r.n);
		if (!i1&&!i2) return tie(b, n)<tie(r.b, r.n);
		return i2;
	}
}nd[200010];

struct UF {
	int p[200010];
	void init() { memset(p, 0, sizeof(p)); }
	int get(int x) { return p[x]?(p[x]=get(p[x])):x; }
	void Union(int x, int y) {
		x=get(x), y=get(y), p[y]=x;
	}
}U;

int T, N, t;
vim adj[200010];

void dfs(int n, int p) { nd[n].p=p; for (auto &i:adj[n]) if (i!=p) dfs(i, n); }

void solve() {
	U.init(); scanf("%d %d", &N, &t);
	for (int i=1; i<=N; i++) adj[i].clear(), nd[i].n=i;
	for (int i=1, a; i<=N; i++) scanf("%d", &a), (a>=0?nd[i].b:nd[i].a)=a, (a>=0?nd[i].a:nd[i].b)=0;
	for (int i=2, u, v; i<=N; i++) scanf("%d %d", &u, &v), adj[u].eb(v), adj[v].eb(u);
	nd[t].b=INF;
	dfs(1, 0);
	set<node> S; for (int i=2; i<=N; i++) S.em(nd[i]);
	while (!S.empty()) {
		auto k=*S.rbegin(); S.erase(k);
		auto p=U.get(k.p); U.Union(p, k.n); S.erase(nd[p]);
		ll x=min(nd[p].a, nd[p].a+nd[p].b+k.a), y=nd[p].a+nd[p].b+k.a+k.b-x;
		tie(nd[p].a, nd[p].b) = tie(x, y);
		if (p!=1) S.em(nd[p]);
	}
	printf("%s\n", nd[1].a<0?"trapped":"escaped");
}

int main() {
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}