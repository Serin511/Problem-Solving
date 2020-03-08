#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

struct line {
	ll x, y; int s, e, i;
	line(pll p, int S, int E, int I) : x(p.fi), y(p.se), s(S), e(E), i(I) {}
};

const int MX = 200005;

int N; ll T; pll P[MX];
vector<pll> lis[MX];
vector<ll> A[MX];

void ve(int I, int s, int e, int ts, int te, vector<line> &Q) {
	if (te<ts) return ;
	int md=(ts+te)/2;
	pll mn(1ll<<60, 0); line now=Q[md];
	for (int i=s; i<=e; i++) mn=min(mn, pll((now.x-lis[I-1][i].fi)*(now.y-lis[I-1][i].se)+A[I-1][i], i));
	A[I][now.i]=min(A[I][now.i], mn.fi); ve(I, s, mn.se, md+1, te, Q); ve(I, mn.se, e, ts, md-1, Q);
}

void sol(int I, int s, int e, vector<line> &Q) {
	if (Q.empty()) return;
	vector<line> Q1, Q2, E;
	int md=(s+e)/2;
	for (auto &i:Q) {
		if (i.s<=s&&e<=i.e) { E.eb(i); continue; }
		if (i.s<=md) Q1.eb(i);
		if (md+1<=i.e) Q2.eb(i);
	}ve(I, s, e, 0, E.size()-1, E);
	sol(I, s, md, Q1); sol(I, md+1, e, Q2);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N>>T;
	for (int i=1; i<=N; i++) cin>>P[i].fi>>P[i].se;
	sort(P+1, P+N+1);
	vector<ll> im;
	for (int i=1; i<=N; i++) {
		int lb=lower_bound(im.begin(), im.end(), P[i].se)-im.begin();
		lis[lb+1].eb(P[i]);
		if (lb<im.size()) im[lb]=min(im[lb], P[i].se);
		else im.eb(P[i].se);
	}int M=im.size()+1;
	lis[0].eb(0, 0); lis[M].eb(T, T); A[0].eb(0);
	for (int i=1; i<=M; i++) {
		int s=0, e=0; vector<line> Q;
		for (int j=0; j<lis[i].size(); j++) {
			while (s<lis[i-1].size()&&lis[i-1][s].se>lis[i][j].se) s++;
			while (e<lis[i-1].size()&&lis[i-1][e].fi<lis[i][j].fi) e++;
			Q.eb(lis[i][j], s, e-1, j);
		}
		A[i].assign(lis[i].size(), 1ll<<60);
		sol(i, 0, lis[i-1].size()-1, Q);
	}
	cout<<A[M][0]<<'\n';
	return 0;
}