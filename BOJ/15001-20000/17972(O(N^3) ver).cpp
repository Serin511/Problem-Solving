#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef pair<int, int> pii;

const int MX = 2005;

int N, D[MX][MX], A[MX];
pii S[MX];

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N; vector<int> cp;
	for (int i=1; i<=N; i++) cin>>S[i].fi>>S[i].se, cp.eb(S[i].fi);
	sort(all(cp)); cp.resize(unique(all(cp))-cp.begin());
	for (int i=1; i<=N; i++)
		S[i].fi=lower_bound(all(cp), S[i].fi)-cp.begin()+1,
		S[i].se=upper_bound(all(cp), S[i].se)-cp.begin();
	sort(S+1, S+1+N);
	for (int i=0; i<=N; i++) for (int j=0; j<=N; j++) D[i][j]=-(1e9);
	D[0][0]=0;
	for (int i=1; i<=N; i++) for (int j=i-1; j>=0; j--) {
		for (int k=N; k>S[i].se; k--) D[j+1][k]=max(D[j+1][k], D[j+1][k]+1);
		for (int k=S[i].se; k>=S[i].fi; k--) D[j+1][S[i].se]=max(D[j+1][S[i].se], D[j+1][k]+1);
		for (int k=S[i].fi-1; k>=0; k--) D[j+1][S[i].se]=max(D[j+1][S[i].se], D[j][k]+1);
	}
	for (int i=1; i<=N; i++) {
		int mx=0;
		for (int j=1; j<=N; j++) mx=max(mx, D[i][j]);
		for (int j=1; j<=mx; j++) A[j]=max(A[j], i);
	}
	for (int i=N; i>=1; i--) cout<<min(A[i], i)<<' ';
	return 0;
}