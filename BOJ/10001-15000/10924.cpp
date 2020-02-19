#include <bits/stdc++.h>
using namespace std;
int *s, *x, *y, *p, *q;
int ans;
int n, m;
int B[200010], posB[200010], F[200010], posF[200010];
// 현재 수열, 현재 수열의 pos, 결과 수열, 결과 수열의 pos
int seq[600010][2], tp;
bool canSwap(int l)
{
	int i; tp=0;
	for (i=0; i<n; i++) B[i]=s[i], posB[s[i]]=i, F[i]=s[i], posF[s[i]]=i;
	for (i=0; i<l; i++) {
		swap(F[x[i]], F[y[i]]);
		swap(posF[F[x[i]]], posF[F[y[i]]]);
	}
	while (tp<n&&F[tp]==tp) tp++;
	for (i=0; i<l; i++) {
		swap(B[x[i]], B[y[i]]);
		swap(posB[B[x[i]]], posB[B[y[i]]]);
		int i1=F[tp], i2=F[posF[tp]];
		swap(F[tp], F[posF[tp]]);
		swap(posF[i1], posF[i2]);
		seq[i][0]=posB[i1], seq[i][1]=posB[i2];
		swap(B[posB[i1]], B[posB[i2]]);
		swap(posB[i1], posB[i2]);
		while (tp<n&&F[tp]==tp) tp++;
		if (tp>=n) break;
	}
	if (tp>=n) {
		for (int j=0; j<=i; j++) p[j]=seq[j][0], q[j]=seq[j][1];
		for (int j=i+1; j<l; j++) p[j]=q[j]=1;
		ans=l;
		return true;
	}
	return false;
}

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
    s=S; x=X; y=Y; p=P; q=Q; n=N; m=M;
	int st=0, re=M;
	while (st<re) {
		int md=(st+re)/2;
		if (canSwap(md)) re=md;
		else st=md+1;
	}
	return ans;
}

int main()
{
	int N, M; int S[200010], X[600010], Y[600010];
	scanf("%d", &N);
	int i;
	for (i=0; i<N; i++) scanf("%d", &S[i]);
	scanf("%d", &M);
	for (i=0; i<M; i++) scanf("%d %d", &X[i], &Y[i]);
	int *P = (int*)malloc(sizeof(int) * (unsigned int)M), *Q = (int*)malloc(sizeof(int) * (unsigned int)M);
	int ans = findSwapPairs(N, S, M, X, Y, P, Q);
	printf("%d\n", ans);
	for (int i = 0; i < ans; ++i)
		printf("%d %d\n", P[i], Q[i]);
	return 0;
}