#include <bits/stdc++.h>
#define fi first
#define se second
#define hsh(x, y) (((x)-1)*C+(y))
using namespace std;
typedef pair<int, int> pii;

const int xx[]={-1, 0, 1, 0}, yy[]={0, 1, 0, -1};

int M, R, C, U[805][805], S[16], v; string D;
int chk[805][805], A[805][805];

int pr[640005], Do[640005];
int get(int x) { return pr[x]?(pr[x]=get(pr[x])):x; }
void Un(int x, int y) {
	if (Do[y]) { Do[x]=1; return ; }
	x=get(x), y=get(y);
	if (x!=y) pr[y]=x;
}

pii stk[640005]; int tp;
bool bfs(int x, int y) {
	tp=0; chk[x][y]=v, stk[tp++]=pii(x, y);
	for (int i=0; i<tp; i++) {
		int a, b; tie(a, b)=stk[i];
		for (int j=0; j<4; j++) {
			int aa=a+xx[j], bb=b+yy[j], w=0;
			if (!U[aa][bb]||chk[aa][bb]==v) continue;
			for (int k=0; k<4; k++) if (chk[aa+xx[k]][bb+yy[k]]==v) w|=(1<<k);
			if (S[w]<U[aa][bb]) continue;
			if (hsh(x, y)!=get(hsh(aa, bb))) { Un(get(hsh(aa, bb)), hsh(x, y)); return 1; }
			chk[aa][bb]=v, stk[tp++]=pii(aa, bb);
		}
	}
	for (int i=0; i<tp; i++) A[stk[i].fi][stk[i].se]=tp;
	Do[hsh(x, y)]=1;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin>>M>>R>>C>>D;
	for (int i=0; i<M; i++) D[i]=(D[i]=='N'?0:D[i]=='S'?2:D[i]=='E'?1:3);
	for (int i=1; i<=R; i++) for (int j=1; j<=C; j++) cin>>U[i][j];
	D+=D, M*=2; 
	for (int i=1; i<16; i++) for (int j=0, k; j<M; j++) {
		if ((i&(1<<D[j]))!=(1<<D[j])) continue;
		for (k=j; k<M; k++) if ((i&(1<<D[k]))!=(1<<D[k])) break;
		S[i]=max(S[i], k-j); j=k-1;
	}
	for (int i=1; i<16; i++) if (S[i]==M) S[i]=1e9;
	
	memset(A, 0x3f, sizeof(A));
	while (1) {
		bool fl=0;
		for (int i=1; i<=R; i++) for (int j=1; j<=C; j++)
			if (U[i][j]&&!Do[hsh(i, j)]&&get(hsh(i, j))==hsh(i, j)) v++, fl|=bfs(i, j);
		if (!fl) break;
	}

	int A1=1e9, A2=0;
	for (int i=1; i<=R; i++) for (int j=1; j<=C; j++) {
		if (!U[i][j]) continue;
		if (A1>A[i][j]) A1=A[i][j], A2=0;
		if (A1==A[i][j]) A2++;
	}
	cout<<A1<<'\n'<<A2<<'\n';
	return 0;
}