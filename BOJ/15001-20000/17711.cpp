#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef vector<int> vim;
typedef pair<int, int> pii;
 
const int sz = 700;

int N, M, Q, X[400010];
priority_queue<int> S[1010], R[1010];

inline void upd(int t) {
	for (int i=t*sz; i<min((t+1)*sz, N); i++) {
		R[t].em(-X[i]);
		X[i]=-R[t].top();
		R[t].pop();
	}
	S[t]=R[t]=priority_queue<int>();
}
 
inline void sol(int t, int &p) {
	S[t].em(p); R[t].em(-p);
	p=S[t].top(); S[t].pop();
}

inline void make(int t) { for (int i=t*sz; i<min(N, (t+1)*sz); i++) S[t].em(X[i]); }

inline int f(int s, int e, int p) {
	int st=s/sz, et=e/sz;
	if (st==et) {
		upd(st);
		for (int i=s; i<=e; i++) if (p<X[i]) swap(p, X[i]);
		make(st);
	}
	else {
		upd(st); upd(et);
		for (int i=s; i<(st+1)*sz; i++) if (p<X[i]) swap(p, X[i]);
		for (int i=st+1; i<et; i++) sol(i, p);
		for (int i=et*sz; i<=e; i++) if (p<X[i]) swap(p, X[i]);
		make(st); make(et);
	}
	return p;
}
 
int main() {
	scanf("%d %d", &N, &Q); M=(N+sz-1)/sz;
	for (int i=0; i<N; i++) scanf("%d", &X[i]), S[i/sz].em(X[i]);
	while (Q--) {
		int s, t, p;
		scanf("%d %d %d", &s, &t, &p); s--; t--;
		if (s>t) printf("%d\n", f(0, t, f(s, N-1, p)));
		else printf("%d\n", f(s, t, p));
	}
	return 0;
}