#include <bits/stdc++.h>
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<int> vim;

const ll MOD = 1e9+7;

ll getinv(ll x) {
	ll ret=1;
	for (int i=30; i>=0; i--) {
		ret=ret*ret%MOD;
		if ((1<<i)&(MOD-2)) ret=ret*x%MOD;
	}
	return ret;
}

int N, A[505], B[505]; vim cp;
ll D[505][1010], L[1010], inv[505];

int main() {
	for (int i=1; i<=500; i++) inv[i]=getinv(i);

	scanf("%d", &N);
	for (int i=1; i<=N; i++) scanf("%d %d", &A[i], &B[i]), cp.eb(A[i]), cp.eb(B[i]+1);
	sort(all(cp)); unq(cp);
	for (int i=1; i<=N; i++) A[i]=upper_bound(all(cp), A[i])-cp.begin();
	for (int i=1; i<=N; i++) B[i]=upper_bound(all(cp), B[i])-cp.begin();
	for (int i=1; i<cp.size(); i++) L[i]=cp[i]-cp[i-1];
	fill(D[0], D[0]+1010, 1);

	for (int i=1; i<=N; i++) {
		D[i][0]=1;
		for (int j=A[i]; j<=B[i]; j++) {
			D[i][j]=D[i-1][j-1]*L[j]%MOD;
			int cnt=1; ll num=L[j]-1;
			for (int k=i-1; k; k--) if (A[k]<=j&&j<=B[k]) {
				cnt++;
				num*=(L[j]+cnt-2)*inv[cnt]%MOD; num%=MOD;
				D[i][j]+=D[k-1][j-1]*num; D[i][j]%=MOD;
			}
		}
		for (int j=1; j<cp.size(); j++) D[i][j]+=D[i-1][j]+D[i][j-1]-D[i-1][j-1]+MOD, D[i][j]%=MOD;
	}

	printf("%lld\n", (D[N][cp.size()-1]+MOD-1)%MOD);
	return 0;
}