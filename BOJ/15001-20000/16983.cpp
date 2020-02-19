#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, C[100001][2], c[2];
ll x, y, A;

int main() {
	scanf("%d", &N);
	for (int i=0; i<2*N; i++) {
		scanf("%lld %lld", &x, &y);
		if (x<1) A+=1-x, x=1;
		else if (x>N) A+=x-N, x=N;
		if (y>2) A+=y-2, y=2;
		else if (y<1) A+=1-y, y=1;
		C[x][y-1]++;
	}
	for (int i=1; i<=N; i++) {
		c[0]+=C[i][0]-1, c[1]+=C[i][1]-1;
		if ((ll)c[0]*c[1]<0) {
			int im=min(abs(c[0]), abs(c[1]));
			A+=im;
			c[0]=(abs(c[0])-im)*(c[0]/abs(c[0]));
			c[1]=(abs(c[1])-im)*(c[1]/abs(c[1]));
		}
		A+=abs(c[0])+abs(c[1]);
	}
	printf("%lld\n", A);
	return 0;
}