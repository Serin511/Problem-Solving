#include <bits/stdc++.h>
using namespace std;

const int SZ=10000000;

int val[SZ], l[SZ], r[SZ];
int nd_tp=1; int new_node() { return nd_tp++; }

int N, M;
int P[500010], rt[500010];

inline void upd(int nw, int rf, int s, int e, int t) {
	if (s==e) { val[nw]=val[rf]+1; return ; }
	int md=(s+e)/2;
	if (t<=md) {
		l[nw]=new_node(); r[nw]=r[rf];
		upd(l[nw], l[rf], s, md, t);
	}
	else {
		r[nw]=new_node(); l[nw]=l[rf];
		upd(r[nw], r[rf], md+1, e, t);
	}
	val[nw]=val[rf]+1;
}

inline int find_kth(int n1, int n2, int s, int e, int k) {
	if (s==e) return s;
	int md=(s+e)/2;
	if (val[l[n2]]-val[l[n1]]>=k) return find_kth(l[n1], l[n2], s, md, k);
	else return find_kth(r[n1], r[n2], md+1, e, k-val[l[n2]]+val[l[n1]]);
}

inline int get(int nw, int s, int e, int t) {
	if (!nw) return 0;
	if (s==e) return val[nw];
	int md=(s+e)/2;
	if (t<=md) return get(l[nw], s, md, t);
	else return get(r[nw], md+1, e, t);
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i=1; i<=N; i++) {
		scanf("%d", &P[i]);
		rt[i]=new_node();
		upd(rt[i], rt[i-1], 1, N, P[i]);
	}
	for (int i=1, s, e; i<=M; i++) {
		scanf("%d %d", &s, &e);
		int im=find_kth(rt[s-1], rt[e], 1, N, (e-s+1)/2+1);
		if (get(rt[e], 1, N, im)-get(rt[s-1], 1, N, im)>=(e-s+1)/2+1) printf("%d\n", im);
		else puts("0");
	}
	return 0;
}