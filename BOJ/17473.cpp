#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node {
	int mx, on, off, lza, lzo;
	node() {}
	node(int v1, int v2, int v3) : mx(v1), on(v2), off(v3) {}
};

node operator +(node n1, node n2) { return node(max(n1.mx, n2.mx), n1.on&n2.on, n1.off&n2.off); }

node st[(1<<19)];

void spread(int i, bool im) {
	st[i].mx |= st[i].lzo; st[i].mx &= ~st[i].lza;
	st[i].on |= st[i].lzo; st[i].on &= ~st[i].lza;
	st[i].off &= ~st[i].lzo; st[i].off |= st[i].lza;
	if (im) { st[i].lza = st[i].lzo = 0; return ; }

	for (auto j:{i*2, i*2+1}) {
		st[j].lzo &= ~st[i].lza; st[j].lzo |= st[i].lzo;
		st[j].lza &= ~st[i].lzo; st[j].lza |= st[i].lza;
	}
	st[i].lza = st[i].lzo = 0;
}

void init(int i, int s, int e, int t, int v) {
	if (s==e) { st[i]=node(v, v, ~v); return ; }
	int md=(s+e)/2;
	if (t<=md) init(i*2, s, md, t, v);
	else init(i*2+1, md+1, e, t, v);
	st[i]=st[i*2]+st[i*2+1];
}

void upd1(int i, int s, int e, int ts, int te, int v) {
	spread(i, s==e);
	if (te<s||e<ts) return ;
	v &= ~st[i].off;
	if (ts<=s&&e<=te && v&st[i].on) {
		st[i].lza = v&st[i].on;
		v &= ~st[i].on;
		spread(i, s==e);
	}
	if (!v) return ;
	int md=(s+e)/2;
	upd1(i*2, s, md, ts, te, v); upd1(i*2+1, md+1, e, ts, te, v);
	st[i]=st[i*2]+st[i*2+1];
}

void upd2(int i, int s, int e, int ts, int te, int v) {
	spread(i, s==e);
	if (te<s||e<ts) return ;
	v &= ~st[i].on;
	if (ts<=s&&e<=te && v&st[i].off) {
		st[i].lzo = v&st[i].off;
		v &= ~st[i].off;
		spread(i, s==e);
	}
	if (!v) return ;
	int md=(s+e)/2;
	upd2(i*2, s, md, ts, te, v); upd2(i*2+1, md+1, e, ts, te, v);
	st[i]=st[i*2]+st[i*2+1];
}

int get(int i, int s, int e, int ts, int te) {
	spread(i, s==e);
	if (te<s||e<ts) return 0;
	if (ts<=s&&e<=te) return st[i].mx;
	int md=(s+e)/2;
	return max(get(i*2, s, md, ts, te), get(i*2+1, md+1, e, ts, te));
}

int N, Q, A;

int main() {
	scanf("%d", &N);
	for (int i=1; i<=N; i++) scanf("%d", &A), init(1, 1, N, i, A);

	scanf("%d", &Q);
	while (Q--) {
		int q, l, r, x;
		scanf("%d %d %d", &q, &l, &r);
		if (q==1) scanf("%d", &x), upd1(1, 1, N, l, r, ~x);
		if (q==2) scanf("%d", &x), upd2(1, 1, N, l, r, x);
		if (q==3) printf("%d\n", get(1, 1, N, l, r));
	}
	return 0;
}
