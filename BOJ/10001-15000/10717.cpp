#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef long long ll;
typedef vector<int> vim;
typedef pair<int, int> pii;

int H, W, L, P; ll ans;
vim V1[4005], V2[4005];

struct Seg {
	int ar[1<<13][4005], tp[1<<13];
	void init() { memset(tp, 0, sizeof(tp)); }
	void upd(int i, int s, int e, int ts, int te, int v) {
		if (te<s||te<ts||e<s||e<ts) return ;
		if (ts<=s&&e<=te) { ar[i][tp[i]++]=v; return ; }
		int md=(s+e)/2;
		upd(i*2, s, md, ts, te, v); upd(i*2+1, md+1, e, ts, te, v);
	}
	int get(int i, int s, int e, int t, int v) {
		int x=lower_bound(ar[i], ar[i]+tp[i], v)-ar[i]; x=tp[i]-x;
		if (s==e) return x;
		int md=(s+e)/2;
		if (t<=md) return x+get(i*2, s, md, t, v);
		else return x+get(i*2+1, md+1, e, t, v);
	}
}S;

void solve(int x) {
	vim a1, a2;
	vector<pii> P; S.init();
	for (int i=max(1, x+1); i<=min(H, x+W); i++) if (1<=i-x&&i-x<=W) P.eb(i, i-x);
	for (auto &i:P) {
		int l1=lower_bound(all(V1[i.fi]), i.se)-V1[i.fi].begin();
		int l2=lower_bound(all(V2[i.se]), i.fi)-V2[i.se].begin();
		a1.eb(min((l1<V1[i.fi].size()?V1[i.fi][l1]:(W+1))-i.se, (l2<V2[i.se].size()?V2[i.se][l2]:(H+1))-i.fi));
		a2.eb((l1<V1[i.fi].size()&&V1[i.fi][l1]==i.se)?0:min(i.se-(l1?V1[i.fi][l1-1]:0), i.fi-(l2?V2[i.se][l2-1]:0)));
	}
	for (int i=0; i<P.size(); i++) {
		if (a1[i]>=L) S.upd(1, 1, P.size(), i+L, i+a1[i], i+1);
		if (a2[i]>=L) ans+=(ll)S.get(1, 1, P.size(), i+1, i-a2[i]+2);
	}
}

int main() {
	scanf("%d %d %d %d", &H, &W, &L, &P);
	for (int i=0, u, v; i<P; i++) scanf("%d %d", &u, &v), V1[u].eb(v), V2[v].eb(u);
	for (int i=1; i<=H; i++) sort(all(V1[i]));
	for (int i=1; i<=W; i++) sort(all(V2[i]));
	for (int i=H-1; i>=1-W; i--) solve(i);
	printf("%lld\n", ans);
	return 0;
}