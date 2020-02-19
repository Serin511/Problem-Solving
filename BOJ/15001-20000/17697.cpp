#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;
typedef vector<int> vim;

int N, K, Q, V[100010];
int S[100010][20], E[100010][20];

int main() {
	scanf("%d %d %d", &N, &K, &Q);
	for (int i=1; i<=N; i++) scanf("%d", &V[i]);
	vim st;
	for (int i=1; i<=N; i++) {
		while (!st.empty()&&V[st.back()]<V[i]) st.pop_back();
		S[i][0]=st.empty()?i:st.back();
		st.eb(i);
	}st.clear();
	for (int i=N; i>=1; i--) {
		while (!st.empty()&&V[st.back()]<V[i]) st.pop_back();
		E[i][0]=st.empty()?i:st.back();
		st.eb(i);
	}
	for (int j=1; j<20; j++) for (int i=1; i<=N; i++) {
		S[i][j]=min(S[S[i][j-1]][j-1], S[E[i][j-1]][j-1]);
		E[i][j]=max(E[S[i][j-1]][j-1], E[E[i][j-1]][j-1]);
	}
	while (Q--) {
		int A, B, C=0; scanf("%d %d", &A, &B); if (A>B) swap(A, B);
		for (int i=19, L=A; i>=0; i--) if (max(E[L][i], E[A][i])<B) {
			int u=min(S[L][i], S[A][i]), v=max(E[L][i], E[A][i]);
			L=u, A=v; C+=(1<<i);
		}
		for (int i=19, R=B; i>=0; i--) if (A<min(S[B][i], S[R][i])) {
			int u=min(S[B][i], S[R][i]), v=max(E[B][i], E[R][i]);
			B=u, R=v; C+=(1<<i);
		}
		printf("%d\n", C);
	}
	return 0;
}