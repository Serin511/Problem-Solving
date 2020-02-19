#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef vector<int> vim;
#define new_line (nd_tp++)
const ll INF = (1ll<<60);

struct line {
	ll a, b;
	ll get(ll x) { return a*x+b; }
	line() { a=0, b=INF; }
	line(ll A, ll B) { a=A, b=B; }
};

int rt[200010], l[1<<21], r[1<<21], nd_tp=1; line L[1<<21];
int N, sz[200010]; vim adj[200010];
ll A[200010], C[200010], P[200010]; vector<line> V[200010];
void upd(int now, line v, ll s, ll e) {
	ll md=(s+e)/2;
	line lo=L[now], hi=v;
	if (lo.get(s)<hi.get(s)) swap(lo, hi);
	if (lo.get(e)>=hi.get(e)) { L[now]=hi; return ; }

	if (lo.get(md)<=hi.get(md)) {
		L[now]=lo;
		if (!l[now]) { l[now]=new_line; }
		upd(l[now], hi, s, md);
	}
	else {
		L[now]=hi;
		if (!r[now]) { r[now]=new_line; }
		upd(r[now], lo, md+1, e);
	}
}
ll get(int now, ll x, ll s, ll e) {
	if (!now) return INF;
	ll md=(s+e)/2;
	if (x<=md) return min(L[now].get(x), get(l[now], x, s, md));
	else return min(L[now].get(x), get(r[now], x, md+1, e));
}

void merge(int p, int v) {
	C[v]+=A[p]-get(rt[v], P[p], 1, 1000000)-C[v];
	if (sz[p]<sz[v]) swap(C[p], C[v]), swap(rt[p], rt[v]), swap(V[p], V[v]);
	for (auto &i:V[v]) V[p].eb(line(i.a, i.b+C[v]-C[p])), upd(rt[p], V[p].back(), 1, 1000000);
}

void dfs(int now) {
	rt[now]=new_line; sz[now]=1;
	for (auto &i:adj[now]) dfs(i), A[now]+=get(rt[i], P[now], 1, 1000000)+C[i];
	for (auto &i:adj[now]) merge(now, i), sz[now]+=sz[i];
	if (sz[now]==1) V[now].eb(line(P[now], 0)), upd(rt[now], V[now].back(), 1, 1000000);
}

int main() {
	scanf("%d", &N);
	for (int i=2, u; i<=N; i++) scanf("%d", &u), adj[u].eb(i);
	for (int i=1; i<=N; i++) scanf("%lld", &P[i]);
	dfs(1);
	printf("%lld\n", A[1]);
	return 0;
}