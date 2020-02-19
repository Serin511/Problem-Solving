#include <bits/stdc++.h>
#define fi first
#define se second
#define ryan bear
#define sq(X) ((X)*(X))
#define em emplace
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

int N, M;
vim adj[300010]; ll C[300010], D[300010];
priority_queue<ll> P[300010];

void Merge(int x, int y) {
	if (P[x].size()<P[y].size()) swap(P[x], P[y]);
	while (!P[y].empty()) { P[x].push(P[y].top()); P[y].pop(); }
}

void dfs(int now) {
	D[now]=C[now];
	if (now>N) {
		P[now].em(C[now]); P[now].em(C[now]);
		return ;
	}
	for (auto &i:adj[now]) {
		dfs(i); D[now]+=D[i];
		Merge(now, i);
	}
	for (int i=1; i<adj[now].size(); i++) P[now].pop();
	ll x = P[now].top(); P[now].pop();
	ll y = P[now].top(); P[now].pop();
	P[now].em(x+C[now]); P[now].em(y+C[now]);
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i=2; i<=N+M; i++) {
		int P; scanf("%d %lld", &P, &C[i]);
		adj[P].eb(i);
	}
	dfs(1); P[1].em(0);
	ll ans=D[1]; ll x=P[1].top(); P[1].pop();
	for (int i=0; !P[1].empty(); P[1].pop(), i++) {
		ans-=i*(x-P[1].top()); x=P[1].top();
	}
	printf("%lld\n", ans);
	return 0;
}