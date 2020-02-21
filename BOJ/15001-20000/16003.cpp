#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef vector<int> vim;
typedef pair<int, int> pii;

int N, M, C[100010], D[100010], chk[100010];
vim adj[100010], ord;
set<pii> S; set<int> E[100010];

int main() {
	scanf("%d %d", &N, &M);
	for (int i=0, u, v; i<M; i++) scanf("%d %d", &u, &v),
		adj[u].eb(v), adj[v].eb(u), E[u].em(v), E[v].em(u);
	for (int i=1; i<=N; i++) S.em(0, i);
	while (!S.empty()) {
		auto k=*S.begin(); S.erase(k);
		ord.eb(k.se); chk[k.se]=1; D[k.se]=N-(int)S.size();
		for (auto &i:adj[k.se]) {
			if (chk[i]) continue;
			S.erase(pii(C[i], i)); C[i]--; S.em(C[i], i);
		}
	}reverse(all(ord));
	for (int i=1; i<=N; i++) {
		int mx=-1, mi;
		for (auto &j:adj[i]) if (D[j]<D[i]&&mx<D[j]) mx=D[j], mi=j;
		if (mx<0) continue;
		for (auto &j:adj[i]) if (j!=mi&&D[j]<D[i]&&E[mi].find(j)==E[mi].end())
			{ puts("0"); return 0; } 
	}
	puts("1");
	for (auto &i:ord) printf("%d ", i); puts("");
	return 0;
}