#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define sq(X) ((X)*(X))
#define all(V) (V).begin(), (V).end()
#define chk_init memset(chk, 0, sizeof(chk))
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
const int INF = 2e9;
const int MAXN = (1<<18)+5;

int N, A[200010], C[200010], T[200010], L[200010], D[200010];

priority_queue<int, vim, greater<int> > pq[105], pp[105];
vim topop[200010][105];

int ar[105][MAXN], ret;
void init() { for (int i=0; i<=100; i++) fill(ar[i], ar[i]+MAXN, (3<<29)); }
inline void upd(int i, int t, int x) {
	while (t<=N) {
		ar[i][t]=min(ar[i][t], x);
		t += (t&-t);
	}
}
inline int get(int i, int t) {
	ret=INF;
	while (t) {
		ret=min(ret, ar[i][t]);
		t -= (t&-t);
	}
	return ret;
}

int main() {
	scanf("%d", &N); init();
	for (int i=1; i<=N; i++) scanf("%d", &A[i]), A[i]+=A[i-1];
	for (int i=1; i<=N; i++) scanf("%d", &C[i]);
	for (int i=1; i<=N; i++) scanf("%d", &T[i]);
	for (int i=1; i<=N; i++) scanf("%d", &L[i]);
	for (int i=1; i<=N; i++) {
		D[i]=INF;
		
		pq[C[i]+50].em(D[i-1]+T[i]-C[i]*A[i-1]);
		if (i+L[i]<=N) topop[i+L[i]][C[i]+50].eb(D[i-1]+T[i]-C[i]*A[i-1]);
		for (int j=0; j<=100; j++) {
			for (auto &k:topop[i][j]) pp[j].em(k);
			while ((!pq[j].empty()) && (!pp[j].empty()) && pq[j].top()==pp[j].top()) { pq[j].pop(); pp[j].pop(); }
			if (!pq[j].empty()) D[i]=min(D[i], (j-50)*A[i]+pq[j].top());
		}

		for (int j=0; j<=100; j++) upd(j, N-i+1, D[i-1]-(j-50)*A[i-1]);
		D[i]=min(D[i], get(C[i]+50, N-max(1, i-L[i]+1)+1)+C[i]*A[i]+T[i]);
	}
	printf("%d\n", D[N]);
	return 0;
}