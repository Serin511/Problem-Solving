#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#define fi first
#define se second
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int INF=(1<<30);
int N, M, K; pii pi[200010];

struct node {
	int s, e; pii v;
}st[(1<<19)];

node operator +(const node &n1, const node &n2) {
	node ret;
	ret.s = n1.s<=n2.v.fi ? n2.s : n1.s<=n2.v.se ? n2.e : INF;
	ret.e = n1.e<=n2.v.fi ? n2.s : n1.e<=n2.v.se ? n2.e : INF;
	ret.v=n1.v;
	return ret;
}

void upd(int i, int s, int e, int t, pii v) {
	if (s==e) {
		st[i].s=v.fi, st[i].e=v.se, st[i].v=v;
		return ;
	}
	int md=(s+e)/2;
	if (t<=md) upd(i*2, s, md, t, v);
	else upd(i*2+1, md+1, e, t, v);
	st[i]=st[i*2]+st[i*2+1];
}

int main() {
	scanf("%d", &N);
	for (int i=1; i<=N; i++) {
		scanf("%d %d", &pi[i].fi, &pi[i].se);
		if (pi[i].fi>pi[i].se) swap(pi[i].fi, pi[i].se);
		upd(1, 1, N, i, pi[i]);
	}
	scanf("%d", &M);
	while (M--) {
		int u, v; scanf("%d %d", &u, &v);
		upd(1, 1, N, u, pi[v]); upd(1, 1, N, v, pi[u]); swap(pi[u], pi[v]);
		if (st[1].s==INF) puts("NIE");
		else puts("TAK");
	}
	return 0;
}