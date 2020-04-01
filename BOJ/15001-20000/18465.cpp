#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 998244353ll;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin>>N; ll S=0;
	vector<int> A(N); for (auto &i:A) cin>>i;
	sort(A.begin(), A.end());
	vector<ll> D(N+1);
	for (int i=0, j=1; i<N; i++) {
		for (; j<=A[i]; j++)
			for (int k=j; k; k--) D[k]=(D[k]+(k==1?1:k*(k-1)*D[k-1]))%MOD;
		S=(S+D[1]-A[i]+MOD)%MOD;
		for (int k=1; k<=A[i]; k++) D[k]=(D[k]+D[k+1])%MOD;
	}
	cout<<S*((MOD+1)/2)%MOD<<'\n';
	return 0;
}