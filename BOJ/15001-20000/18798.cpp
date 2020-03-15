#include <bits/stdc++.h>
using namespace std;

const int MX = 250005;

int N, K, Q, A[MX];

int F[MX];
void upd(int t, int v) { while (t<=N) F[t]+=v, t+=t&-t; }
int get(int t) { int r=0; while (t) r+=F[t], t-=t&-t; return r; }

struct UF {
	int p[MX];
	int gp(int x) { return p[x]?(p[x]=gp(p[x])):x; }
	void Un(int x, int y) {
		x=gp(x), y=gp(y);
		p[x]=y;
	}
}U[30];

void qu(int t, int v) {
	if (A[t]!=K&&(A[t]|v)==K) upd(t, 1);
	if (A[t]==K&&(A[t]|v)!=K) upd(t, -1);
	A[t]|=v;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N>>K;
	for (int i=1; i<=N; i++) {
		cin>>A[i];
		if (A[i]==K) upd(i, 1);
	}
	cin>>Q;
	while (Q--) {
		int q, l, r, x;
		cin>>q>>l>>r;
		if (q==1) {
			cin>>x;
			for (int i=0; i<30; i++) if (x&(1<<i)) {
				qu(l, (1<<i));
				for (int j=U[i].gp(l); j<r; j=U[i].gp(j)) qu(j+1, x), U[i].Un(j, j+1);
			}
		}
		if (q==2) cout<<get(r)-get(l-1)<<'\n';
	}
	return 0;
}