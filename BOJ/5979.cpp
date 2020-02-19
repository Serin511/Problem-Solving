#include <bits/stdc++.h>
#define eb emplace_back
#define sq(X) ((X)*(X))
using namespace std;
typedef long long ll;
typedef vector<int> vim;
#define new_line (nd_tp++)
const ll INF = (1ll<<60);
const ll MAX= (1<<30);

struct line {
	ll a, b;
	ll get(ll x) { return a*x+b; }
	line() { a=0, b=INF; }
	line(ll A, ll B) { a=A, b=B; }
};

int rt[50010], l[1<<21], r[1<<21], nd_tp=1; line L[1<<21];

int N, sz[50010]; vim adj[50010];
ll A[50010], C[50010], D[50010], S[50010], cnt[50010]; vector<line> V[50010];
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
	ll i1=get(rt[v], D[p], -MAX, MAX)+sq(D[p])+C[v], i2;
	if (!V[p].size()) {
		A[p]=S[p]=i1;
		swap(C[p], C[v]), swap(rt[p], rt[v]), swap(V[p], V[v]);
		return ;
	}

	C[v]+=S[p]; C[p]+=i1; i2=i1+S[p];
	if (sz[p]<sz[v]) swap(C[p], C[v]), swap(rt[p], rt[v]), swap(V[p], V[v]);

	ll mn=cnt[p]>2?A[p]+i1:INF;
	for (auto &i:V[v])
		mn=min(mn, i.get(D[p])+sq(D[p])-sq(i.a/2+D[p])+get(rt[p], 2*D[p]+i.a/2, -MAX, MAX)+sq(2*D[p]+i.a/2)+C[v]+C[p]-i2);
	A[p]=mn;

	for (auto &i:V[v]) V[p].eb(line(i.a, i.b+C[v]-C[p])), upd(rt[p], V[p].back(), -MAX, MAX);
	S[p]+=i1;
}

void dfs(int now, int par) {
	rt[now]=new_line; D[now]=D[par]+1; sz[now]=1;
	for (auto &i:adj[now]) if (i!=par)
		cnt[now]++, dfs(i, now), merge(now, i), sz[now]+=sz[i];
	if (adj[now].size()-(par==0?0:1)!=1) V[now].eb(line(-2*D[now], sq(D[now])+A[now]-C[now])), upd(rt[now], V[now].back(), -MAX, MAX);
	else A[now]=S[now];
}

int main() {
	scanf("%d", &N);
	for (int i=2, u, v; i<=N; i++) scanf("%d %d", &u, &v), adj[u].eb(v), adj[v].eb(u);
	dfs(1, 0);
	printf("%lld\n", A[1]);
	return 0;
}