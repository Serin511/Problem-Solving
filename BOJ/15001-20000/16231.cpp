#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef __int128 LL;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;

const ll INF = 2e15;
const int XX = 200005;

int N, Y, K, sz[XX], ar[XX], ans[XX], P[XX], rt[XX];
ll M, C[XX], D[XX];
vector<pii> adj[XX];
vector<ll> cp;

map<int, priority_queue<ll> > mp[XX];
multiset<pli> pq[XX];

struct node {
	LL val;
	int cnt, l, r;
}st[1<<24];
int nd_tp=1;
#define new_node nd_tp++

int Find(ll x) { return lower_bound(cp.begin(), cp.end(), x)-cp.begin()+1; }

void upd(int i, ll s, ll e, ll t, int v) {
	if (s==e) { st[i].val+=cp[s-1]*v, st[i].cnt+=v; return ; }
	ll md=(s+e)/2;
	if (t<=md) {
		if (!st[i].l) st[i].l=new_node;
		upd(st[i].l, s, md, t, v);
	}else {
		if (!st[i].r) st[i].r=new_node;
		upd(st[i].r, md+1, e, t, v);
	}
	st[i].cnt=st[st[i].l].cnt+st[st[i].r].cnt;
	st[i].val=st[st[i].l].val+st[st[i].r].val;
}
int get(int i, ll s, ll e, ll X, LL U) {
	if (!i) return 0;
	if (s==e) return min((LL)st[i].cnt, U/(cp[s-1]-X));
	ll md=(s+e)/2;
	if (U>st[st[i].l].val-(LL)st[st[i].l].cnt*X)
		return st[st[i].l].cnt+get(st[i].r, md+1, e, X, U-st[st[i].l].val+(LL)st[st[i].l].cnt*X);
	return get(st[i].l, s, md, X, U);
}

void Merge(int p, int u, int h) {
	if (sz[p]<sz[u])
		swap(rt[p], rt[u]), swap(pq[p], pq[u]), swap(mp[p], mp[u]);
	for (auto &i:pq[u]) {
		upd(rt[p], 1, Y, Find(i.fi), 1);
		pq[p].em(i); mp[p][i.se].em(i.fi);
		if (mp[p][i.se].size()>P[i.se])
			upd(rt[p], 1, Y, Find(mp[p][i.se].top()), -1),
			pq[p].erase(pq[p].find(pli(mp[p][i.se].top(), i.se))),
			mp[p][i.se].pop();
	}
}

void init(int n) {
	cp.eb(D[n]+C[ar[n]]);
	for (auto &i:adj[n]) D[i.fi]=D[n]+i.se, init(i.fi);
}

void dfs(int n) {
	rt[n]=new_node;
	upd(rt[n], 1, Y, Find(D[n]+C[ar[n]]), 1);
	pq[n].em(D[n]+C[ar[n]], ar[n]);
	mp[n][ar[n]].em(D[n]+C[ar[n]]);
	sz[n]=1;
	for (auto &i:adj[n]) {
		dfs(i.fi);
		Merge(n, i.fi, i.se);
		sz[n]+=sz[i.fi];
	}
	ans[n]=get(rt[n], 1, Y, D[n], M);
}

int main() {
	scanf("%d %d %lld", &N, &K, &M);
	for (int i=2, u, v; i<=N; i++) scanf("%d %d", &u, &v), adj[u].eb(i, v);
	for (int i=1; i<=N; i++) scanf("%d", &ar[i]);
	for (int i=1; i<=K; i++) scanf("%lld", &C[i]);
	for (int i=1; i<=K; i++) scanf("%d", &P[i]);
	init(1); sort(cp.begin(), cp.end()); cp.resize(unique(cp.begin(), cp.end())-cp.begin()); Y=cp.size();
	dfs(1);
	for (int i=1; i<=N; i++) printf("%d\n", ans[i]);
	return 0;
}