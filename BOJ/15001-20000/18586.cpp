#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef vector<int> vim;

const int MX = 300005;

int N, M, K[MX], D[MX];
ll A[MX], C[MX];
vim adj[MX], cam[MX];
map<int, ll> mp[MX];

void mg(int p, int c) {
	if (mp[p].size()<mp[c].size()) swap(mp[p], mp[c]);
	for (auto &i:mp[c]) mp[p][i.first]+=i.second;
}

void dfs(int n, int p) {
	D[n]=D[p]+1; mp[n][D[n]]+=A[n];
	for (auto &i:adj[n]) dfs(i, n), mg(n, i);
	for (auto &i:cam[n]) for (auto k=mp[n].upper_bound(D[n]+K[i]); C[i]&&k!=mp[n].begin(); k=mp[n].upper_bound(D[n]+K[i])) {
		int j=(--k)->first;
		if (mp[n][j]>=C[i]) mp[n][j]-=C[i], C[i]=0;
		else C[i]-=mp[n][j], mp[n][j]=0;
		if (!mp[n][j]) mp[n].erase(j);
	}
}

void sol() {
	cin>>N>>M;
	for (int i=1; i<=N; i++) adj[i].clear(), cam[i].clear(), mp[i].clear();
	for (int i=2, p; i<=N; i++) cin>>p, adj[p].eb(i);
	for (int i=1; i<=N; i++) cin>>A[i];
	for (int i=1, x; i<=M; i++) cin>>x>>K[i]>>C[i], cam[x].eb(i);
	dfs(1, 0);
	ll A=0; for (auto &i:mp[1]) A+=i.second;
	cout<<A<<'\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int T; cin>>T;
	while (T--) sol();
	return 0;
}