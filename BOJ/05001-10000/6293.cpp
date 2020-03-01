#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int INF = 1e6, SZ=70005;

int N, M, A, U[SZ];
int P[SZ][11], Q[SZ][11][11];
string S, T;

int main() {
	cin>>N>>S; T.pb(S[0]-'a'), M++;
	for (int i=1; i<N; i++) {
		if (S[i]!='e') {
			T.pb(S[i]-'a'), M++;
			if (S[i-1]=='e') U[M-1]=INF;
		}
		else A+=2;
	}
	memset(P[0], 0x3f, sizeof(P[0]));
	memset(Q[0], 0x3f, sizeof(Q[0]));
	P[0][T[0]]=0;
	for (int i=0; i<M; i++) for (int j=0; j<=10; j++) {
		int x=P[i][j], y=P[i][T[i]];
		P[i+1][j]=min({INF, (j==T[i]?INF:x+U[i]), y+2, (j==T[i]?INF:Q[i][T[i]][j]), Q[i][T[i]][T[i]]+2});
		for (int k=0; k<=10; k++)
			Q[i+1][j][k]=min({INF, (j==T[i]?INF:x+3), y+5, (j==T[i]||k==T[i]?INF:Q[i][j][k]+1),
				(j==T[i]?INF:Q[i][j][T[i]]+3), (k==T[i]?INF:Q[i][T[i]][k]+3), Q[i][T[i]][T[i]]+5});
	}
	cout<<A+P[M][10]-2<<'\n';
	return 0;
}