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

const ll MOD=1e9+7;
int N; ll ans=1; vector<pii> V;
map<int, int> mp;

vim par;
int get(int x) { return par[x]==-1?x:par[x]=get(par[x]); }
void Union(int x, int y) { x=get(x), y=get(y); if (x!=y) par[y]=x; }

int main() {
	scanf("%d", &N); V.resize(N); par.resize(2*N); fill(all(par), -1);
	for (auto &i:V) scanf("%d %d", &i.fi, &i.se);
	sort(all(V));
	for (int i=0; i<N; i++) {
		auto s=mp.lower_bound(V[i].fi), e=mp.upper_bound(V[i].se);
		if (e!=mp.begin()) for (; s!=e; ++s) {
			Union(i, s->se+N);
			Union(i+N, s->se);
			if (get(s->se)==get(prev(e)->se)) break;
		}
		mp[V[i].se]=i;
	}
	for (int i=0; i<N; i++) if (get(i)==get(i+N)) { puts("0"); return 0; }
	for (int i=0; i<N; i++) if (get(i)==i) ans=ans*2%MOD;
	printf("%lld\n", ans);
	return 0;
}