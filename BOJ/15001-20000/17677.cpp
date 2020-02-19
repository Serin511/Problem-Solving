#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#define fi first
#define se second
#define ryan bear
#define sq(X) ((X)*(X))
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

vector<pll> C; vlm cp; ll ans=-(1ll<<60);
int N, M, O;

inline int Find(ll x) { return lower_bound(all(cp), x)-cp.begin(); }

struct node {
	int cnt; ll val;
	int l, r;
}nd[5000010]; int nd_tp=1;
int new_node() { return nd_tp++; }

int root[200010];

void upd(int now, int l, int t, int s, int e) {
	nd[now].cnt = nd[l].cnt + 1;
	nd[now].val = nd[l].val + cp[t];
	if (s==e) return ;
	int md=(s+e)/2;
	if (t<=md) {
		nd[now].l=new_node(); nd[now].r=nd[l].r;
		upd(nd[now].l, nd[l].l, t, s, md);
	}
	else {
		nd[now].l=nd[l].l; nd[now].r=new_node();
		upd(nd[now].r, nd[l].r, t, md+1, e);
	}
}

ll get(int n1, int n2, int s, int e, int c) {
	assert(c>=0);
	if (s==e) return c*cp[s];
	int md=(s+e)/2;
	if (nd[nd[n2].r].cnt-nd[nd[n1].r].cnt >= c) return get(nd[n1].r, nd[n2].r, md+1, e, c);
	else return nd[nd[n2].r].val-nd[nd[n1].r].val + get(nd[n1].l, nd[n2].l, s, md, c-(nd[nd[n2].r].cnt-nd[nd[n1].r].cnt));
}

void f(int s1, int e1, int s2, int e2) {
	if (s1>e1 || s2>e2) return ;
	int md=(s1+e1)/2; ll mx=-(1ll<<60), mi=0;
	for (int i=s2; i<=min(e2, md-M+1); i++) {
		ll ret=get(root[i], root[md-1], 0, O, M-2);
		ret = ret+C[i].se+C[md].se - 2*(C[md].fi-C[i].fi);
		if (mx<ret) mx=ret, mi=i;
	}
	ans=max(ans, mx);
	f(s1, md-1, s2, mi); f(md+1, e1, mi, e2);
}

int main() {
	scanf("%d %d", &N, &M);
	C.resize(N);
	for (auto &i:C) {
		scanf("%lld %lld", &i.se, &i.fi);
		cp.eb(i.se);
	}
	sort(all(C)); sort(all(cp)); unq(cp); O=cp.size();
	for (int i=0; i<=N; i++) {
		root[i]=new_node();
		if (i) upd(root[i], root[i-1], Find(C[i].se), 0, O);
	}
	f(M-1, N-1, 0, N-1);
	printf("%lld\n", ans);
	return 0;
}