#include <bits/stdc++.h>
#define em emplace
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef vector<int> vim;

struct node {
	int n; ll a, b;
	node() : b(1) {}
	bool operator <(const node &n1)const {
		return (a*n1.b==n1.a*b?n<n1.n:a*n1.b>n1.a*b);
	}
}nd[1005];

int N, R, P[1005], par[1005]; vim adj[1005];
ll A;

int get(int x) { return par[x]?(par[x]=get(par[x])):x; }
void Un(int x, int y) { x=get(x), par[y]=x; }

void dfs(int n, int p) {
	P[n]=p;
	for (auto &i:adj[n]) if (i!=p) dfs(i, n);
}

int main() {
	scanf("%d %d", &N, &R);
	for (int i=1; i<=N; i++) nd[i].n=i, scanf("%lld", &nd[i].a), A+=nd[i].a;
	for (int i=N-1, u, v; i; i--) scanf("%d %d", &u, &v), adj[u].eb(v), adj[v].eb(u);
	dfs(R, 0);
	set<node> S;
	for (int i=1; i<=N; i++) if (i!=R) S.em(nd[i]);
	while (!S.empty()) {
		auto k=*S.begin(); S.erase(k);
		auto l=get(P[k.n]); Un(l, k.n); S.erase(nd[l]);
		A+=k.a*nd[l].b; nd[l].a+=k.a; nd[l].b+=k.b;
		if (l!=R) S.em(nd[l]);
	}
	printf("%lld\n", A);
	return 0;
}