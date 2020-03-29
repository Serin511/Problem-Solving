#include <bits/stdc++.h>
#define em emplace
#define eb emplace_back
using namespace std;
typedef long long ll;

const int MX = 250005;

struct dt {
	int S, E; ll V;
	dt(int s, int e, ll v) : S(s), E(e), V(v) {}
};

int N;
vector<dt> B;
vector<int> adj[MX], chk;
priority_queue<ll> nd[MX];

void mg(int p, int c) {
	if (nd[p].size()<nd[c].size()) swap(nd[p], nd[c]);
	vector<ll> x;
	while (nd[c].size()) x.eb(nd[c].top()+nd[p].top()), nd[c].pop(), nd[p].pop();
	for (auto &i:x) nd[p].em(i);
}

void dfs(int n) {
	chk[n]=1;
	for (auto &i:adj[n]) {
		dfs(i);
		mg(n, i);
	}
	nd[n].em(B[n].V);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N;
	for (int i=0, s, e, v; i<N; i++) cin>>s>>e>>v, B.eb(s, e, v);
	sort(B.begin(), B.end(), [](dt &d1, dt &d2) { return d1.S==d2.S?d1.E>d2.E:d1.S<d2.S; });
	vector<pair<int, int> > S;
	for (int i=0; i<N; i++) {
		while (S.size()&&S.back().second<=B[i].S) S.pop_back();
		if (S.size()) adj[S.back().first].eb(i);
		S.eb(i, B[i].E);
	}
	chk.resize(N);
	vector<ll> A(N, 0);
	for (int i=0; i<N; i++) if (!chk[i]) {
		dfs(i); vector<ll> x;
		for (int j=0; nd[i].size(); j++) A[j]+=nd[i].top(), nd[i].pop();
	}
	for (int i=1; i<N; i++) A[i]+=A[i-1];
	for (auto &i:A) cout<<i<<' ';
	return 0;
}