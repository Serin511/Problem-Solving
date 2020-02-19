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

int L, Q;
int a1[(1<<20)], a2[(1<<20)], a3[(1<<20)], a4[(1<<20)];
char s[20];

inline void f1() {
	int x, y, ans; x=y=ans=0;
	for (int i=0; i<L; i++) {
		if (s[i]=='1') x|=(1<<i);
		if (s[i]=='0') y|=(1<<i);
	}
	ans+=a3[x];
	for (int i=y; i; i=(i-1)&y) ans+=a3[i|x]*(a4[i]%2?-1:1);
	printf("%d\n", ans);
}
inline void f2() {
	int x, y, ans; x=y=ans=0;
	for (int i=0; i<L; i++) {
		if (s[i]=='0') x|=(1<<i);
		if (s[i]=='1') y|=(1<<i);
	}
	ans+=a2[x];
	for (int i=y; i; i=(i-1)&y) ans+=a2[i|x]*(a4[i]%2?-1:1);
	printf("%d\n", ans);
}
inline void f3() {
	int x, y, ans; x=y=ans=0;
	for (int i=0; i<L; i++) {
		if (s[i]=='1') x|=(1<<i);
		if (s[i]=='?') y|=(1<<i);
	}
	ans+=a1[x];
	for (int i=y; i; i=(i-1)&y) ans+=a1[i|x];
	printf("%d\n", ans);
}

int main() {
	scanf("%d %d", &L, &Q);
	for (int i=0; i<(1<<L); i++) scanf("%1d", &a1[i]);
	for (int i=0; i<(1<<L); i++) {
		if (i) a4[i]=a4[i-(i&-i)]+1;
		a2[i^((1<<L)-1)]+=a1[i];
		a3[i]+=a1[i];
	}
	for (int i=0; i<L; i++)
		for (int j=0; j<(1<<L); j++)
			if (!((j>>i)&1)) { a2[j]+=a2[j|(1<<i)]; a3[j]+=a3[j|(1<<i)]; }

	while (Q--) {
		scanf("%s", s);
		int c0=0, c1=0, cq=0;
		for (int i=0; i<L; i++) (s[i]=='0'?c0:s[i]=='1'?c1:cq)++;
		reverse(s, s+L);
		if (c0<=c1&&c0<=cq) f1();
		else if (c1<=c0&&c1<=cq) f2();
		else f3();
	}
	return 0;
}