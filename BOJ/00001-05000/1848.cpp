#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
using namespace std;
typedef vector<int> vim;
typedef pair<int, int> pii;

int N, M; vector<pii> adj[5010];
int c1[5010], c2[5010], ans=(1<<30);

inline void dijk(vector<pii> &X) {
	priority_queue<pii> pq;
	memset(c1, 0, sizeof(c1));
	memset(c2, 0, sizeof(c2));
	for (auto &i:X) {
		c1[i.fi]=1;
		pq.em(-i.se, i.fi);
	}
	while (!pq.empty()) {
		auto k=pq.top(); pq.pop();
		if (k.se==1) { ans=min(ans, -k.fi); return ; }
		if (c2[k.se]) continue;
		c2[k.se]=1;
		for (auto &i:adj[k.se]) if (!c2[i.fi]&&(!c1[k.se]||i.fi!=1)) pq.em(k.fi-i.se, i.fi);
	}
}

inline void f(int b) {
	vector<pii> X, Y;
	for (int i=0; i<adj[1].size(); i++) ((i&(1<<b))?X:Y).eb(adj[1][i]);
	dijk(X); dijk(Y);
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i=1, a, b, c, d; i<=M; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		adj[a].eb(b, c); adj[b].eb(a, d);
	}
	for (int i=0; i<=13; i++) f(i);
	printf("%d\n", ans);
	return 0;
}