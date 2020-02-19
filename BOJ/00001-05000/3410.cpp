#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef vector<int> vim;
typedef pair<int, int> pii;

int N, M; ll D[100010][2];
vector<pii> adj[100010];

void dijk(int st) {
	priority_queue<pair<ll, int> > pq;
	vim chk(N+1, 0);
	pq.em(0, st);
	while (!pq.empty()) {
		auto k=pq.top(); pq.pop();
		if (chk[k.se]) continue;
		D[k.se][st-1]=-k.fi; chk[k.se]=1;
		for (auto &i:adj[k.se]) if (!chk[i.fi]) pq.em(k.fi-i.se, i.fi);
	}
}

void solve() {
	scanf("%d %d", &N, &M);
	for (int i=1; i<=N; i++) adj[i].clear();
	for (int i=1, u, v, c; i<=M; i++)
		scanf("%d %d %d", &u, &v, &c), adj[u].eb(v, c), adj[v].eb(u, c);
	dijk(1); dijk(2);
	vector<ll> U, V;
	for (int i=1; i<=N; i++) U.eb(D[i][0]+D[i][1]), V.eb(D[i][0]-D[i][1]);
	sort(U.begin(), U.end()), sort(V.begin(), V.end());
	ll S=0;
	for (int i=0; i<N/2; i++) S-=U[i]+V[i];
	for (int i=(N+1)/2; i<N; i++) S+=U[i]+V[i];
	printf("%.12lf\n", (double)S/2.0/N);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}