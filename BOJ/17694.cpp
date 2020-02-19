#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, K;
ll T, X[100010], Y[100010];

bool solve(ll S) {
	for (int i=1; i<=N; i++) Y[i]=X[i]-2*S*T*i;
	if (Y[1]<Y[N]) return false;
	int l1, l2, r1, r2; l1=r1=K; l2=1, r2=N;
	bool i1, i2;
	i1=i2=true;
	while (i1||i2) {
		int i=l1-1, j=r1+1;
		while (i>=1&&Y[i]>=Y[r1]&&Y[i]<Y[l1]) i--;
		while (j<=N&&Y[j]<=Y[l1]&&Y[j]>Y[r1]) j++;
		i1=(i>=1&&Y[i]>=Y[l1]); if (i1) l1=i;
		i2=(j<=N&&Y[j]<=Y[r1]); if (i2) r1=j;
	}
	i1=i2=true;
	while (i1||i2) {
		int i=l2+1, j=r2-1;
		while (i<=K&&Y[i]>=Y[r2]&&Y[i]<Y[l2]) i++;
		while (j>=K&&Y[j]<=Y[l2]&&Y[j]>Y[r2]) j--;
		i1=(i<=K&&Y[i]>=Y[l2]); if (i1) l2=i;
		i2=(j>=K&&Y[j]<=Y[r2]); if (i2) r2=j;
	}
	return l1<=l2&&r2<=r1;
}

int main() {
	scanf("%d %d %lld", &N, &K, &T);
	for (int i=1; i<=N; i++) scanf("%lld", &X[i]);
	ll s=-1, e=1e10;
	while (s+1<e) {
		ll md=(s+e+1)/2;
		if (solve(md)) e=md;
		else s=md;
	}
	printf("%lld\n", e);
}