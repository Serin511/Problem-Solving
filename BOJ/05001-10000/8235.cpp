#include <bits/stdc++.h>
#define pb push_back
using namespace std;

int N, P[1000005], Q[1000005], A;
string S, T;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N>>S;
	for (int i=0; i<N/2; i++) T.pb(S[i]), T.pb(S[N-1-i]);
	N=N/2*2;
	int r=-1, k=-1;
	for (int i=0; i<N; i++) {
		if (i<=r) P[i]=min(r-i, P[2*k-i]);
		while (i>=P[i]&&i+P[i]+1<N&&T[i-P[i]]==T[i+P[i]+1]) P[i]++;
		if (r<i+P[i]) r=i+P[i], k=i;
		Q[i-P[i]+1]=max(Q[i-P[i]+1], i);
	}
	for (int i=0, j=0; i<N/2; i++) {
		j=max({j, i*2+1, Q[i*2+1], Q[i*2+2]});
		if (P[i]==i+1) A=max(A, j-i);
	}
	cout<<A<<'\n';
	return 0;
}