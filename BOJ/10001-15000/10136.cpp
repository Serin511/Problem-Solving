#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair<int, int> pii;

int N;
pii p1[100000], p2[100000]; int t1, t2;

int main() {
	scanf("%d", &N);
	while (N--) {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);

		int ans=min(b-a, d-c)+1;
		for (int i=1; i<=sqrt(max(b, d))+10; i++) if ((a-1)/i<b/i && (c-1)/i<d/i) ans=max(ans, i);

		t1=t2=0; int mx=0;
		for (int i=sqrt(b)+10; i; i--) {
			pii x={max(mx, max(b/(i+1), (a-1)/i)+1), b/i};
			if (x.fi>x.se) continue;
			mx=x.se+1; p1[t1++]=x;
		}
		if (mx<=b) p1[t1++]=pii(mx, b);

		mx=0;
		for (int i=sqrt(d)+10; i; i--) {
			pii x={max(mx, max(d/(i+1), (c-1)/i)+1), d/i};
			if (x.fi>x.se) continue;
			mx=x.se+1; p2[t2++]=x;
		}
		if (mx<=d) p2[t2++]=pii(mx, d);

		for (int i=0, j=0; i<t1; i++) {
			while (p2[j].se<p1[i].fi&&j<t2) j++;
			while (p2[j].se<=p1[i].se&&j<t2) {
				ans=max(ans, min(p1[i].se, p2[j].se));
				j++;
			}
			if (j<t2&&p2[j].fi<=p1[i].se) ans=max(ans, min(p1[i].se, p2[j].se));
		}
		printf("%d\n", ans);
	}
	return 0;
}