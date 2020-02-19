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
typedef bitset<1001> bs;

int chk[1010], sz[1010];
int N, K;
vector<pii> adj[1010];
vector<bs> sv1[1010], sv2[1010];
int a1[1010][1010], a2[1010][1010];

void dfs1(int now) {
	chk[now]=1; sz[now]=1;
	for (auto &i:adj[now]) if (!chk[i.fi]) {
		dfs1(i.fi);
		sz[now]+=sz[i.fi];
	}
	fill(a1[now], a1[now]+1010, (1<<20)); a1[now][1]=0; sv1[now].resize(sz[now]+1); sv1[now][1].set(now, true);
	fill(a2[now], a2[now]+1010, (1<<20)); a2[now][0]=0; sv2[now].resize(sz[now]+1);
}

void dfs2(int now) {
	chk[now]=1; int s=1; int i1; bs i2;
	for (auto &i:adj[now]) if (!chk[i.fi]) {
		dfs2(i.fi);
		for (int j=s+sz[i.fi]; j>=0; j--) {
			i1=a1[now][max(0, j-sz[i.fi])]+a2[i.fi][j-max(0, j-sz[i.fi])];
			i2=sv1[now][max(0, j-sz[i.fi])]|sv2[i.fi][j-max(0, j-sz[i.fi])];

			for (int k=max(0, j-sz[i.fi]); k<=j&&k<=s; k++) {
				i1=min({i1, a1[now][k]+a2[i.fi][j-k], a1[now][k]+a1[i.fi][j-k]+i.se});
				if (i1==a1[now][k]+a2[i.fi][j-k]) i2=sv1[now][k]|sv2[i.fi][j-k];
				if (i1==a1[now][k]+a1[i.fi][j-k]+i.se) i2=sv1[now][k]|sv1[i.fi][j-k];
			}
			a1[now][j]=i1; sv1[now][j]=i2;

			i1=a2[now][max(0, j-sz[i.fi])]+a1[i.fi][j-max(0, j-sz[i.fi])];
			i2=sv2[now][max(0, j-sz[i.fi])]|sv1[i.fi][j-max(0, j-sz[i.fi])];

			for (int k=max(0, j-sz[i.fi]); k<=j&&k<=s; k++) {
				i1=min({i1, a2[now][k]+a1[i.fi][j-k], a2[now][k]+a2[i.fi][j-k]+i.se});
				if (i1==a2[now][k]+a1[i.fi][j-k]) i2=sv2[now][k]|sv1[i.fi][j-k];
				if (i1==a2[now][k]+a2[i.fi][j-k]+i.se) i2=sv2[now][k]|sv2[i.fi][j-k];
			}
			a2[now][j]=i1; sv2[now][j]=i2;
		}
		s+=sz[i.fi];
	}
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i=1; i<N; i++) {
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		adj[u].eb(v, c); adj[v].eb(u, c);
	}
	dfs1(1); chk_init; dfs2(1);
	printf("%d\n", min(a1[1][K], a2[1][K]));
	if (a1[1][K]<a2[1][K]) { for (int i=1; i<=N; i++) if (sv1[1][K][i]) printf("%d ", i); puts(""); }
	else { for (int i=1; i<=N; i++) if (sv2[1][K][i]) printf("%d ", i); puts(""); }
	return 0;
}