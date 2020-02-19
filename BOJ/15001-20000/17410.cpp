#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
using namespace std;
 
const int SZ=300, MAX=10000;

int N, Q, A[100010], B[405][10005];

int main() {
	scanf("%d", &N);
	for (int i=0; i<N; i++) {
		scanf("%d", &A[i]);
		for (int l=MAX+1-A[i]; l<=MAX; l+=l&-l) B[i/SZ][l]++;
	}
	scanf("%d", &Q);
	while (Q--) {
		int q, i, j, k;
		scanf("%d %d %d", &q, &i, &j);
		if (q==1) {
			i--;
			for (int l=MAX+1-A[i]; l<=MAX; l+=l&-l) B[i/SZ][l]--;
			A[i]=j;
			for (int l=MAX+1-A[i]; l<=MAX; l+=l&-l) B[i/SZ][l]++;
		}
		if (q==2) {
			i--, j--; scanf("%d", &k);
			if (k==MAX) { puts("0"); continue; }
			if (i/SZ == j/SZ) {
				int ans=0;
				for (int l=i; l<=j; l++) if (A[l]>k) ans++;
				printf("%d\n", ans);
				continue;
			}
			int im=(i/SZ+1)*SZ, ans=0;
			for (int l=i; l<im; l++) if (A[l]>k) ans++;
			for (int l=j/SZ*SZ; l<=j; l++) if (A[l]>k) ans++;
			for (int l=i/SZ+1; l<j/SZ; l++) for (int r=MAX-k; r; r-=r&-r) ans+=B[l][r];
			printf("%d\n", ans);
		}
	}
	return 0;
}