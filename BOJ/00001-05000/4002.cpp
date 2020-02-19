#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef vector<int> vim;

int N; vim adj[100010];
ll M, C[100010], L[100010], mx;
priority_queue<ll> pq[100010]; ll S[100010];

void Merge(int u, int v) {
	while (S[u]+S[v]>M) {
		if (pq[u].empty()) S[v]-=pq[v].top(), pq[v].pop();
		else if (pq[v].empty()) S[u]-=pq[u].top(), pq[u].pop();
		else {
			if (pq[u].top()>pq[v].top()) S[u]-=pq[u].top(), pq[u].pop();
			else S[v]-=pq[v].top(), pq[v].pop();
		}
	}
	if (pq[u].size()<pq[v].size()) swap(pq[u], pq[v]);
	S[u]+=S[v];
	for (; !pq[v].empty(); pq[v].pop()) pq[u].push(pq[v].top());
}

void dfs(int now) {
	S[now]=C[now]; pq[now].push(C[now]);
	for (auto &i:adj[now]) {
		dfs(i);
		Merge(now, i);
	}
	mx=max(mx, (ll)(L[now]*pq[now].size()));
}

int main() {
	scanf("%d %lld", &N, &M);
	for (int i=1; i<=N; i++) {
		int b;
		scanf("%d %lld %lld", &b, &C[i], &L[i]);
		adj[b].eb(i);
	}
	dfs(0);
	printf("%lld\n", mx);
	return 0;
}