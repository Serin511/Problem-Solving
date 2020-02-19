#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef vector<int> vim;
typedef pair<int, int> pii;

const int MAX=400;

int N, M, Q, ans[100010], chk[100010], ar[100010];
vim adj[100010], qu[100010], C[100010];
vector<pii> B[100010];

int main() {
	scanf("%d %d %d", &N, &M, &Q);
	for (int i=0, u, v; i<M; i++) scanf("%d %d", &u, &v), adj[v].eb(u);
	for (int i=1, t, y; i<=Q; i++) {
		scanf("%d %d", &t, &y); qu[t].eb(i);
		C[i].resize(y); for (auto &j:C[i]) scanf("%d", &j);
	}
	for (int i=1; i<=N; i++) {
		B[i].eb(0, i);
		for (auto &j:adj[i]) {
			vector<pii> im;
			int b=0;
			for (auto &k:B[i]) {
				while (b<B[j].size()&&k.fi<B[j][b].fi+1&&im.size()<MAX) {
					if (!chk[B[j][b].se]) im.eb(B[j][b].fi+1, B[j][b].se), chk[B[j][b].se]=1;
					b++;
				}
				if (im.size()>=MAX) break;
				if (!chk[k.se]) im.eb(k), chk[k.se]=1;
			}
			for (auto &k:im) chk[k.se]=0;
			swap(B[i], im);
		}
		for (auto &j:qu[i]) {
			ans[j]=-1;
			for (auto &k:C[j]) chk[k]=1;
			if (B[i].size()<MAX||C[j].size()<MAX) {
				for (auto &k:B[i]) if (!chk[k.se]) { 
					ans[j]=k.fi;
					break;
				}
			}
			else {
				for (int k=1; k<=i; k++) {
					ar[k]=(chk[k]?-1e6:0);
					for (auto &l:adj[k]) ar[k]=max(ar[k], ar[l]+1);
				}
				if (ar[i]>=0) ans[j]=ar[i];
			}
			for (auto &k:C[j]) chk[k]=0;
		}
	}
	for (int i=1; i<=Q; i++) printf("%d\n", ans[i]);
	return 0;
}