#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
const ll INF = 1ll<<60;

int N, M, A[500010]; ll pd[1<<20], mx[1<<20], mn[1<<20], dp[1<<20];
vector<pii> adj[1000010];

void dfs(int n) {
	for (auto &i:adj[n]) 
		dp[i.fi]=dp[n]+i.se, dfs(i.fi), mx[n]=max({mx[n], mx[i.fi], mn[i.fi]+i.se}), mn[n]=min(!mn[n]?INF:mn[n], mn[i.fi]+i.se);
}

int main() {
	cin>>N>>M; vector<string> nm(N+1);
	for (int i=1, j; i<=N; i++) cin>>nm[i]>>j>>pd[i+M], adj[j].eb(i+M, pd[i+M]);
	for (int i=1, j; i<=M; i++) cin>>j>>pd[i], adj[j].eb(i, pd[i]);
	dfs(0);
	priority_queue<ll> pq;
	vector<pli> lf, nd;
	for (int i=M+1; i<=N+M; i++) lf.eb(dp[i], i-M);
	for (int i=1; i<=N+M; i++) nd.eb(mx[i], i);
	sort(all(lf)), sort(all(nd));
	int t=0, l; for (auto &i:lf) {
		for (; t<N+M&&nd[t].fi<=i.fi; t++) l=nd[t].se, pq.em(-(mn[l]+pd[l]));
		while (!pq.empty()&&-pq.top()<=i.fi) pq.pop();
		A[i.se]=pq.size()+1;
	}
	for (int i=1; i<=N; i++) cout<<nm[i]<<' '<<A[i]<<'\n';
	return 0;
}