#include <bits/stdc++.h>
#define fi first
#define se second
#define ryan bear
#define all(V) ((V).begin()), ((V).end())
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;
typedef vector<int> vim;
typedef vector<ll> vlm;
 
int N, L;
int chk[2010];
ll V[2010][2010], S[2010];
vector<pll> ar[2010];
vim ans;
 
bool cmp(pll a, pll b) {return (__int128)a.fi*b.se<(__int128)b.fi*a.se;}
 
int main() {
	scanf("%d %d", &N, &L);
	for (int i=1; i<=N; i++) for (int j=1; j<=L; j++) {
		scanf("%lld", &V[i][j]);
		V[i][j]*=N;
		S[i]+=V[i][j];
	}
	ll s;
	for (int i=1; i<=N; i++) {
		s=0;
		for (int j=1, k=1; j<=L; j++) {
			s+=V[i][j];
			while (k<=N && k*(S[i]/N)<=s) {
				ar[i].push_back({(j-1)*V[i][j]+k*(S[i]/N)-(s-V[i][j]) , V[i][j]});
				k++;
			}
		}
	}
	pll mn={0, 1}; int mi;
	for (int i=1; i<=N; i++) {
		mn={1000000, 1};
		for (int j=1; j<=N; j++) {
			if (chk[j]) continue;
			if (cmp(ar[j][i-1], mn)) mn=ar[j][i-1], mi=j;
		}
		if (i<N) printf("%lld %lld\n", mn.fi, mn.se);
		ans.push_back(mi);
		chk[mi]=1;
	}
	for (int i:ans) printf("%d ", i);
	puts("");
	return 0;
}