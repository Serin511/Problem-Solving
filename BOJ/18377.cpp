#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

struct node {
	ll mx, mn, lz, mxc, mnc, zr;
	node() { mx=mn=lz=mxc=mnc=zr=0; }
};

int N, K, Q, A[100010], B[100010];

node operator +(node n1, node n2) {
	node ret;
	if (n1.mx<n2.mx) swap(n1, n2);
	ret.mx=n1.mx, ret.mxc=n1.mxc; if (n1.mx==n2.mx) ret.mxc+=n2.mxc;
	if (n1.mn>n2.mn) swap(n1, n2);
	ret.mn=n1.mn, ret.mnc=n1.mnc; if (n1.mn==n2.mn) ret.mnc+=n2.mnc;
	if (ret.mn*2==K) ret.zr=ret.mnc;
	if (ret.mx*2==K) ret.zr=ret.mxc;
	return ret;
}

struct seg {
	node st[1<<18];
	void init(int i, int s, int e) {
		if (s==e) { st[i].mxc=st[i].mnc=st[i].zr=1; return ; }
		int md=(s+e)/2;
		init(i*2, s, md); init(i*2+1, md+1, e);
		st[i]=st[i*2]+st[i*2+1];
	}
	void spread(int i) {
		st[i].mx+=st[i].lz; st[i].mn+=st[i].lz;
		if (i<(1<<17)) st[i*2].lz+=st[i].lz, st[i*2+1].lz+=st[i].lz;
		st[i].lz=0;
	}
	void upd(int i, int s, int e, int ts, int te, ll v) {
		spread(i);
		if (te<s||e<ts) return ;
		if (ts<=s&&e<=te) { st[i].lz+=v; spread(i); return ; }
		int md=(s+e)/2;
		upd(i*2, s, md, ts, te, v); upd(i*2+1, md+1, e, ts, te, v);
		st[i]=st[i*2]+st[i*2+1];
	}
}Sa, Sb;

int main() {
	scanf("%d %d %d", &N, &K, &Q); Sa.init(1, 1, N-K+1); Sb.init(1, 1, N-K+1);
	ll K_=(ll)K*K;
	while (Q--) {
		int a, b; scanf("%d %d", &a, &b);
		if (a==1) {
			A[b]=1-A[b];
			Sa.upd(1, 1, N-K+1, b-K+1, b, A[b]?1:-1);
		}
		if (a==2) {
			B[b]=1-B[b];
			Sb.upd(1, 1, N-K+1, b-K+1, b, B[b]?1:-1);
		}
		node n1, n2; ll mx1, mx2, mn1, mn2;
		n1=Sa.st[1]; n2=Sb.st[1];
		mx1=K-2*n1.mx; mx2=K-2*n2.mx; mn1=K-2*n1.mn; mn2=K-2*n2.mn;
		vector<pll> V;
		V.eb(mx1*mx2, n1.mxc*n2.mxc);
		if (mx2!=mn2) V.eb(mx1*mn2, n1.mxc*n2.mnc);
		if (mx1!=mn1) V.eb(mn1*mx2, n1.mnc*n2.mxc);
		if (mx1!=mn1&&mx2!=mn2) V.eb(mn1*mn2, n1.mnc*n2.mnc);
		sort(all(V));
		if (V[0].fi==0) printf("%lld %lld\n", K_/2, (n1.zr+n2.zr)*(N-K+1)-n1.zr*n2.zr);
		else {
			ll s=0;
			for (auto &i:V) if (i.fi==V[0].fi) s+=i.se;
			printf("%lld %lld\n", (K_-V[0].fi)/2, s);
		}
	}
	return 0;
}