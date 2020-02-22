#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, M, K;
	cin>>N>>M; K=sqrt(N*M);
	if (N<M||K*K!=N*M) return !puts("-1");
	cout<<N*K<<'\n';
	for (int i=1; i<=N; i++) for (int j=0; j<K; j++)
		cout<<i<<' '<<(K*i+N-j-1)%N+1<<'\n';
	return 0;
}