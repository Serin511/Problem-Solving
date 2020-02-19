#include <bits/stdc++.h>
#define eb emplace_back
#define init(V) memset(V, 0, sizeof(V))
using namespace std;
typedef long long ll;
typedef vector<int> vim;

const int X = 1<<18;

int N, dep[X], sz[X], cnt[X], c1[X], c2[X], c3[X];
vim adj[X], C;

void dfs(int n, int p, ll &A) {
	dep[n]=dep[p]+1; sz[n]=1; A+=(ll)dep[p];
	for (auto &i:adj[n]) if (i!=p) dfs(i, n, A), sz[n]+=sz[i];
}

void get_cent(int now, int par) {
	if (N-sz[now]>N/2) return ;
	int fl=0;
	for (auto &i:adj[now]) if (i!=par&&sz[i]>N/2) fl=1;
	if (!fl) C.eb(now);
	for (auto &i:adj[now]) if (i!=par) get_cent(i, now);
}

ll f(int C) {
	ll A=0; dfs(C, 0, A); init(cnt); init(c1); for (auto &i:adj[C]) cnt[sz[i]]++;
	c1[0]=1;
	for (int i=1; i<=N/2; i++) if (cnt[i]) {
		init(c2); init(c3);
		for (int j=0; j<=N/2; j++) if (c1[j]) c2[j+i*min(cnt[i], (N/2-j)/i)]=1;
		for (int j=N/2; j>=i; j--) {
			if (c2[j]) c3[j%i]++;
			if (c1[j]) c3[j%i]--;
			if (c3[j%i]) c1[j]=1;
		}
	}
	for (int i=N/2; i; i--) if (c1[i]) { A+=(ll)i*(N-1-i); break; }
	return A;
}

int main() {
	scanf("%d", &N);
	for (int i=1, u, v; i<N; i++) scanf("%d %d", &u, &v), adj[u].eb(v), adj[v].eb(u);
	ll A; dfs(1, 0, A); get_cent(1, 0);
	A=0; for (auto &i:C) A=max(A, f(i));
	printf("%d %lld\n", N-1, A);
	return 0;
}