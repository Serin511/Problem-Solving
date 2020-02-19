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
const ll MOD = 998244353;

int N, M, K; vim adj[300010];
int chk[300010]; ll a0[300010], a1[300010], a2[300010], a3[300010], ans[300010];

void dfs1(int now) {
	chk[now]=1; a1[now]=a0[now];
	for (auto &i:adj[now]) if (!chk[i]) {
		dfs1(i);
		a1[now]+=a1[i]; a2[now]+=a2[i]+a1[i]; a3[now]+=a3[i];
	}
	a3[now]+=2*a2[now]-(a1[now]-a0[now]);
}

void dfs2(int now, ll s1, ll s2) {
	chk[now]=1; ans[now]=s2; s1+=a2[now];
	for (auto &i:adj[now]) if (!chk[i]) 
		dfs2(i, s1-a2[i]-a1[i]+(M-a1[i]), s2-(2*a2[i]+a1[i])+(2*(s1-a2[i]-a1[i])+(M-a1[i])));
}

int main() {
	scanf("%d", &N);
	for (int i=1; i<N; i++) {
		int u, v; scanf("%d %d", &u, &v);
		adj[u].eb(v); adj[v].eb(u);
	}

	scanf("%d", &M);
	for (int i=1; i<=M; i++) {
		int u; scanf("%d", &u);
		a0[u]++;
	}

	dfs1(1); chk_init; dfs2(1, 0, a3[1]);

	ll s=0; scanf("%d", &K);
	for (int i=1; i<=K; i++) {
		int u; scanf("%d", &u);
		s+=ans[u]%MOD;
	}
	printf("%lld\n", s%MOD);
	return 0;
}