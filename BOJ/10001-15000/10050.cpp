#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, l=-1;
	scanf("%d", &N);
	if (N==3) { puts("2 to -1\n5 to 2\n3 to -3"); return 0; }
	int i;
	for (i=0; i<N-7; i+=4) {
		printf("%d to %d\n", 2*N-2-i, -1+i);
		printf("%d to %d\n", 3+i, 2*N-2-i);
	}
	if (N-i==4) for (auto &j:{6, 3, 0, 7}) printf("%d to %d\n", j+i, l+i), l=j;
	if (N-i==5) for (auto &j:{8, 3, 6, 0, 9}) printf("%d to %d\n", j+i, l+i), l=j;
	if (N-i==6) for (auto &j:{10, 7, 2, 6, 0, 11}) printf("%d to %d\n", j+i, l+i), l=j;
	if (N-i==7) for (auto &j:{8, 5, 12, 3, 9, 0, 13}) printf("%d to %d\n", j+i, l+i), l=j;
	for (i=i-4; i>=0; i-=4) {
		printf("%d to %d\n", i, 2*N-5-i);
		printf("%d to %d\n", 2*N-1-i, i);
	}
	return 0;
}