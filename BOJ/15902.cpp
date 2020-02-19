#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD=1e9+7;

int L, N, M;
int A[3010], B[3010], c1, c2;
ll D[3010], ans=1, f[3010], f_[3010];

ll inv(ll x) {
	ll ret=1;
	for (int i=30; i>=0; i--) {
		ret=ret*ret%MOD;
		if ((1<<i)&(MOD-2)) ret=ret*x%MOD;
	}
	return ret;
}

int main() {
	scanf("%d", &L);
	D[0]=D[1]=D[2]=1; f[0]=1;
	for (int i=1; i<=L; i++) f[i]=f[i-1]*i%MOD;
	for (int i=0; i<=L; i++) f_[i]=inv(f[i]);

	for (int i=3; i<=L; i++) {
		for (int j=1; j<=i-1; j+=2) D[i]+=((D[j]*D[i-j]%MOD)*f_[j-1]%MOD)*f_[i-j-1]%MOD;
		D[i]%=MOD; D[i]=D[i]*f[i-2]%MOD;
	}

	scanf("%d", &N); for (int i=1; i<=N; i++) scanf("%d", &A[i]);
	scanf("%d", &M); for (int i=1; i<=M; i++) scanf("%d", &B[i]);

	for (int i=1, j=1, k, l; i<=N, j<=M; ) {
		int s1=A[i], s2=B[j];
		k=i+1, l=j+1;
		while (s1!=s2) {
			if (s1<s2) s1+=A[k++];
			else s2+=B[l++];
		}
		if (k-i>=2||l-j>=2) {
			c1+=s1-1;
			ans=ans*(D[s1]*f_[s1-1]%MOD)%MOD;
		}
		i=k, j=l;
	}
	ans=ans*f[c1]%MOD;
	printf("%d %lld\n", c1, ans);
	return 0;
}