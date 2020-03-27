#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef vector<int> vim;

int N, M, Q;
vim A, D, chk, adj[1005];
vector<pair<int, int> > E, S, qu;

void bfs(int st) {
	S.clear(); S.eb(st, D[st]);
	fill(all(chk), 0); chk[st]=1;
	for (int i=0; i<S.size(); i++) {
		D[S[i].fi]=S[i].se;
		for (auto &j:adj[S[i].fi]) if (!chk[j]&&S[i].se+1<D[j]) S.eb(j, S[i].se+1), chk[j]=1;
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	cin>>N>>M>>Q; D=vim(N+1, 1e9); D[1]=0; chk=vim(N+1);
	for (int i=0, u, v; i<M; i++) cin>>u>>v, E.eb(u, v);
	char t;
	for (int i=0, p; i<Q; i++) cin>>t>>p, qu.eb((t=='U'?0:1), p);

	reverse(all(qu));
	vim C(M, 0); for (auto &i:qu) if (!i.fi) C[i.se-1]=1;
	for (int i=0; i<M; i++) if (!C[i]) adj[E[i].fi].eb(E[i].se);
	bfs(1);

	for (auto &i:qu) {
		int v=i.se;
		if (!i.fi) {
			v--; adj[E[v].fi].eb(E[v].se);
			if (D[E[v].fi]+1<D[E[v].se]) D[E[v].se]=D[E[v].fi]+1, bfs(E[v].se);
		}else A.eb(D[v]>N?-1:D[v]);
	}reverse(all(A));

	for (auto &i:A) cout<<i<<'\n';
	return 0;
}