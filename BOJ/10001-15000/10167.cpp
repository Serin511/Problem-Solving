#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#define fi first
#define se second
#define ryan bear
#define sq(X) ((X)*(X))
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

int N, M; vim cpx, cpy;
vector<pair<pii, ll> > P;

ll lm[(1<<16)], rm[(1<<16)], am[(1<<16)], val[(1<<16)];
ll ans;
void init() {
	memset(lm, 0, sizeof(lm));
	memset(rm, 0, sizeof(rm));
	memset(am, 0, sizeof(am));
	memset(val, 0, sizeof(val));
}

void upd(int i, int t, int s, int e, ll v) {
	if (s==e) {
		val[i]+=v;
		lm[i]=max(0ll, val[i]); rm[i]=max(0ll, val[i]); am[i]=max(0ll, val[i]);
		return ;
	}
	int md=(s+e)/2;
	if (t<=md) 	upd(i*2  , t,    s, md, v);
	else		upd(i*2+1, t, md+1,  e, v);
	lm[i]=max(lm[i*2], val[i*2]+lm[i*2+1]);
	rm[i]=max(rm[i*2+1], val[i*2+1]+rm[i*2]);
	am[i]=max({am[i*2], am[i*2+1], rm[i*2]+lm[i*2+1]});
	val[i]=val[i*2]+val[i*2+1];
}

void solve(int st) {
	init();
	for (int i=st; i<N; i++) {
		int j;
		for (j=i; j<N; j++) {
			if (P[i].fi.fi!=P[j].fi.fi) break;
			upd(1, P[j].fi.se, 0, M, P[j].se);
		}
		i=j-1; ans=max(ans, am[1]);
	}
}

int main() {
	scanf("%d", &N); P.resize(N);
	for (auto &i:P) {
		scanf("%d %d %lld", &i.fi.fi, &i.fi.se, &i.se);
		cpx.eb(i.fi.fi), cpy.eb(i.fi.se);
	}
	sort(all(cpx)); unq(cpx); sort(all(cpy)); unq(cpy); M=cpy.size();
	for (int i=0; i<N; i++) {
		P[i].fi.fi=lower_bound(all(cpx), P[i].fi.fi)-cpx.begin();
		P[i].fi.se=lower_bound(all(cpy), P[i].fi.se)-cpy.begin();
	}
	sort(all(P));
	for (int i=0; i<N; i++) {
		solve(i);
		int j; for (j=i; j<N; j++) if (P[i].fi.fi!=P[j].fi.fi) break;
		i=j-1;
	}
	printf("%lld\n", ans);
	return 0;
}