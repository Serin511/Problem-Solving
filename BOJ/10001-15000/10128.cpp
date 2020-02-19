#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef vector<int> vim;

int N, Q, K[1000010];
int D[1000010], S[1000010], A[1000010], mx;
vim adj[1000010];

struct line {
	ll a, b;
	ll get(ll x) { return a*x+b; }
	line() {}
	line(ll A, ll B) { a=A, b=B; }
};

line L[1000010]; int s, e;
void upd(line v) {
	while (s+1<e && (L[e-2].b-v.b)*(L[e-1].a-L[e-2].a)<=(L[e-2].b-L[e-1].b)*(v.a-L[e-2].a)) e--;
	L[e++]=v;
}
void get(ll x) { while (s+1<e && L[s].get(x)<L[s+1].get(x)) s++; }

void dfs(int now, int dep) {
	D[dep]++; mx=max(mx, dep);
	for (auto &i:adj[now]) dfs(i, dep+1);
}

int main() {
	scanf("%d %d", &N, &Q);
	for (int i=1; i<=Q; i++) scanf("%d", &K[i]);
	for (int i=2, u; i<=N; i++) scanf("%d", &u), adj[u].eb(i);
	dfs(1, 1);
	for (int i=mx; i; i--) S[i]=S[i+1]+D[i];
	for (int i=1; i<=mx+1; i++) upd(line(i, S[i]));
	for (int i=1; i<=N; i++) {
		get(i);
		A[i]=L[s].a-1+(S[(int)L[s].a]+i-1)/i;
	}
	for (int i=1; i<=Q; i++) printf("%d ", A[min(N, K[i])]); puts("");
	return 0;
}