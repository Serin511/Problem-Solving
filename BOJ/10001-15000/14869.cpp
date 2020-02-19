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

int N, M, S, E, T;
vim ar[3010]; int ban[3010]; deque<pii> dq[3010];
int Dp[3010][3010];
int get(int i, int s, int e) { return s?(ar[i][e]-ar[i][s-1]):ar[i][e]; }

int main() {
	scanf("%d %d %d %d %d", &N, &M, &S, &E, &T);
	for (int i=1; i<=N; i++) {
		ar[i].resize(M+1);
		for (int j=1; j<=M; j++) { scanf("%d", &ar[i][j]); ar[i][j]+=ar[i][j-1]; }
	}
	for (int i=1; i<=N; i++) scanf("%d", &ban[i]);
	for (int i=2; i<=S; i++) for (int j=1; j<=N; j++) Dp[j][i]=(3<<29);
	for (int i=S+1; i<=M; i++) {
		pii m1, m2, m3, im; m1=m2=m3=pii((3<<29), (3<<29));
		for (int j=1; j<=N; j++) {
			while (!dq[j].empty()&&dq[j].front().fi<i-E) dq[j].pop_front();
			while (!dq[j].empty()&&dq[j].back().se+get(j, dq[j].back().fi, i-1)>=Dp[j][i-S]+get(j, i-S, i-1)) dq[j].pop_back();
			dq[j].eb(i-S, Dp[j][i-S]);

			im=pii(dq[j].front().se+get(j, dq[j].front().fi, i-1), j);
			if (im.fi<=m1.fi) { m3=m2; m2=m1; m1=im; }
			else if (im.fi<=m2.fi) { m3=m2; m2=im; }
			else if (im.fi<=m3.fi) m3=im;
		}
		for (int j=1; j<=N; j++) {
			if (m1.se==j||m1.se==ban[j]) {
				if (m2.se==j||m2.se==ban[j]) Dp[j][i]=m3.fi+T;
				else Dp[j][i]=m2.fi+T;
			}
			else Dp[j][i]=m1.fi+T;
		}
	}
	int ans=(3<<29);
	for (int i=M-E+1; i<=M; i++) for (int j=1; j<=N; j++) ans=min(ans, Dp[j][i]+get(j, i, M));
	printf("%d\n", ans);
	return 0;
}