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
 
const ll INF=(1ll<<60);
 
struct Seg {
	Seg *l, *r;
	ll dt1, dt2, dt3;
	Seg() {l=r=NULL; dt1=INF, dt2=dt3=-INF;}
	void upd1(int s, int e, int i, ll val) {
		if (s==e) { dt1=val; dt2=-INF; return; }
 
		spread();
 
		int md=(s+e)/2;
		if (i<=md) {
			if (!l) l=new Seg();
			l->upd1(s, md, i, val);
		}
		else {
			if (!r) r=new Seg();
			r->upd1(md+1, e, i, val);
		}
 
		dt1=min((l?l->dt1:INF), (r?r->dt1:INF));
	}
	void upd2(int s, int e, int is, int ie, ll val) {
		if (is>ie) return ;
		if (is<=s&&e<=ie) { dt2=max(dt2, val); dt3=max(dt3, dt2-dt1); return ; }
 
		spread();
 
		int md=(s+e)/2;
		if (is<=md) {
			if (l) l->upd2(s, md, is, ie, val);
		}
		if (md+1<=ie) {
			if (r) r->upd2(md+1, e, is, ie, val);
		}
		dt3=max(dt3, max((l?l->dt3:-INF), (r?r->dt3:-INF)));
	}
	ll get(int s, int e, int is, int ie) {
		if (is>ie) return -INF;
		spread();
		if (is<=s&&e<=ie) return dt3;
		int md=(s+e)/2; ll L, R; L=R=-INF;
		if (is<=md) L=(l?l->get(s, md, is, ie):-INF);
		if (md+1<=ie) R=(r?r->get(md+1, e, is, ie):-INF);
		return max(L, R);
	}
	void spread() {
		dt3=max(dt3, dt2-dt1);
		if (l) l->dt2=max(l->dt2, dt2);
		if (r) r->dt2=max(r->dt2, dt2);
		dt2=-INF;
	}
	void kill(int s, int e, int i) {
		if (s==e) {spread(); dt1=INF; return ;}
		int md=(s+e)/2;
		spread();
		if (i<=md) l->kill(s, md, i);
		else r->kill(md+1, e, i);
		dt1=min((l?l->dt1:INF), (r?r->dt1:INF));
		dt3=max(dt3, max((l?l->dt3:-INF), (r?r->dt3:-INF)));
	}
};
Seg *root;
 
int N; ll H[200010]; int A[200010], B[200010];
int Q, L[200010], R[200010];
vim Qu[200010]; ll ans[200010];
vim S[400010], E[400010];
 
void solve() {
	root=new Seg();
	for (int i=1; i<=N; i++) {
		for (int j:S[i]) root->upd1(1, N, j, H[j]);
		for (int j:E[i]) root->kill(1, N, j);
		if (i-A[i]>=1) root->upd2(1, N, max(1, i-B[i]), i-A[i], H[i]);
		for (int j:Qu[i]) ans[j]=max(ans[j], root->get(1, N, L[j], R[j]));
	}
}
 
int main() {
	//freopen("in.txt", "r", stdin);
	scanf("%d", &N);
	for (int i=1; i<=N; i++) {
		scanf("%lld %d %d", &H[i], &A[i], &B[i]);
		S[i+A[i]].push_back(i);
		E[i+B[i]+1].push_back(i);
	}
	scanf("%d", &Q);
	for (int i=0; i<Q; i++) {
		scanf("%d %d", &L[i], &R[i]);
		Qu[R[i]].push_back(i); ans[i]=-INF;
	}
	solve();
	for (int i=1; i<=N; i++) H[i]=INF-H[i];
	solve();
	for (int i=0; i<Q; i++) printf("%lld\n", ans[i]<0?-1:ans[i]);
	return 0;
}