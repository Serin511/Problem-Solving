#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef vector<int> vim;

const int sz=300005;

int N, M, Q; vim O[sz], qu[sz];
int L[sz], R[sz], s[sz], e[sz];
ll P[sz], A[sz];

ll ar[300010];
void init() { memset(ar, 0, sizeof(ar)); }
void upd(int t, ll v) { while (t<=M) ar[t]+=v, t+=t&-t; }
void lz(int l, int r, ll v) {
	upd(l, v), upd(r+1, -v);
	if (l>r) upd(1, v);
}
ll get(int t) { ll ret=0; while (t) ret+=ar[t], t-=t&-t; return ret; }

int main() {
	scanf("%d %d", &N, &M);
	for (int i=1, j; i<=M; i++) scanf("%d", &j), O[j].eb(i);
	for (int i=1; i<=N; i++) scanf("%lld", &P[i]);
	scanf("%d", &Q);
	for (int i=1; i<=N; i++) s[i]=1, e[i]=Q+1;
	for (int i=1; i<=Q; i++) scanf("%d %d %lld", &L[i], &R[i], &A[i]);

	for (int w=1; w<=19; w++) {
		init();
		for (int i=1; i<=Q+1; i++) qu[i].clear();
		for (int i=1; i<=N; i++) if (s[i]<e[i]) qu[(s[i]+e[i])/2].eb(i);
		for (int i=1; i<=Q; i++) {
			lz(L[i], R[i], A[i]);
			for (auto &j:qu[i]) {
				ll l=0;
				for (auto &k:O[j]) l+=get(k), l=min(l, P[j]);
				if (l>=P[j]) e[j]=i;
				else s[j]=i+1;
			}
		}
	}
	for (int i=1; i<=N; i++) {
		if (s[i]<=Q) printf("%d\n", s[i]);
		else puts("NIE");
	}
	return 0;
}