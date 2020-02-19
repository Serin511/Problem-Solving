#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define sq(X) ((X)*(X))
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int INF=(1<<30);

int N, K;
vector<pii> adj[200010];
int fin[200010], sz[200010], im, ans;
set<pii> S;
pii vis[200010]; int tp;

void subsz(int now, int par) {
	sz[now]=1;
	for (auto &i:adj[now]) if (i.fi!=par&&!fin[i.fi]) {
		subsz(i.fi, now);
		sz[now]+=sz[i.fi];
	}
}

int get_cent(int now, int par) {
	for (auto &i:adj[now]) if (i.fi!=par&&!fin[i.fi]&&sz[i.fi]>=im/2) return get_cent(i.fi, now);
	return now;
}

void visit(int now, int par, int d, int dep) {
	vis[tp++]=pii(d, dep);
	for (auto &i:adj[now]) if (i.fi!=par&&!fin[i.fi]) visit(i.fi, now, d+i.se, dep+1);
}

void dfs(int now) {
	subsz(now, 0); im=sz[now];
	int cent=get_cent(now, 0); fin[cent]=1;
	S.clear(); set<pii>::iterator it;
	for (auto &i:adj[cent]) if (!fin[i.fi]) {
		tp=0; visit(i.fi, cent, i.se, 1);
		for (int j=0; j<tp; j++) {
			it=S.lower_bound(pii(K-vis[j].fi, 0));
			if (it==S.end()||it->fi!=K-vis[j].fi) continue;
			ans=min(ans, it->se+vis[j].se);
		}
		for (int j=0; j<tp; j++) S.insert(vis[j]);
	}
	it=S.lower_bound(pii(K, 0));
	if (!(it==S.end()||it->fi!=K)) ans=min(ans, it->se);
	for (auto &i:adj[cent]) if (!fin[i.fi]) dfs(i.fi);
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i=1; i<N; i++) {
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		adj[u].eb(v, c), adj[v].eb(u, c);
	}
	ans=INF; dfs(1);
	printf("%d\n", ans==INF?-1:ans);
	return 0;
}