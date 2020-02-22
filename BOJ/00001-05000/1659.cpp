#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef long long ll;
typedef vector<int> vim;
typedef pair<int,int> pii;

int N, M;

int main() {
	scanf("%d %d", &N, &M);
	vim lst(1<<20), r(N), b(M), R(N+2), B(M+2); vector<pii> ar;
	vector<ll> D(N+M+1), sr(N+M+1), sb(N+M+1);
	ar.eb(0, 0);
	for (auto &i:r) scanf("%d", &i), ar.eb(i, 0);
	for (auto &i:b) scanf("%d", &i), ar.eb(i, 1);
	sort(all(ar)); fill(all(lst), -1);
	for (int i=1; i<=N+M; i++) {
		sr[i]=sr[i-1], sb[i]=sb[i-1];
		if (!ar[i].se) sr[i]+=ar[i].fi;
		else sb[i]+=ar[i].fi;
	}

	int x=0; lst[500000]=0;
	R[0]=-(1<<30); for (int i=0; i<N; i++) R[i+1]=r[i]; R[N+1]=(2e9);
	B[0]=-(1<<30); for (int i=0; i<M; i++) B[i+1]=b[i]; B[M+1]=(2e9);
	for (int i=1; i<=N+M; i++) {
		x+=(ar[i].se?-1:1);
		int ls=lst[x+500000];
		if (!ar[i].se) {
			int lb=lower_bound(1+all(B), ar[i].fi)-B.begin();
			D[i]=D[i-1]+min((ll)B[lb]-ar[i].fi, (ll)ar[i].fi-B[lb-1]);
		}else {
			int lb=lower_bound(1+all(R), ar[i].fi)-R.begin();
			D[i]=D[i-1]+min((ll)R[lb]-ar[i].fi, (ll)ar[i].fi-R[lb-1]);
		}
		if (ls!=-1) D[i]=min(D[i], D[ls]+(ll)abs(sr[i]-sr[ls]-sb[i]+sb[ls]));
		lst[x+500000]=i;
	}
	printf("%lld\n", D.back());
}
