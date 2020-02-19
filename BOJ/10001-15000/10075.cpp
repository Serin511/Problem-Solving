#include <bits/stdc++.h>
using namespace std;

const int sz=100010;
int n, x[sz], q[sz], p[sz], a;

int main() {
	scanf("%d", &n);
	for (int i=1; i<=n; i++) scanf("%d", &x[i]);
	for (int i=2; i<=n; i++) scanf("%d %d", &p[i], &q[i]), p[i]++;
	for (int i=n; i; i--) {
		if (q[i]==0) a+=x[i], x[p[i]]=max(0, x[p[i]]-x[i]);
        if (q[i]==1) x[p[i]]+=x[i];
		if (q[i]==2) x[p[i]]=max(x[p[i]], x[i]);
	}
	printf("%d", a);
	return 0;
}