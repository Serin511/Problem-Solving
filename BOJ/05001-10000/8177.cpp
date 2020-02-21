#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, M, D; ll K, V[1<<19], L[1<<19], R[1<<19], S[1<<19];

void merge(int i) {
	V[i]=max({V[i*2], V[i*2+1], R[i*2]+L[i*2+1]});
	L[i]=max(L[i*2], S[i*2]+L[i*2+1]);
	R[i]=max(R[i*2+1], S[i*2+1]+R[i*2]);
	S[i]=S[i*2]+S[i*2+1];
}

void upd(int i, int s, int e, int t, ll v) {
	if (s==e) { S[i]+=v; V[i]=L[i]=R[i]=S[i]; return ; }
	int md=(s+e)/2;
	if (t<=md) upd(i*2, s, md, t, v);
	else upd(i*2+1, md+1, e, t, v);
	merge(i);
}

void init(int i, int s, int e) {
	if (s==e) { S[i]=-K; V[i]=L[i]=R[i]=S[i]; return ; }
	int md=(s+e)/2;
	init(i*2, s, md); init(i*2+1, md+1, e);
	merge(i);
}

int main() {
	scanf("%d %d %lld %d", &N, &M, &K, &D);
	init(1, 1, N);
	for (int i=0, r, x; i<M; i++) {
		scanf("%d %d", &r, &x);
		upd(1, 1, N, r, x);
		printf("%s\n", V[1]>K*D?"NIE":"TAK");  
	}
	return 0;
}