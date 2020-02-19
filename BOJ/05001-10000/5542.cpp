#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef vector<int> vim;
typedef pair<int, int> pii;

int N, M, K, Q, d[100010], chk[100010];
int x[100010], y[100010], s[100010], e[100010];
vector<pii> adj[100010];
vim cp, P[100010], qu[100010];

int par[100010];
int get(int u) { return par[u]?(par[u]=get(par[u])):u; }
void Union(int u, int v) {
	u=get(u); v=get(v);
	if (u!=v) par[v]=u;
}

int main() {
	scanf("%d %d %d %d", &N, &M, &K, &Q);
	for (int i=0, u, v, c; i<M; i++) scanf("%d %d %d", &u, &v, &c), adj[u].eb(v, c), adj[v].eb(u, c);
	priority_queue<pii> pq;
	for (int i=0, u; i<K; i++) scanf("%d", &u), pq.em(0, u);
	while (!pq.empty()) {
		auto k=pq.top(); pq.pop();
		if (chk[k.se]) continue;
		chk[k.se]=1; d[k.se]=-k.fi;
		for (auto &i:adj[k.se]) if (!chk[i.fi]) pq.em(k.fi-i.se, i.fi);
	}
	for (int i=1; i<=N; i++) cp.eb(d[i]);
	sort(all(cp)); unq(cp);
	for (int i=1; i<=N; i++) P[lower_bound(all(cp), d[i])-cp.begin()].eb(i);
	for (int i=1; i<=Q; i++) scanf("%d %d", &x[i], &y[i]), s[i]=0, e[i]=cp.size();
	for (int p=0; p<20; p++) {
		memset(par, 0, sizeof(par));
		for (int i=0; i<cp.size(); i++) qu[i].clear();
		for (int i=1; i<=Q; i++) if (s[i]+1<e[i]) qu[(s[i]+e[i])/2].eb(i);
		for (int i=cp.size()-1; i>=0; i--) {
			for (auto &j:P[i]) for (auto &k:adj[j]) if (d[k.fi]>=cp[i]) Union(k.fi, j);
			for (auto &j:qu[i]) {
				if (get(x[j])==get(y[j])) s[j]=i;
				else e[j]=i;
			}
		}
	}
	for (int i=1; i<=Q; i++) printf("%d\n", cp[s[i]]);
	return 0;
}