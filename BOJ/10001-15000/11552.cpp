#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).resize(unique(all(V))-(V).begin())
using namespace std;
typedef long long ll;
typedef vector<int> vim;
typedef pair<int, int> pii;

int M, N, P, X1[30010], X2[30010], Y1[30010], Y2[30010];
ll B, C[30010];

int Find(vim &cp, int X) { return lower_bound(all(cp), X)-cp.begin()+1; }

struct Seg {
	ll F[1<<18], lz[1<<18];
	void init() { memset(F, 0, sizeof(F)); memset(lz, 0, sizeof(lz)); }
	void spread(int i) {
		F[i]+=lz[i]; if (i<(1<<17)) lz[i*2]+=lz[i], lz[i*2+1]+=lz[i];
		lz[i]=0;
	}
	void upd(int i, int s, int e, int ts, int te, ll v) {
		spread(i);
		if (e<ts||te<s) return ;
		if (ts<=s&&e<=te) { lz[i]+=v; spread(i); return ; }
		int md=(s+e)/2;
		upd(i*2, s, md, ts, te, v); upd(i*2+1, md+1, e, ts, te, v);
		F[i]=min(F[i*2], F[i*2+1]);
	}
}S;

bool f(int X) {
	vim cp1, cp2;
	for (int i=1; i<=P; i++)
		cp1.eb(max(1, X1[i]-X+1)), cp1.eb(X2[i]), cp1.eb(X2[i]+1),
		cp2.eb(max(1, Y1[i]-X+1)), cp2.eb(Y2[i]+1);
	cp1.eb(1), cp2.eb(1), cp1.eb(N-X+1), cp2.eb(M-X+1);
	sort(all(cp1)), unq(cp1); sort(all(cp2)), unq(cp2);
	vector<pair<pii, ll> > in[1<<16];
	for (int i=1; i<=P; i++) {
		in[Find(cp2, max(1, Y1[i]-X+1))].eb(pii(Find(cp1, max(1, X1[i]-X+1)), Find(cp1, X2[i])), C[i]);
		in[Find(cp2, Y2[i]+1)].eb(pii(Find(cp1, max(1, X1[i]-X+1)), Find(cp1, X2[i])), -C[i]);
	}
	int SZ=Find(cp1, N-X+1); S.init();
	for (int i=1; i<=cp2.size(); i++) {
		if (cp2[i-1]>M-X+1) break;
		for (auto &j:in[i]) S.upd(1, 1, SZ, j.fi.fi, j.fi.se, j.se);
		if (S.F[1]<=B) return true;
	}
	return false;
}

int main() {
	scanf("%d %d %lld %d", &N, &M, &B, &P);
	for (int i=1; i<=P; i++) scanf("%d %d %d %d %lld", &X1[i], &Y1[i], &X2[i], &Y2[i], &C[i]);
	if (!f(1)) { puts("0"); return 0; }
	int s=1, e=min(M, N);
	while (s<e) {
		int md=(s+e+1)/2;
		if (f(md)) s=md;
		else e=md-1;
	}
	printf("%d\n", s);
	return 0;
}