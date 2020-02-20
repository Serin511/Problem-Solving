#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef long long ll;
typedef pair<int, ll> pil;
const ll INF = 1ll<<60;

ll F[1<<21], lz1[1<<21], lz2[1<<21];
inline void spread(int i) {
	F[i]=max(F[i]+lz1[i], lz2[i]);
	if (i<(1<<20)) for (auto &j:{i*2, i*2+1}) lz1[j]+=lz1[i], lz2[j]+=lz1[i], lz2[j]=max(lz2[j], lz2[i]);
	lz1[i]=0, lz2[i]=-INF;
}
inline void upd1(int i, int s, int e, int ts, int te, ll v) {
	spread(i);
	if (e<ts||te<s||te<ts) return ;
	if (ts<=s&&e<=te) { lz1[i]+=v, lz2[i]+=v; spread(i); return ; }
	int md=(s+e)/2;
	upd1(i*2, s, md, ts, te, v); upd1(i*2+1, md+1, e, ts, te, v);
	F[i]=max(F[i*2], F[i*2+1]);
}
inline void upd2(int i, int s, int e, int ts, int te, ll v) {
	spread(i);
	if (e<ts||te<s||te<ts) return ;
	if (ts<=s&&e<=te) { lz2[i]=v; spread(i); return ; }
	int md=(s+e)/2;
	upd2(i*2, s, md, ts, te, v); upd2(i*2+1, md+1, e, ts, te, v);
	F[i]=max(F[i*2], F[i*2+1]);
}
inline ll get(int i, int s, int e, int t) {
	spread(i);
	if (s==e) return F[i];
	int md=(s+e)/2;
	if (t<=md) return get(i*2, s, md, t);
	else return get(i*2+1, md+1, e, t);
}

int N, M;
ll A[1<<20], B[1<<20], S[1<<20], T[1<<20], P[1<<20], Q[1<<20];
vector<pair<int, pil> > qu;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin>>N>>M;
	for (register int i=1; i<=N; i++) cin>>A[i]>>S[i]>>P[i], A[i]+=A[i-1];
	for (register int i=1; i<=M; i++) cin>>B[i]>>T[i]>>Q[i], B[i]+=B[i-1];
	for (register int i=1; i<=N; i++) {
		int I=upper_bound(B, B+M+1, S[i]-A[i])-B-1;
		if (I>=0) qu.eb(i, pil(I, P[i]));
	}qu.eb(N+1, pil(M-1, -INF));
	ll im=0;
	for (register int i=1; i<=M; i++) {
		int J=upper_bound(A, A+N+1, T[i]-B[i])-A-1;
		if (J>=0) qu.eb(J+1, pil(i-1, -Q[i])), im+=Q[i];
	}
	sort(all(qu));
	for (register int i=1, j=0; i<=N+1; i++) {
		for (register int k=j; k<qu.size()&&qu[k].fi==i; k++) {
			auto l=qu[k].se; upd1(1, 0, M, 0, l.fi, l.se);
		}
		for (; j<qu.size()&&qu[j].fi==i; j++) {
			auto l=qu[j].se; upd2(1, 0, M, l.fi+1, M, get(1, 0, M, l.fi));
		}
	}
	cout<<get(1, 0, M, M)+im<<"\n";
	cout.flush();
	return 0;
}