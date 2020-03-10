#include <bits/stdc++.h>
#define pp pop_back
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef long long ll;
typedef vector<int> vim;

struct Edge {
	int u, v, t, chk; ll c;
	Edge() : chk(0), t(0) {}
	bool operator <(const Edge &r)const {
		return c<r.c;
	}
};

struct UF {
	int pr[100005], sz[100005];
	vim P1, P2, P3;
	void init(int v) { for (int i=1; i<=v; i++) pr[i]=0, sz[i]=1; }
	void pop(int x) {
		while (x--) {
			assert(P1.size());
			pr[P1.back()]=0;
			sz[P2.back()]=P3.back();
			P1.pp(); P2.pp(); P3.pp();
		}
	}
	int gp(int x) { return pr[x]?gp(pr[x]):x; }
	bool Un(int x, int y) {
		x=gp(x), y=gp(y);
		if (x!=y) {
			if (sz[x]<sz[y]) swap(x, y);
			P1.eb(y), P2.eb(x), P3.eb(sz[x]);
			pr[y]=x; sz[x]=max(sz[x], sz[y]+1);
		}
		return x!=y;
	}
}U;

int N, M; ll A;

void dnc(int s, int e, ll cost, vector<Edge> &E, vector<Edge> &C) {
	if (s==e) {
		vector<Edge> X;
		merge(all(E), all(C), back_inserter(X));
		int c=0;
		for (auto &i:X) if (U.Un(i.u, i.v)) c++, cost+=i.c;
		A^=cost; U.pop(c);
		return ;
	}
	vector<Edge> L, R, E1, E2;
	int md=(s+e)/2, c=0, t=0;
	for (auto &i:C) (i.t<=md?L:R).eb(i);

	for (auto &i:C) if (U.Un(i.u, i.v)) c++;
	for (auto &i:E) {
		if (U.Un(i.u, i.v)) t++, c++, E1.eb(i), cost+=i.c;
		else E2.eb(i);
	}
	U.pop(c); c=0;
	for (auto &i:E1) U.Un(i.u, i.v); E1.clear();

	for (auto &i:E2) if (U.Un(i.u, i.v)) c++, E1.eb(i);
	U.pop(c); E2.clear();

	dnc(s, md, cost, E1, L);
	merge(all(E1), all(L), back_inserter(E2));
	dnc(md+1, e, cost, E2, R);
	U.pop(t);
}

void sol() {
	cin>>N>>M;
	U.init(N); A=0;
	vector<Edge> E(N-1), C(M);
	for (auto &i:E) cin>>i.v>>i.c, i.v++;
	for (int i=0; i<N-1; i++) E[i].u=i+2;
	for (auto &i:C) cin>>i.u>>i.v>>i.c, i.u++, i.v++;
	for (int i=0; i<M; i++) C[i].t=i+1;
	sort(all(E)), sort(all(C));
	dnc(1, M, 0, E, C);
	cout<<A<<'\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int T; cin>>T;
	while (T--) sol();
	return 0;
}