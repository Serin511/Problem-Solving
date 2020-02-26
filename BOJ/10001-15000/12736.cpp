#include <bits/stdc++.h>
#define em emplace
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef vector<int> vim;

int N, M;
vim adj[300010]; ll C[300010], D[300010];
priority_queue<ll> P[300010];

void Merge(int x, int y) {
	if (P[x].size()<P[y].size()) swap(P[x], P[y]);
	while (P[y].size()) P[x].em(P[y].top()), P[y].pop();
}

void dfs(int n) {
	D[n]=C[n];
	if (n>N) { P[n].em(C[n]), P[n].em(C[n]); return ; }
	for (auto &i:adj[n]) dfs(i), D[n]+=D[i], Merge(n, i);
	for (int i=1; i<adj[n].size(); i++) P[n].pop();
	ll x=P[n].top(); P[n].pop();
	ll y=P[n].top(); P[n].pop();
	P[n].em(x+C[n]); P[n].em(y+C[n]);
}

int main() {
	cin>>N>>M;
	for (int i=2, p; i<=N+M; i++) cin>>p>>C[i], adj[p].eb(i);
	dfs(1); P[1].em(0);
	ll A=D[1]; ll x=P[1].top(); P[1].pop(); int i=0;
	while (P[1].size()) A-=i*(x-P[1].top()), x=P[1].top(), P[1].pop(), i++;
	cout<<A<<'\n';
	return 0;
}