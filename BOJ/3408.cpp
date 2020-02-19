#include <bits/stdc++.h>
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef vector<int> vim;

int N, M, A[200010], S[200010], E[200010];
vim cp, P[200010];

bool f(int s, int e) {
	if (s>=e) return true;
	int md=(s+e)/2;
	for (int i=s, j=e; i<=j; i++, j--) {
		if (S[i]<=s&&e<=E[i]) return f(s, i-1)&f(i+1, e);
		if (S[j]<=s&&e<=E[j]) return f(s, j-1)&f(j+1, e);
	}
	return false;
}

void solve() {
	cp.clear();
	scanf("%d", &N);
	for (int i=1; i<=N; i++) scanf("%d", &A[i]), cp.eb(A[i]);
	sort(all(cp)); unq(cp);
	for (int i=1; i<=cp.size(); i++) P[i].clear(), P[i].eb(0);
	for (int i=1; i<=N; i++) A[i]=lower_bound(all(cp), A[i])-cp.begin()+1, P[A[i]].eb(i);
	for (int i=1; i<=cp.size(); i++) {
		P[i].eb(N+1);
		for (int j=1; j<P[i].size()-1; j++) S[P[i][j]]=P[i][j-1]+1, E[P[i][j]]=P[i][j+1]-1;
	}
	printf("%s\n", f(1, N)?"non-boring":"boring");
}

int main() {
	int T; scanf("%d", &T);
	while (T--) solve();
	return 0;
}