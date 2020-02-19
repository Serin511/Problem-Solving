#include <bits/stdc++.h>
#define fi first
#define se second
#define ryan bear
#define em emplace
#define eb emplace_back
#define sq(X) ((X)*(X))
#define all(V) (V).begin(), (V).end()
#define chk_init memset(chk, 0, sizeof(chk))
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

int N, K;
int D1[100005][105], D2[100005][105], C[100005], sz[100005];
vim adj[100005];

inline void dfs(int now) {
	int s=1;
	for (int i=1; i<=K; i++) D1[now][i]=D2[now][i]=-(1<<29);
	D1[now][1]=C[now];
	for (auto &i:adj[now]) {
		dfs(i);
		for (int j=min(s, K); j>=0; j--) for (int k=min(sz[i], K-j); k>=0; k--) {
			D1[now][j+k]=max(D1[now][j+k], D1[now][j]+D2[i][k]);
			D2[now][j+k]=max(D2[now][j+k], D2[now][j]+max(D1[i][k], D2[i][k]));
		}
		s+=sz[i];
	}
	sz[now]=s;
}

void solve() {
	scanf("%d %d", &N, &K);
	for (int i=1; i<=N; i++) adj[i].clear();
	for (int i=1; i<=N; i++) scanf("%d", &C[i]);
	for (int i=2; i<=N; i++) {
		int u; scanf("%d", &u);
		adj[u+1].eb(i);
	}
	dfs(1);
	int mx=-(1<<30); for (int i=1; i<=K; i++) mx=max({mx, D1[1][i], D2[1][i]});
	printf("%d\n", mx);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) solve();
	return 0;
}