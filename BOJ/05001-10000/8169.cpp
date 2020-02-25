#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef vector<int> vim;

int N, S, K;
vim adj[100040];
ll rc[100040][25], ex[100040][25];

ll dfs(int n, int p) {
	if (n>K) rc[n][0]=1;
	ll r=0;
	for (auto &i:adj[n]) if (i!=p) {
		r+=dfs(i, n);
		for (int j=1; j<=K; j++) rc[n][j]+=rc[i][j-1], ex[n][j]+=ex[i][j-1];
	}
	ex[n][0]+=(rc[n][K]+S-1)/S*S;
	r+=(rc[n][K]+S-1)/S;
	for (int i=K; i>=0; i--) for (auto &j:{0, 1}) {
		if (K-i-j<0) continue;
		ll t=min(ex[n][K-i-j], rc[n][i]);
		ex[n][K-i-j]-=t, rc[n][i]-=t;
	}
	return r;
}

int main() {
	cin>>N>>S>>K;
	for (int i=1, u, v; i<N; i++) scanf("%d %d", &u, &v), adj[u+K].eb(v+K), adj[v+K].eb(u+K);
	for (int i=1; i<=K; i++) adj[i].eb(i+1), adj[i+1].eb(i);
	cout<<dfs(1, 0)<<'\n';
	return 0;
}