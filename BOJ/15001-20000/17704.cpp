#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef vector<int> vim;
typedef pair<int, int> pii;

struct Seg {
	int ar[(1<<19)];
	void upd(int i, int s, int e, int t, int v) {
		if (s==e) { ar[i]=max(ar[i], v); return ; }
		int md=(s+e)/2;
		if (t<=md) upd(i*2, s, md, t, v);
		else upd(i*2+1, md+1, e, t, v);
		ar[i]=max(ar[i*2], ar[i*2+1]);
	}
	int get(int i, int s, int e, int ts, int te) {
		if (e<ts||te<s) return 0;
		if (ts<=s&&e<=te) return ar[i];
		int md=(s+e)/2;
		return max(get(i*2, s, md, ts, te), get(i*2+1, md+1, e, ts, te));
	}
}S;

int N, Q, A[200010], B[200010], ans[200010];
pii P[200010];
vim cp1, cp2, pn[200010]; vector<pii> qu[200010];

int main() {
	scanf("%d %d", &N, &Q);
	for (int i=1; i<=N; i++) scanf("%d %d", &P[i].fi, &P[i].se), cp1.eb(P[i].fi), cp2.eb(P[i].se);
	sort(all(cp1)); unq(cp1); sort(all(cp2)); unq(cp2);
	for (int i=1; i<=N; i++) P[i].fi=lower_bound(all(cp1), P[i].fi)-cp1.begin()+1, P[i].se=lower_bound(all(cp2), P[i].se)-cp2.begin()+1;
	sort(P+1, P+N+1);
	for (int i=1; i<=N; i++) pn[P[i].fi].eb(P[i].se);
	for (int i=1; i<=Q; i++) {
		scanf("%d %d", &A[i], &B[i]);
		A[i]=lower_bound(all(cp1), A[i])-cp1.begin()+1; B[i]=upper_bound(all(cp2), B[i])-cp2.begin();
		qu[A[i]].eb(B[i], i);
	}
	for (int i=cp1.size(); i; i--) {
		for (auto &j:pn[i]) {
			int im=S.get(1, 1, cp2.size(), 1, j);
			S.upd(1, 1, cp2.size(), j, im+1);
		}
		for (auto &j:qu[i]) ans[j.se]=S.get(1, 1, cp2.size(), 1, j.fi);
	}
	for (int i=1; i<=Q; i++) printf("%d\n", ans[i]);
	return 0;
}