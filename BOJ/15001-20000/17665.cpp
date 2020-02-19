#include <bits/stdc++.h>
#define fi first
#define se second
#define ryan bear
#define sq(X) ((X)*(X))
#define em emplace
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
const int MAX = 1e9;

struct node {
	int a, b, c;
	node() { a=b=c=-MAX; }
	node(int a_, int b_, int c_) { a=a_, b=b_, c=c_; }
};

node operator + (const node &n1, const node &n2) {
	return node(max(n1.a, n2.a), max(n1.b, n2.b), max({n1.c, n2.c, n1.a+n2.b}));
}

struct SegTree {
	node nd[(1<<20)];
	void init(int i, int s, int e, int t, int val) {
		if (s==e) { nd[i].b=val; return ; }
		int md=(s+e)/2;
		if (t<=md) init(i*2, s, md, t, val);
		else init(i*2+1, md+1, e, t, val);
		nd[i]=nd[i*2]+nd[i*2+1];
	}
	void upd(int i, int s, int e, int t, int val) {
		if (s==e) { nd[i].a=max(nd[i].a, val); return ; }
		int md=(s+e)/2;
		if (t<=md) upd(i*2, s, md, t, val);
		else upd(i*2+1, md+1, e, t, val);
		nd[i]=nd[i*2]+nd[i*2+1];
	}
	node get(int i, int s, int e, int ts, int te) {
		if (te<s||e<ts) return node();
		if (ts<=s&&e<=te) return nd[i];
		int md=(s+e)/2;
		return get(i*2, s, md, ts, te)+get(i*2+1, md+1, e, ts, te);
	}
}S;

vector<pii> V[500010], Qu[500010]; vim stk;
int N, Q, A[500010], ans[500010];

int main() {
	scanf("%d", &N);
	for (int i=1; i<=N; i++) {
		scanf("%d", &A[i]);
		S.init(1, 1, N, i, A[i]);
		while (!stk.empty()) {
			int j=stk.back();
			if (2*i-j<=N) V[j].eb(2*i-j-1, A[i]+A[j]);
			if (A[j]>A[i]) break;
			stk.pop_back();
		}
		stk.eb(i);
	}

	scanf("%d", &Q);
	for (int i=0; i<Q; i++) {
		int l, r; scanf("%d %d", &l, &r);
		Qu[l].eb(r, i);
	}
	
	for (int i=N; i>=1; i--) {
		for (auto &j:V[i]) S.upd(1, 1, N, j.fi, j.se);
		for (auto &j:Qu[i]) ans[j.se]=S.get(1, 1, N, i, j.fi).c;
	}

	for (int i=0; i<Q; i++) printf("%d\n", ans[i]);
	return 0;
}