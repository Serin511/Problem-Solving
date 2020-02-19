#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node {
	ll val, mx, mx2; int mxc;
	node() : val(0), mx(0), mx2(0), mxc(0) {}
	node(ll V, ll m1, ll m2, int mc) : val(V), mx(m1), mx2(m2), mxc(mc) {}
};

node operator +(node n1, node n2) {
	if (n1.mx<n2.mx) swap(n1, n2);
	if (n1.mx==n2.mx) return node(n1.val+n2.val, n1.mx, max(n1.mx2, n2.mx2), n1.mxc+n2.mxc);
	else return node(n1.val+n2.val, n1.mx, max(n2.mx, n1.mx2), n1.mxc);
}

node st[(1<<21)];

void init(int i, int s, int e, int t, ll v) {
	if (s==e) { st[i]=node(v, v, 0, 1); return ; }
	int md=(s+e)/2;
	if (t<=md) init(i*2, s, md, t, v);
	else init(i*2+1, md+1, e, t, v);
	st[i]=st[i*2]+st[i*2+1];
}

void spread(int i, int s, int e) {
	if (s==e) return ;
	if (st[i].mx<st[i*2].mx) st[i*2].val-=(st[i*2].mx-st[i].mx)*st[i*2].mxc, st[i*2].mx=st[i].mx;
	if (st[i].mx<st[i*2+1].mx) st[i*2+1].val-=(st[i*2+1].mx-st[i].mx)*st[i*2+1].mxc, st[i*2+1].mx=st[i].mx;
}

void upd(int i, int s, int e, int ts, int te, ll v) {
	spread(i, s, e);
	if (te<s||e<ts||st[i].mx<=v) return ;
	if (ts<=s&&e<=te&&st[i].mx2<v) {
		st[i].val-=(st[i].mx-v)*st[i].mxc; st[i].mx=v; spread(i, s, e); 
		return ;
	}
	int md=(s+e)/2;
	upd(i*2, s, md, ts, te, v); upd(i*2+1, md+1, e, ts, te, v);
	st[i]=st[i*2]+st[i*2+1];
}

ll get1(int i, int s, int e, int ts, int te) {
	spread(i, s, e);
	if (te<s||e<ts) return 0;
	if (ts<=s&&e<=te) return st[i].mx;
	int md=(s+e)/2;
	return max(get1(i*2, s, md, ts, te), get1(i*2+1, md+1, e, ts, te));
}

ll get2(int i, int s, int e, int ts, int te) {
	spread(i, s, e);
	if (te<s||e<ts) return 0;
	if (ts<=s&&e<=te) return st[i].val;
	int md=(s+e)/2;
	return get2(i*2, s, md, ts, te)+get2(i*2+1, md+1, e, ts, te);
}

int N, Q; ll A;

int main() {
	scanf("%d", &N);
	for (int i=1; i<=N; i++) scanf("%lld", &A), init(1, 1, N, i, A);
	scanf("%d", &Q);
	while (Q--) {
		int q, l, r; ll x;
		scanf("%d %d %d", &q, &l, &r);
		if (q==1) scanf("%lld", &x), upd(1, 1, N, l, r, x);
		if (q==2) printf("%lld\n", get1(1, 1, N, l, r));
		if (q==3) printf("%lld\n", get2(1, 1, N, l, r));
	}
	return 0;
}