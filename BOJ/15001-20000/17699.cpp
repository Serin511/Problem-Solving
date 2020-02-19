#include <bits/stdc++.h>
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef vector<int> vim;

int N, Q;
vim C, B, A[500010], pos[500010];
vim l, r;
int Xk, Yk, lb;

inline bool Find(int L, int R, int X) {
	lb=lower_bound(all(pos[X]), L)-pos[X].begin();
	return (lb<pos[X].size()&&pos[X][lb]<=R);
}

int main() {
	scanf("%d", &N);
	C.resize(N); B.resize(N+1); l.resize(N+1); r.resize(N+1);
	for (int i=1; i<N; i++) scanf("%d", &C[i]);
	for (int i=1; i<=N; i++) {
		scanf("%d", &B[i]);
		A[i].resize(B[i]);
		for (auto &j:A[i]) scanf("%d", &j);
		for (auto &j:A[i]) pos[j].eb(i);
	}
	for (int i=1; i<=N; i++) {
		l[i]=r[i]=i;
		for (int fl; ; ) {
			fl=0;
			if (l[i]>1 && Find(l[i], r[i], C[l[i]-1])) {
				r[i]=max(r[i], r[l[i]-1]);
				l[i]=l[l[i]-1];
				fl=1;
			}
			else if (r[i]<N && Find(l[i], r[i], C[r[i]])) { r[i]++; fl=1; }
			if (!fl) break;
		}
	}
	scanf("%d", &Q);
	while (Q--) {
		scanf("%d %d", &Xk, &Yk);
		if (l[Xk]<=Yk&&Yk<=r[Xk]) puts("YES");
		else puts("NO");
	}
	return 0;
}