#include <cstdio>
int N, A[1<<20], B[1<<20], D[1<<20];
int main() {
	scanf("%d", &N);
	for (int i=0; i<N; i++) scanf("%d %d", &A[i], &B[i]), D[i]=A[i]-B[i];
	for (int p=0; p<32; p++) for (int i=0; i<N; i++) if (D[i]>0) {
		int x = D[i]+1<A[i]?(D[i]+1)/2:A[i]/2;
		A[i]-=x*2, D[i]-=x*2;
		A[(i+1)%N]+=x, D[(i+1)%N]+=x;
	}
	for (int i=0; i<N; i++) if (A[i]!=B[i]) { puts("No"); return 0; }
	puts("Yes");
	return 0;
}