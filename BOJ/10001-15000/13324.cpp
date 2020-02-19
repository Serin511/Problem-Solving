#include <bits/stdc++.h>
#define em emplace
using namespace std;
typedef long long ll;

int N; ll A[1<<20], B[1<<20];
priority_queue<ll> pq;

int main() {
	scanf("%d", &N);
	for (int i=1; i<=N; i++) {
		scanf("%lld", &A[i]); A[i]-=i;
		pq.em(A[i]); pq.em(A[i]);
		pq.pop(); B[i]=pq.top();
	}
	for (int i=N-1; i>=1; i--) B[i]=min(B[i], B[i+1]);
	for (int i=1; i<=N; i++) printf("%lld\n", B[i]+i);
	return 0;
}