#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define sq(X) ((X)*(X))
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
const int MAX = (1<<30);

int N, M, K;
pii s[250010], e[250010]; ll cost[250010], ans[250010]; int used[250010];
priority_queue<pair<ll, pii>, vector<pair<ll, pii> >, greater<pair<ll, pii> > > pq;
vim V;

struct seg1 {
	int seg[(1<<20)];
	void upd(int i, int s, int e, int t, int val) {
		if (s==e) { seg[i]=val; return ; }
		int md=(s+e)/2;
		if (t<=md) upd(i*2, s, md, t, val);
		else upd(i*2+1, md+1, e, t, val);
		seg[i]=min(seg[i*2], seg[i*2+1]);
	}
	int get(int i, int s, int e, int ts, int te) {
		if (e<ts||te<s) return MAX;
		if (ts<=s&&e<=te) return seg[i];
		int md=(s+e)/2;
		return min(get(i*2, s, md, ts, te), get(i*2+1, md+1, e, ts, te));
	}
}S1;

struct seg2 {
	vim seg[(1<<20)];
	void upd(int i, int s, int e, int ts, int te, int val) {
		if (e<ts||te<s) return ;
		if (ts<=s&&e<=te) { seg[i].eb(val); return ; }
		int md=(s+e)/2;
		upd(i*2, s, md, ts, te, val); upd(i*2+1, md+1, e, ts, te, val);
	}
	void get(int i, int s, int e, int t) {
		for (auto &j:seg[i]) {
			if (used[j]) continue;
			used[j]=1;
			V.eb(j);
		}
		seg[i].clear();
		if (s==e) return ;
		int md=(s+e)/2;
		if (t<=md) get(i*2, s, md, t);
		else get(i*2+1, md+1, e, t);
	}
}S2;

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i=1; i<=N; i++) S1.upd(1, 1, N, i, i);
	for (int i=1; i<=M; i++) {
		scanf("%lld %d %d %d %d", &cost[i], &s[i].fi, &s[i].se, &e[i].fi, &e[i].se);
		S2.upd(1, 1, N, s[i].fi, s[i].se, i);
	}
	pq.em(0, pii(K, K)); fill(ans, ans+N+1, -1);
	while (!pq.empty()) {
		auto k=pq.top(); pq.pop();
		for (int i=S1.get(1, 1, N, k.se.fi, k.se.se); i<=k.se.se; i=S1.get(1, 1, N, k.se.fi, k.se.se)) {
			ans[i]=k.fi; S1.upd(1, 1, N, i, MAX);
			V.clear(); S2.get(1, 1, N, i);
			for (auto &j:V) pq.em(k.fi+cost[j], pii(e[j].fi, e[j].se));
		}
	}
	for (int i=1; i<=N; i++) printf("%lld ", ans[i]); puts("");
	return 0;
}