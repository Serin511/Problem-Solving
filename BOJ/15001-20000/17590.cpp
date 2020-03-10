#include <bits/stdc++.h>
#define em emplace
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef vector<int> vim;

const int MX = 200005;

struct node {
	int p, n; ll a, b;
	bool operator <(const node &r)const {
		bool i1=(a+b>=0), i2=(r.a+r.b>=0);
		if (i1&&i2) return tie(a, n)<tie(r.a, r.n);
		if (!i1&&!i2) return tie(b, n)<tie(r.b, r.n);
		return i2;
	}
}nd[MX];

int pr[MX];
int gp(int x) { return pr[x]?(pr[x]=gp(pr[x])):x; }

int T, N, chk[MX];
vim adj[MX];

void d1(int n) {
	if (nd[n].b==-1) chk[n]=1;
	for (auto &i:adj[n]) {
		d1(i);
		if (chk[i]) chk[n]=1;
	}
}

ll d3(int n) {
	ll r=0;
	for (auto &i:adj[n]) r+=max(-nd[i].a-1, -nd[i].a-nd[i].b+d3(i));
	return r;
}

void d2(int n, ll m1, ll m2) {
	m2+=nd[n].a; if (m2<0) m1-=m2, m2=0;
	if (nd[n].b==-1) cout<<m1<<' ';
	m2+=nd[n].b;
	for (auto &i:adj[n]) if (!chk[i]) {
		m2-=max(-nd[i].a-1, -nd[i].a-nd[i].b+d3(i)); if (m2<0) m1-=m2, m2=0;
	}
	for (auto &i:adj[n]) if (chk[i]) d2(i, m1, m2);
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N;
	for (int i=2; i<=N; i++) 
		cin>>nd[i].p>>nd[i].b>>nd[i].a, nd[i].a*=-1, nd[i].p++, nd[i].n=i,
		adj[nd[i].p].eb(i);
	d1(1); d2(1, 0, 0);
	for (int i=2; i<=N; i++) if (nd[i].b==-1) nd[i].b=1e18;
	set<node> S;
	for (int i=2; i<=N; i++) S.em(nd[i]);
	while (!S.empty()) {
		auto k=*S.rbegin(); S.erase(k);
		auto p=gp(k.p); pr[gp(k.n)]=gp(p); S.erase(nd[p]);
		ll x=min(nd[p].a, nd[p].a+nd[p].b+k.a), y=nd[p].a+nd[p].b+k.a+k.b-x;
		tie(nd[p].a, nd[p].b)=tie(x, y);
		if (p!=1) S.em(nd[p]);
	}
	cout<<-nd[1].a<<'\n';
	return 0;
}