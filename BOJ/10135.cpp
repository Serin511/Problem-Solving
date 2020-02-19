#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

ll ccw(pll x, pll y) { return x.fi*y.se-x.se*y.fi; }

struct node {
	ll x, y, z; int i;
	node(ll X, ll Y, ll Z, int I) : x(X), y(Y), z(Z), i(I) {}
	bool operator <(const node &n)const {
		return tie(x, y, z)<tie(n.x, n.y, n.z);
	}
};

int N, M, A[200010], K[200010];
pll v1, v2;

int ar[200010];
void upd(int t, int v) { while (t<=M) ar[t]+=v, t+=t&-t; }
int get(int t) { int r=0; while (t) r+=ar[t], t-=t&-t; return r; }

void solve(int s, int e, vector<node> &V) {
	if (s==e) { for (auto &i:V) A[i.i]=s; return ; }
	int md=(s+e)/2;
	vector<node> V1, V2;
	for (auto &i:V) {
		int c=get(i.y);
		if (i.i<=md||K[i.i]<=c) V1.eb(i), upd(i.y, 1);
		else K[i.i]-=c, V2.eb(i);
	}
	for (auto &i:V1) upd(i.y, -1);
	solve(s, md, V1); solve(md+1, e, V2);
}

int main() {
	scanf("%d %lld %lld %lld %lld", &N, &v1.fi, &v1.se, &v2.fi, &v2.se);
	if (ccw(v1, v2)<0) swap(v1, v2);
	vector<node> V; vector<ll> cp;
	for (int i=0; i<N; i++) {
		ll x, y;
		scanf("%lld %lld", &x, &y);
		V.eb(ccw(v1, pll(x, y)), -ccw(v2, pll(x, y)), x*v1.fi, i+1);
		cp.eb(V[i].y);
	}
	for (int i=1; i<=N; i++) scanf("%d", &K[i]);
	sort(all(V)); sort(all(cp)); cp.resize(unique(all(cp))-cp.begin()); M=cp.size();
	for (auto &i:V) i.y=lower_bound(all(cp), i.y)-cp.begin()+1;
	solve(1, N, V);
	for (int i=1; i<=N; i++) printf("%d ", A[i]); puts("");
	return 0;
}