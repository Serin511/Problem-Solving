#include <bits/stdc++.h>
#define fi first
#define se second
#define ryan bear
#define all(V) ((V).begin()), ((V).end())
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;
typedef vector<int> vim;
typedef vector<ll> vlm;


int H, W;
int ar[2010][2010], im[2010][2010];
int Lmn[2010][2010], Lmx[2010][2010], Rmn[2010][2010], Rmx[2010][2010];
int lb[2010];

void init() {
	for (int i=1; i<=H; i++) Lmn[i][0]=Rmn[i][W+1]=(1<<30);
	for (int i=1; i<=W; i++) Lmn[0][i]=Rmn[H+1][i]=(1<<30);
	for (int i=1; i<=H; i++) for (int j=1; j<=W; j++) {
		Lmn[i][j]=min({ar[i][j], Lmn[i-1][j], Lmn[i][j-1]});
		Lmx[i][j]=max({ar[i][j], Lmx[i-1][j], Lmx[i][j-1]});
	}
	for (int i=H; i>=1; i--) for (int j=W; j>=1; j--) {
		Rmn[i][j]=min({ar[i][j], Rmn[i+1][j], Rmn[i][j+1]});
		Rmx[i][j]=max({ar[i][j], Rmx[i+1][j], Rmx[i][j+1]});
	}
}

int f(int v, int mn) {
	int r=W;
	int rn=(1<<30), rx=0;
	for (int i=1; i<=H; i++) {
		int u=upper_bound(Lmx[i]+1, Lmx[i]+W+1, mn+v)-Lmx[i];
		r=min(r, u-1);
		rn=min(rn, Rmn[i][u]);
		rx=max(rx, Rmx[i][u]);
	}
	if (rn==(1<<30)) rn=0;
	return (rx-rn<=v?1:0);
}

int solve() {
	init();
	int mx=0, st=0, mn=Lmn[H][W];
	for (int i=H; i>=1; i--) {
		for (int j=W; j>=1; j--) if (mn==ar[i][j]) { st=max(st, j); break; }
		lb[i]=st; mx=max(mx, Lmx[i][st]);
	}
	int s=mx-mn, e=Lmx[H][W], ret;
	int ans=(1<<30);
	while (s<e) {
		int md=(s+e)/2;
		if (f(md, mn)) {
			ans=md; e=md;
		}
		else s=md+1;
	}
	return ans;
}

int main() {
	int ans;
	scanf("%d %d", &H, &W);
	for (int i=1; i<=H; i++) for (int j=1; j<=W; j++) scanf("%d", &ar[i][j]);

	ans=solve(); 

	for (int i=1; i<=H; i++) for (int j=1; j<=W; j++) im[i][j]=ar[H-i+1][j];
	for (int i=1; i<=H; i++) for (int j=1; j<=W; j++) ar[i][j]=im[i][j];
	ans=min(ans, solve());

	for (int i=1; i<=H; i++) for (int j=1; j<=W; j++) im[i][j]=ar[i][W-j+1];
	for (int i=1; i<=H; i++) for (int j=1; j<=W; j++) ar[i][j]=im[i][j];
	ans=min(ans, solve());

	for (int i=1; i<=H; i++) for (int j=1; j<=W; j++) im[i][j]=ar[H-i+1][j];
	for (int i=1; i<=H; i++) for (int j=1; j<=W; j++) ar[i][j]=im[i][j];
	ans=min(ans, solve());

	printf("%d\n", ans);
	return 0;
}