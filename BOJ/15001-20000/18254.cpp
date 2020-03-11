#include <bits/stdc++.h>
using namespace std;

const int MX = 100005, B = 300, C = 350;

int N, M, K, Q;
int ar[MX], L[MX], R[MX];
int Qu[C][MX], X[C];

struct Fw {
	int st[MX];
	void upd(int t, int v) { while (t<=N) st[t]^=v, t+=t&-t; }
	int get(int t) { int r=0; while (t) r^=st[t], t-=t&-t; return r; }
	int get(int s, int e) { return get(e)^get(s-1); }
}A, O, E;

void upd(int l, int r, int v) {
	(l%2?O:E).upd(l, v);
	if ((l^r)&1) (l%2?O:E).upd(r+1, v);
	else (l%2?E:O).upd(r, v);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N>>M>>Q;
	for (int i=1, a; i<=N; i++) cin>>a, A.upd(i, a);
	K=(M+B-1)/B;
	for (int s=0, l, r, x; s<M; s+=B) {
		int e=min(M, s+B)-1, in=s/B;
		for (int i=s; i<=e; i++) {
			cin>>l>>r>>x; L[i]=l, R[i]=r;
			upd(l, r, x);
			Qu[in][l]++; Qu[in][r+1]--;
		}
		for (int i=1; i<=N; i++) Qu[in][i]+=Qu[in][i-1];
		for (int i=1; i<=N; i++) Qu[in][i]^=Qu[in][i-1], Qu[in][i]&=1;
	}
	while (Q--) {
		int q, l, r, v;
		cin>>q>>l>>r;
		if (q==1) {
			cin>>v; l--; r--;
			for (int i=l-1; i>=l/B*B; i--) upd(L[i], R[i], v);
			for (int i=r+1; i<M&&i<(r/B+1)*B; i++) upd(L[i], R[i], v);
			for (int i=l/B; i<=r/B; i++) X[i]^=v;
		}
		if (q==2) {
			int v=A.get(l, r)^((l-1)&1?O:E).get(l-1)^(r&1?O:E).get(r);
			for (int i=0; i<K; i++) v^=X[i]*(Qu[i][r]^Qu[i][l-1]);
			cout<<v<<'\n';
		}
	}
	return 0;
}