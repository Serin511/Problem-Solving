#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define dot(p1, p2) ((p1).fi*(p2).fi+(p1).se*(p2).se)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

pll operator -(pll &p1, pll &p2) {
	return pll(p1.fi-p2.fi, p1.se-p2.se);
}
ll ccw(pll x, pll y, pll z) {
	pll p1=y-x, p2=z-x;
	return p1.fi*p2.se-p1.se*p2.fi;
}

struct Edge {
	int u, v; pll C;
	Edge(int x, int y, ll t, ll c) : u(x), v(y), C(t, c) {}
};

int N, M;
vector<Edge> E;

int p[205];
void init() { memset(p, 0, sizeof(p)); }
int get(int x) { return p[x]?(p[x]=get(p[x])):x; }
bool Union(int x, int y) { 
	x=get(x), y=get(y);
	if (x==y) return false;
	p[y]=x; return true;
}

pll sv1(1<<30, 1<<30), sv2;
pll make_mst(pll C, bool im) {
	sort(all(E), [&](Edge &p1, Edge &p2){ return dot(p1.C, C)<dot(p2.C, C); });
	init(); pll r(0, 0);
	for (auto &i:E) if (Union(i.u, i.v)) {
		r.fi+=i.C.fi, r.se+=i.C.se;
		if (im) printf("%d %d\n", i.u-1, i.v-1);
	}
	if (sv1.fi*sv1.se>r.fi*r.se) sv1=r, sv2=C;
	return r;
}

void f(pll s, pll e) {
	pll md=make_mst(pll(s.se-e.se, e.fi-s.fi), false);
	if (ccw(s, md, e)>0) f(s, md), f(md, e);
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i=0, x, y, t, c; i<M; i++)
		scanf("%d %d %d %d", &x, &y, &t, &c), E.eb(x+1, y+1, t, c);
	pll s=make_mst(pll(1, 0), false), e=make_mst(pll(0, 1), false);
	f(s, e);
	printf("%lld %lld\n", sv1.fi, sv1.se);
	make_mst(sv2, true);
	return 0;
}