#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
using namespace std;
typedef long long ll;

int N, chk[200010], l[200010], r[200010]; ll A[200010], ans;
priority_queue<pair<ll, int> > pq;


int main() {
	scanf("%d", &N);
	for (int i=1; i<=N; i++) scanf("%lld", &A[i]), pq.em(A[i], i), l[i]=i-1, r[i]=i+1;
	A[0]=A[N+1]=-(1e16);
	for (int i=(N+1)/2; i; i--) {
		while (chk[pq.top().se]) pq.pop();
		auto k=pq.top(); pq.pop();
		ans+=k.fi; printf("%lld\n", ans);
		chk[l[k.se]]=chk[r[k.se]]=1;
		A[k.se]=A[l[k.se]]+A[r[k.se]]-A[k.se]; pq.em(A[k.se], k.se);
		l[k.se]=l[l[k.se]], r[l[k.se]]=k.se;
		r[k.se]=r[r[k.se]], l[r[k.se]]=k.se;
	}
	return 0;
}