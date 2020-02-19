#include <bits/stdc++.h>
#define ncr(n, r) ((n<0||n<r||r<0)?0:C[n][r])
using namespace std;

const int sz = 1005;
double C[sz][sz], A[sz][sz];
int N, D, R;

int main() {
	for (int i=1; i<1001; i++) for (int j=1; j<i; j++) C[i][j]=C[i][j-1]+log(i-j+1)-log(j);
	scanf("%d %d %d", &N, &D, &R);
	for (int i=1; i<=R; i++) for (int j=0; j<=D; j++) A[i][j]=(i+j);
	for (int i=R+1; i<=N; i++) {
		A[i][0]=R;
		for (int j=1; j<=D; j++) {
			A[i][j]=R;
			for (int k=0; k<=min(i, j); k++) A[i][j]+=exp(ncr(i, k)-ncr(i+j-1, j)+ncr(j-1, j-k))*A[k][j-k];
		}
	}
	printf("%.6lf\n", A[N][D]);
	return 0;
}