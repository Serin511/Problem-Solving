#include <bits/stdc++.h>
#define fi first
#define se second
#define ryan bear
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
#define fastio ios::sync_with_stdio(false); cin.tie(0)
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

int N, T;
ll x[30010], y[30010], dx[30010], dy[30010];

pll operator -(pll p1, pll p2) { return pll(p1.fi-p2.fi, p1.se-p2.se); }

int ccw(pll v1, pll v2) {
	if (v1.fi*v2.se-v1.se*v2.fi > 0) return 1; //ccw
	else if (v1.fi*v2.se-v1.se*v2.fi < 0) return -1; //cw
	else return 0; //collinear
}
int ccw1(pll p1, pll p2, pll p3) { return ccw(p2-p1, p3-p1); }
int ccw2(pll p1, pll p2, pll p3, pll p4) { return ccw(p2-p1, p4-p3); }
ll sq(ll k) { return k*k; }

vector<pll> make_ch(vector<pll> P) { //convex hull
	sort(all(P)); unq(P);
	vector<pll> ch;
	for (auto &i:P) {
		while (ch.size()>1 && ccw1(ch[ch.size()-2], ch.back(), i)!=1) ch.pop_back();
		ch.eb(i);
	}
	reverse(all(P)); int tp=ch.size();
	for (auto &i:P) {
		while (tp<ch.size() && ccw1(ch[ch.size()-2], ch.back(), i)!=1) ch.pop_back();
		ch.eb(i);
	}
	ch.pop_back();
	return ch;
}

ll dist(vector<pll> P) {
	P=make_ch(P); ll ret=sq(P[0].fi-P[1].fi)+sq(P[0].se-P[1].se);
	for (int i=0, j=1; i<P.size(); i++) {
		if (i==j) j++;
		while (ccw2(P[i], P[(i+1)%P.size()], P[j], P[(j+1)%P.size()])==1) j=(j+1)%P.size();
		ret=max(ret, sq(P[i].fi-P[j].fi)+sq(P[i].se-P[j].se));
	}
	return ret;
}

ll solve(int t) {
	vector<pll> P;
	for (int i=1; i<=N; i++) P.eb(x[i]+dx[i]*t, y[i]+dy[i]*t);
	return dist(P);
}

int main() {
	scanf("%d %d", &N, &T);
	for (int i=1; i<=N; i++) scanf("%lld %lld %lld %lld", &x[i], &y[i], &dx[i], &dy[i]);
	vector<pll> p;
	int s=0, e=T, mi=0;
	while (s<e-10) {
		int m1=(s*2+e)/3, m2=(s+e*2)/3;
		ll r1=solve(m1), r2=solve(m2);
		if (r1>r2) s=m1;
		else e=m2;
	}
	pll ans=pll((1ll<<60), (1ll<<60));
	for (int i=s; i<=e; i++) ans=min(ans, pll(solve(i), (ll)i));
	printf("%lld\n%lld\n", ans.se, ans.fi);
	return 0;
}