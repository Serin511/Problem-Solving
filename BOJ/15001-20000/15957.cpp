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

struct node {
	int l, r;
	ll lz;
}st[(1<<23)]; int nd_tp=1;
inline int new_node() { return nd_tp++; }

int N, K, clr[100010], ord[100010], out[100010], rt[100010], ans[100010];
ll J; vim S[100010], adj[100010], cp, qn[100010];

int cnt;
void dfs(int now) {
	ord[now]=++cnt;
	for (auto &i:adj[now]) dfs(i);
	out[now]=cnt;
}

struct Query { int t, p; ll s; };
vector<Query> qu;

void upd(int now, int ref, int s, int e, int ts, int te, ll val) {
	st[now]=st[ref];
	if (ts<=s&&e<=te) { st[now].lz+=val; return ; }
	int md=(s+e)/2;
	if (ts<=md) {
		st[now].l=new_node();
		upd(st[now].l, st[ref].l, s, md, ts, te, val);
	}
	if (md+1<=te) {
		st[now].r=new_node();
		upd(st[now].r, st[ref].r, md+1, e, ts, te, val);
	}
}

ll get(int now, int s, int e, int t) {
	if (!now) return 0;
	if (s==e) return st[now].lz;
	int md=(s+e)/2;
	if (t<=md) return st[now].lz+get(st[now].l, s, md, t);
	else return st[now].lz+get(st[now].r, md+1, e, t);
}

int main() {
	scanf("%d %d %lld", &N, &K, &J);
	for (int i=2, u; i<=N; i++) scanf("%d", &u), adj[u].eb(i);
	for (int i=1; i<=N; i++) scanf("%d", &clr[i]), S[clr[i]].eb(i);
	dfs(1); qu.resize(K);
	for (auto &i:qu) scanf("%d %d %lld", &i.t, &i.p, &i.s), cp.eb(i.t);
	cp.eb(0); sort(all(cp)); unq(cp);
	for (int i=0; i<K; i++) qn[lower_bound(all(cp), qu[i].t)-cp.begin()].eb(i);

	for (int i=0; i<cp.size(); i++) {
		rt[i]=new_node();
		if (i) st[rt[i]]=st[rt[i-1]];
		for (auto &j:qn[i]) {
			int im=new_node();
			upd(im, rt[i], 1, N, ord[qu[j].p], out[qu[j].p], qu[j].s/(out[qu[j].p]-ord[qu[j].p]+1));
			rt[i]=im;
		}
	}
	for (int i=1; i<=N; i++) {
		if (!S[i].size()) continue;
		int s=0, e=cp.size()-1;
		while (s+1<e) {
			int md=(s+e+1)/2; ll sum=0;
			for (auto &j:S[i]) sum+=get(rt[md], 1, N, ord[j]);
			if (sum<=J*S[i].size()) s=md;
			else e=md;
		}
		ll sum=0;
		for (auto &j:S[i]) sum+=get(rt[e], 1, N, ord[j]);
		if (sum>J*S[i].size()) ans[i]=cp[e];
		else ans[i]=-1;
	}

	for (int i=1; i<=N; i++) printf("%d\n", ans[clr[i]]);
	return 0;
}