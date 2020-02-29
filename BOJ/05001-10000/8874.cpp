#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef tuple<int, int> pii;

const int B=10, INF=(1<<30);

int R, C, Q, H[5005][205], V[5005][205], S[1050][205][205], D[205];

void upd(int i, int s, int e, int ts, int te) {
	if (e<ts||te<s) return ;
	if (e-s+1<=B) {
		memset(S[i], 0x3f, sizeof(S[i]));
		for (int j=0; j<C; j++) S[i][j][j]=0;
		for (int j=0; j<C; j++) for (int k=s; k<=e; k++) {
			for (int l=C-1; l>=0; l--) S[i][j][l]=min(S[i][j][l], S[i][j][l+1]+H[k][l]);
			for (int l=1; l<C; l++) S[i][j][l]=min(S[i][j][l], S[i][j][l-1]+H[k][l-1]);
			for (int l=0; l<C; l++) S[i][j][l]+=V[k][l];
		}
		return ;
	}
	int md=(s+e)/2;
	upd(i*2, s, md, ts, te); upd(i*2+1, md+1, e, ts, te);
	memset(D, 0, sizeof(D)); D[C]=C-1;
	for (int j=0; j<C; j++) for (int k=C-1; k>=0; k--) {
		pii mn(INF, 0);
		for (int l=D[k]; l<=D[k+1]; l++) mn=min(mn, pii(S[i*2][j][l]+S[i*2+1][l][k], l));
		tie(S[i][j][k], D[k])=mn;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin>>R>>C;
	for (int i=0; i<R; i++) for (int j=0; j<C-1; j++) cin>>H[i][j];
	for (int i=0; i<R-1; i++) for (int j=0; j<C; j++) cin>>V[i][j];
	upd(1, 0, R-1, 0, R-1);
	cin>>Q;
	while (Q--) {
		int q, x, y, w;
		cin>>q>>x>>y;
		if (q==1) cin>>w, H[x][y]=w, upd(1, 0, R-1, x, x);
		if (q==2) cin>>w, V[x][y]=w, upd(1, 0, R-1, x, x+1);
		if (q==3) cout<<S[1][x][y]<<'\n';
	}
	return 0;
}