#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
using namespace std;
typedef vector<int> vim;

const int SZ = 1<<17;

int N, M, K, A, B, D1[SZ], D2[SZ];
vim a1[SZ], a2[SZ];

void f1() {
	vector<pair<int, int> > S; vim c(N+1, 0);
	S.eb(K, 0); c[K]=1;
	for (int i=0; i<S.size(); i++) {
		int x=S[i].fi; D1[x]=S[i].se;
		for (auto &j:a1[x]) if (!c[j]) S.eb(j, S[i].se+1), c[j]=1;
	}
}
void f2() {
	vector<pair<int, int> > S; vim c1(N+1, 0), c2(N+1, 0);
	S.eb(K, 0); c1[K]=1;
	for (int i=0; i<S.size(); i++) {
		int x=S[i].fi; D2[x]=S[i].se;
		for (auto &j:a1[x]) c2[j]=1;
		for (auto &j:a1[x]) for (int k=0; k<a2[j].size(); k++) {
			while (k<a2[j].size()&&c1[a2[j][k]]) swap(a2[j][k], a2[j][a2[j].size()-1]), a2[j].pop_back();
			if (k<a2[j].size()&&!c1[a2[j][k]]&&!c2[a2[j][k]]) S.eb(a2[j][k], S[i].se+1), c1[a2[j][k]]=1;
		}
		for (auto &j:a1[x]) c2[j]=0;
	}
}

int main() {
	scanf("%d %d %d %d %d", &N, &M, &K, &A, &B);
	for (int i=1, u, v; i<=M; i++) scanf("%d %d", &u, &v), a1[u].eb(v), a2[u].eb(v), a1[v].eb(u), a2[v].eb(u);
	f1(); f2();
	for (int i=1; i<=N; i++) printf("%d\n", min({D1[i]*A, D1[i]/2*B+D1[i]%2*A, D2[i]>0?D2[i]*B:(1<<30)}));
	return 0;
}