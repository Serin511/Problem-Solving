#include <bits/stdc++.h>
#include <utility>
#include <algorithm>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int MAX=(1<<21);

int ans[(1<<21)];

struct seg{
	pii pi[(1<<22)];
	void lazy(int val, int ind, int op) {
		if (op==1) {
			pi[ind].fi=max(val, pi[ind].first);
			pi[ind].se=max(val, pi[ind].second);
		}
		if (op==2) {
			pi[ind].fi=min(val, pi[ind].first);
			pi[ind].se=min(val, pi[ind].second);
		}
	}
	void update(int s, int e, int i, int ds, int de, int h, int op) {
		if (!(s<=de&&ds<=e)) return ;
		if (s<=ds&&de<=e) {
			lazy(h, i, op);
			if (s==e) ans[s]=pi[i].fi;
		}
		else {
			lazy(pi[i].fi, i*2, 1); lazy(pi[i].se, i*2, 2);
			lazy(pi[i].fi, i*2+1, 1); lazy(pi[i].se, i*2+1, 2);
			pi[i]={0,(1<<30)};
			int md=(ds+de)/2;
			update(s, e, i*2, ds, md, h, op);
			update(s, e, i*2+1, md+1, de, h, op);
		}
	}
}T;


void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	for (int i=0; i<k; i++) T.update(left[i], right[i], 1, 0, n-1, height[i], op[i]);
	for (int i=0; i<n; i++) T.update(i, i, 1, 0, n-1, 0, 1);
	for (int i=0; i<n; i++) finalHeight[i]=ans[i];
	return;
}
int N, K, OP[500010], L[500010], R[500010], H[500010], FH[500010];
int main() {
	scanf("%d %d", &N, &K);
	for (int i=0; i<K; i++) scanf("%d %d %d %d", &OP[i], &L[i], &R[i], &H[i]);
	buildWall(N, K, OP, L, R, H, FH);
	for (int i=0; i<N; i++) printf("%d\n", FH[i]);
	return 0;
}