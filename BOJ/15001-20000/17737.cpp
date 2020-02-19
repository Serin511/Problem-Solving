#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int N; pii P[200010]; ll A, S[200010];
void upd(int t, ll v) { while (t<=N) S[t]+=v, t+=t&-t; }
ll get(int t) { ll r=0; while (t) r+=S[t], t-=t&-t; return r; }

void f(int s, int e) {
	if (s==e) return ;
	int md=(s+e)/2;
	f(s, md); f(md+1, e);
	set<int> S; vector<pair<pii, int> > V;
	S.insert(N+1);
	for (int i=md, j; i>=s; i--) {
		j=*S.lower_bound(P[i].se); S.insert(P[i].se);
		V.eb(pii(P[i].se, 1), j-1);
	}S.clear();
	S.insert(0);
	for (int i=md+1, j; i<=e; i++) {
		j=*prev(S.lower_bound(P[i].se)); S.insert(P[i].se);
		V.eb(pii(j+1, 0), P[i].se);
	}
	sort(V.begin(), V.end());
	for (auto &i:V) {
		if (i.fi.se==0) upd(i.se, 1);
		if (i.fi.se==1) A+=get(i.se)-get(i.fi.fi-1);
	}
	for (auto &i:V) if (i.fi.se==0) upd(i.se, -1);
}

int main() {
	scanf("%d", &N);
	for (int i=1; i<=N; i++) scanf("%d %d", &P[i].fi, &P[i].se);
	sort(P+1, P+1+N, [](pii &p1, pii &p2){ return p1.se<p2.se; });
	for (int i=1; i<=N; i++) P[i].se=i;
	sort(P+1, P+1+N);
	f(1, N);
	printf("%lld\n", A);
	return 0;
}