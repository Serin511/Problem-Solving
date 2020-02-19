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
const int MAXN = 1010101;

int N, B, C;
int arr[MAXN];
int cnt[MAXN][3];
ll ans;

int main(){
	scanf("%d %d %d", &N, &B, &C);
	for(int i=1;i<=N;i++) scanf("%d",&arr[i]);
	if (B<=C) {
		for (int i=1; i<=N; i++) ans+=(ll)arr[i]*B;
		printf("%lld\n", ans);
		return 0;
	}
	for(int i=1;i<=N;i++){
		int v;
		v=min(arr[i], cnt[i-1][2]);
		arr[i]-=v; cnt[i-1][2]-=v; cnt[i][1]+=v;
		v=min(arr[i], cnt[i-1][1]);
		arr[i]-=v; cnt[i-1][1]-=v; cnt[i][0]+=v;
		
		cnt[i][2]=arr[i];
	}
	for (int i=1; i<=N; i++) ans+=(ll)cnt[i][0]*(B+2*C)+(ll)cnt[i][1]*(B+C)+(ll)cnt[i][2]*B;
	printf("%lld\n",ans);
	return 0;
}