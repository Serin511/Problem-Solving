#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;

int N, M, K, chk[3010]; ll ans;
vlm cp;
vector<pair<int, ll> > adj[3010];
priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;

ll solve(ll C) {
	while (!pq.empty()) pq.pop();
	pq.em(0, 1); memset(chk, 0, sizeof(chk));
	while (!pq.empty()) {
		auto i=pq.top(); pq.pop(); if (chk[i.se]) continue;
		chk[i.se]=1;
		if (i.se==N) return i.fi+C*K;
		for (auto &j:adj[i.se]) if (!chk[j.fi]) pq.em(i.fi+max(j.se-C, 0ll), j.fi);
	}
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i=1; i<=M; i++) {
		int u, v; ll w;
		scanf("%d %d %lld", &u, &v, &w);
		adj[u].eb(v, w); adj[v].eb(u, w); cp.eb(w);
	}
	cp.eb(0); ans=(1ll<<60);
	for (auto &i:cp) ans=min(ans, solve(i));
	printf("%lld\n", ans);
	return 0;
}