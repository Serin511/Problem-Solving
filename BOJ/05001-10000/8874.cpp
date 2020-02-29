#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int> pii;

const int B=10, INF=1e9, X=5005, Y=205;

int R, C, Q, H[X][Y], V[X][Y], S[1050][Y][Y], D[Y];

void upd(int ts, int te, int i=1, int s=0, int e=R-1) {
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
	upd(ts, te, i*2, s, md); upd(ts, te, i*2+1, md+1, e);
	fill(D, D+C, 0); D[C]=C-1;
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
	upd(0, R-1);
	cin>>Q; while (Q--) {
		int q, x, y, w;
		cin>>q>>x>>y;
		if (q==1) cin>>w, H[x][y]=w, upd(x, x);
		if (q==2) cin>>w, V[x][y]=w, upd(x, x+1);
		if (q==3) cout<<S[1][x][y]<<'\n';
	}
	return 0;
}