#include <bits/stdc++.h>
#define fi first
#define se second
#define ryan bear
#define sq(X) ((X)*(X))
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

const ll MOD=1000000000ll;
int N; vector<pii> P;
inline int Find(pii p) {
	int lb=lower_bound(all(P), p)-P.begin();
	return (lb<P.size()&&P[lb]==p)?lb:-1;
}
vim adj[100010]; int ar[100010], sz[100010], vis[100010]; ll D[100010];

ll ans=0;
void dfs1(int now) {
	vis[now]=1; D[now]=sz[now];
	for (int i:adj[now]) if (!vis[i]) {
		dfs1(i);
		D[now]+=D[i];
	}
}
void dfs2(int now, ll s) {
	vis[now]=1;
	for (int i:adj[now]) if (!vis[i]) {
		dfs2(i, s+D[now]-D[i]);
		ans+=(s+D[now]-D[i])*D[i];
		ans%=MOD;
	}
}

void init() {
	sort(all(P));
	memset(ar, 0, sizeof(ar));
	memset(sz, 0, sizeof(sz));
	memset(vis, 0, sizeof(vis));
	memset(D, 0, sizeof(D));
	for (int i=0; i<=100000; i++) adj[i].clear();
}
void solve() {
	init(); int C=0;
	for (int i=0; i<N; i++) {
		C++;
		ar[i]=C;
		int j; for (j=i+1; j<N; j++) {
			if (P[j].fi!=P[i].fi||P[j].se!=P[j-1].se+1) break;
			ar[j]=C;
		}
		i=j-1;
	}
	for (int i=0; i<N; i++) sz[ar[i]]++;
	for (int i=0; i<N; i++) {
		int r=Find(pii(P[i].fi+1, P[i].se));
		if (r!=-1&&(!adj[ar[i]].size()||adj[ar[i]].back()!=ar[r])) adj[ar[i]].eb(ar[r]);
	}
	for (int i=0; i<N; i++) {
		int r=Find(pii(P[i].fi-1, P[i].se));
		if (r!=-1&&(!adj[ar[i]].size()||adj[ar[i]].back()!=ar[r])) adj[ar[i]].eb(ar[r]);
	}
	memset(vis, 0, sizeof(vis)); dfs1(1);
	memset(vis, 0, sizeof(vis)); dfs2(1, 0);
}

int DistanceSum(int n, int *X, int *Y) {
	N=n; for (int i=0; i<N; i++) P.eb(X[i], Y[i]);
	solve(); for (auto &i:P) swap(i.fi, i.se); solve();
	return (int)ans;
}

int main() {
	int n, *x, *y;
	scanf("%d", &n);
	x=(int*)malloc(sizeof(int)*n);
	y=(int*)malloc(sizeof(int)*n);
	for (int i=0; i<n; i++) scanf("%d %d", &x[i], &y[i]);
	printf("%d\n", DistanceSum(n, x, y));
	return 0;
}