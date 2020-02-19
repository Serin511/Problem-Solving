#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#define em emplace
using namespace std;
typedef long long ll;

char s[65];
int N, K;
ll B[1000010], stk[6000100], f, e;
unordered_set<ll> S;

inline void getnum(ll &x) {
	x=0; scanf("%s", s);
	for (int i=0; i<N; i++) if (s[i]=='1') x|=(1ll<<(N-i-1));
}

inline bool Find(ll x) { return *lower_bound(B, B+K, x)==x; }

void solve(ll u, ll v) {
	S.clear(); S.em(u); f=e=0; stk[e++]=u;
	for (f=0; f<e&&e<K*10+10000; f++) {
		if (stk[f]==v) return ;
		for (int j=0; j<N; j++) if (S.find(stk[f]^(1ll<<j))==S.end() && !Find(stk[f]^(1ll<<j))) {
			stk[e++]=stk[f]^(1ll<<j), S.em(stk[f]^(1ll<<j));
		}
	}
	if (e>=K*10+10000) return ;
	puts("NIE"); exit(0);
}

int main() {
	scanf("%d %d", &N, &K);
	ll u, v; getnum(u), getnum(v);
	for (int i=0; i<K; i++) getnum(B[i]);
	sort(B, B+K); B[K]=-1;
	solve(u, v); solve(v, u);
	puts("TAK");
	return 0;
}