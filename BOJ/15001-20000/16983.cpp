#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
int cnt[100010][2];

int main() {
	scanf("%d", &N);
	ll x, y;
	ll ans=0;
	for (int i=0; i<2*N; i++) {
		scanf("%lld %lld", &x, &y);
		if (x<1) { ans+=1ll-x; x=1; }
		else if (x>N) { ans+=x-N; x=N; }
		if (y>2) { ans+=y-2ll; y=2; }
		else if (y<1) { ans+=1-y; y=1; }
		cnt[x][y-1]++;
	}
	int c[2]; c[0]=c[1]=0;
	for (int i=1; i<=N; i++) {
		c[0]+=cnt[i][0]-1, c[1]+=cnt[i][1]-1;
		if ((ll)c[0]*c[1]<0) {
			int im=min(abs(c[0]), abs(c[1]));
			ans+=(ll)im;
			c[0]=(abs(c[0])-im)*(c[0]/abs(c[0]));
			c[1]=(abs(c[1])-im)*(c[1]/abs(c[1]));
		}
		ans+=abs(c[0])+abs(c[1]);
	}
	printf("%lld\n", ans);
	return 0;
}