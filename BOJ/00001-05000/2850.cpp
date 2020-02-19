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

const int MOD=10007;
unordered_map<ll, int> mp[2];
char ar[15][15];
int N, M;
int y[11], z[8];
inline ll f(ll x) {
	ll ret=0;
	for (int i=0; i<=M; i++) y[i]=(x>>(3*i))&7;
	memset(z, 0, sizeof(z));
	z[1]=1;
	for (int i=0, c=2; i<=M; i++) {
		if (y[i]>1&&!z[y[i]]) z[y[i]]=c++;
		y[i]=z[y[i]];
	}
	for (int i=0; i<=M; i++) ret+=((ll)y[i]<<(3*i));
	return ret;
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i=1; i<=N; i++) scanf("%s", ar[i]+1);
	if (ar[1][1]=='#'||ar[N][M]=='#') { puts("0"); return 0; }
	mp[0][8]=1;
	for (int i=0; i<=N*M; i++) {
		mp[(i+1)%2].clear();
		for (auto &j:mp[i%2]) {
			if (i&&ar[(i+M-1)/M][(i-1)%M+1]=='#'&&((j.fi&7)!=0||(j.fi&(7ll<<(3*M)))!=0)) continue;
			if (i%M==0) {
				if (j.fi&7) continue;
				mp[(i+1)%2][f(j.fi>>3)]+=j.se%MOD;
				if ((j.fi>>3)&7) mp[(i+1)%2][f(((j.fi>>6)<<3)+(((j.fi>>3)&7ll)<<(3*M)))]+=j.se%MOD;
				if (!(j.fi&56)) mp[(i+1)%2][f((j.fi>>3)+7+((ll)7<<(3*M)))]+=j.se%MOD;
			}
			else {
				if (!(j.fi&63)) {
					mp[(i+1)%2][f(j.fi>>3)]+=j.se%MOD;
					mp[(i+1)%2][f((j.fi>>3)+7+((ll)7<<(3*M)))]+=j.se%MOD;
				}
				else if (!(j.fi&7)) {
					mp[(i+1)%2][f(j.fi>>3)]+=j.se%MOD;
					mp[(i+1)%2][f(((j.fi>>6)<<3)+(((j.fi>>3)&7)<<(3*M)))]+=j.se%MOD;
				}
				else if (!(j.fi&56)) {
					mp[(i+1)%2][f((j.fi>>3)+(j.fi&7))]+=j.se%MOD;
					mp[(i+1)%2][f((j.fi>>3)+((j.fi&7)<<(3*M)))]+=j.se%MOD;
				}
				else {
					if (ar[(i+M-1)/M][(i-1)%M+2]=='#') continue;
					if (((j.fi>>3)&7)==(j.fi&7)) continue;
					ll mn=min((j.fi>>3)&7, j.fi&7), mx=max((j.fi>>3)&7, j.fi&7), x=j.fi;
					for (int k=0; k<=M; k++) {
						if ((ll)((x>>(3*k))&7) == mx) x^=((mx^mn)<<(3*k));
					}
					mp[(i+1)%2][f((x>>6)<<3)]+=j.se%MOD;
				}
			}
		}
	}
	printf("%d\n", mp[N*M%2][1ll<<(3*M)]%MOD);
	return 0;
}