#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define sq(X) ((X)*(X))
#define all(V) (V).begin(), (V).end()
#define chk_init memset(chk, 0, sizeof(chk))
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

int N, A[100010], chk[100010], cy[100010];
ll C[100010], S, ans, M1[100010], M2[100010];

int main() {
	scanf("%d", &N);
	for (int i=1; i<=N; i++) scanf("%d %lld", &A[i], &C[i]), S+=C[i];

	int cnt=0;
	for (int i=1; ; i=A[i]) {
		if (chk[i]) {
			if (i==1&&cnt==N) { puts("0"); return 0; }
			break;
		}
		chk[i]=1, cnt++;
	}
	chk_init;

	for (int i=1; i<=N; i++) if (chk[i]==0) {
		int j; for (j=i; chk[j]==0; j=A[j]) chk[j]=i;
		if (chk[j]==i) for (; cy[j]==0; j=A[j]) cy[j]=1;
	}

	for (int i=1; i<=N; i++) M1[A[i]]=max(M1[A[i]], C[i]);
	for (int i=1; i<=N; i++) if (!cy[i]) M2[A[i]]=max(M2[A[i]], C[i]);

	ll mx;
	for (int i=1; i<=N; i++) {
		ans+=M1[i];
		if (cy[i]) {
			mx=M2[i]-M1[i];
			for (int j=i; cy[j]==1; j=A[j]) {
				mx=max(mx, M2[j]-M1[j]);
				cy[j]=0;
			}
			ans+=mx;
		}
	}
	printf("%lld\n", S-ans);
	return 0;
}