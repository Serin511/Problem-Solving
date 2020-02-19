#include <bits/stdc++.h>
#define fi first
#define se second
#define ryan bear
#define em emplace
#define eb emplace_back
#define sq(X) ((X)*(X))
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

int N, B, Q;
vim adj[5010]; vector<pii> ans[5010];
int bl[5010], subsz[5010], chk[5010];
int qu[5010][5010];

void dfs1(int now) {
	chk[now]=1; subsz[now]=1;
	for (auto &i:adj[now]) if (!chk[i]) {
		dfs1(i); subsz[now]+=subsz[i];
	}
	ans[now].resize(min(B, subsz[now])+1); fill(all(ans[now]), pii(10000, 0));
}

void dfs2(int now) {
	chk[now]=1; 
	if (bl[now]) ans[now][1]=pii(1, 1);
	else ans[now][0]=pii(1, 1);
	int sum=1;
	for (auto &i:adj[now]) if (!chk[i]) {
		dfs2(i);
		for (int j=min(sum, B); j>=0; j--) if (ans[now][j].se) for (int k=min(subsz[i], B); k>=0; k--) {
			if (!ans[i][k].se) continue;
			ans[now][j+k].fi=min(ans[now][j+k].fi, ans[now][j].fi+ans[i][k].fi);
			ans[now][j+k].se=max(ans[now][j+k].se, ans[now][j].se+ans[i][k].se);
		}
		sum+=subsz[i];
	}
}

void f() {
	vector<pii> ar[5010];
	for (int i=1; i<=N; i++) for (int j=0; j<ans[i].size(); j++) ar[j].eb(ans[i][j]);
	for (int i=0; i<=B; i++) {
		sort(all(ar[i]));
		ar[i].erase(lower_bound(all(ar[i]), pii(10000, 0)), ar[i].end());
		for (int j=0, k=0; j<ar[i].size(); j++) {
			for (k=max(k, ar[i][j].fi); k<=ar[i][j].se; k++) qu[k][i]=1;
		}
	}
}

int main() {
	scanf("%d %d", &N, &B);
	for (int i=1; i<=B; i++) { int u; scanf("%d", &u); bl[u]=1; }
	for (int i=1; i<N; i++) {
		int u, v; scanf("%d %d", &u, &v);
		adj[u].eb(v); adj[v].eb(u);
	}

	dfs1(1); memset(chk, 0, sizeof(chk)); dfs2(1); f();

	scanf("%d", &Q); int cnt=0;
	while (Q--) {
		int u, v;
		scanf("%d %d", &u, &v);
		if (qu[u][v]) cnt++;
	}
	printf("%d\n", cnt);
	return 0;
}