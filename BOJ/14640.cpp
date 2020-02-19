#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef vector<int> vim;
typedef pair<int, int> pii;

int N, T; vector<pii> P;
vim FP, st, re;

void NO() {
	puts("no");
	exit(0);
}

int main() {
	scanf("%d %d", &N, &T);
	P.resize(N); for (auto &i:P) scanf("%d %d", &i.fi, &i.se), re.eb(i.se);
	sort(all(P)); sort(all(re));
	st=vim(re), FP=vim(N, 0);
	for (int i=N-1; i>=0; i--) {
		for (int j=N-1; j>=0; j--) if (P[i].se<=re[j]) {
			st[j]-=T;

			auto k=max(i+1, (int)(lower_bound(all(P), pii(st[j]+1, 0))-P.begin()));
			if (k<N) st[j]=min(st[j], P[k].fi-FP[k]);

			if (st[j]<P[i].fi) NO();
			if (st[j]<P[i].fi+T) FP[i]=max(FP[i], P[i].fi+T-st[j]);
		}
		for (int j=i+1; j<N; j++) FP[i]=max(FP[i], FP[j]-P[j].fi+P[i].fi);
		for (int j=i+1; j<N; j++)
			if (P[j].fi-FP[j]<P[i].fi) FP[j]=max(FP[j], FP[i]+P[j].fi-P[i].fi);
	}
	puts("yes");
	return 0;
}