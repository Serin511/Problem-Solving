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
const ll INF = (1ll<<60);

int N, K; vlm ar; ll mx; int mi; int lst[205][100010];

struct line {
	ll a, b; int ind;
	ll get(ll x) { return a*x+b; }
	line() {}
	line(ll A, ll B, int i) { a=A, b=B, ind=i; }
};

struct CHT {
	line L[100010]; int s, e;
	void init() { s=e=0; }
	void upd(line &v) {
		while (s+1<e && (L[e-1].b<v.b || (L[e-2].b-v.b)*(L[e-1].a-L[e-2].a)<=(L[e-2].b-L[e-1].b)*(v.a-L[e-2].a))) e--;
		L[e++]=v;
	}
	pll get(ll x) {
		while (s+1<e && L[s].get(x)<L[s+1].get(x)) s++;
		return pll(L[s].get(x), L[s].ind);
	}
}cht[2];

void dfs(int k, int i) {
	if (!k) return ;
	dfs(k-1, lst[k][i]);
	printf("%d ", i);
}

int main() {
	scanf("%d %d", &N, &K); ar.resize(N+1);
	for (int i=1; i<=N; i++) { scanf("%lld", &ar[i]); ar[i]+=ar[i-1]; }
	line im=line(ar[N], 0, 0);
	cht[0].init(); cht[0].upd(im);
	for (int i=1; i<K; i++) {
		cht[i&1].init();
		for (int j=i; j<N; j++) {
			auto k=cht[(i-1)&1].get(ar[j]); k.fi-=ar[j]*ar[j];
			lst[i][j]=min((int)k.se, j-1);
			im=line(ar[N]+ar[j], k.fi-ar[N]*ar[j], j);
			cht[i&1].upd(im);
		}
	}
	for (int i=K; i<N; i++) {
		auto k=cht[(K-1)&1].get(ar[i]);
		lst[K][i]=min((int)k.se, i-1);
		if (mx<=k.fi-ar[i]*ar[i]) mx=k.fi-ar[i]*ar[i], mi=i;
	}
	printf("%lld\n", mx);
	dfs(K, mi); puts("");
	return 0;
}