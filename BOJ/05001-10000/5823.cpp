#include <bits/stdc++.h>
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
 
int N, L, X[150010], im[150010], Q;
int A[410][810], sz[410];
int B[410][810], C[410][810];
 
void myinit() {
	for (int i=0, k=0; i<=N/400; i++) for (int j=0; j<sz[i]; j++) im[k++]=A[i][j];
	memset(sz, 0, sizeof(sz));
	for (int i=0; i<N; i++) A[i/400][sz[i/400]++]=im[i];
	for (int i=0; i<=N/400; i++) for (int j=sz[i]-1, k=sz[i]-1; j>=0; j--) {
		while (k&&A[i][k-1]>A[i][j]+L) k--;
		if (A[i][j]+L>=A[i][k]) B[i][j]=A[i][j], C[i][j]=1;
		else B[i][j]=B[i][k], C[i][j]=C[i][k]+1;
	}
}

void init(int N_, int L_, int X_[]) {
	N=N_; L=L_; for (int i=0; i<N; i++) { X[i]=X_[i]; A[i/400][sz[i/400]++]=X[i]; }
	for (int i=0; ; i++) if (!sz[i]) { A[i][0]=(1<<30); break; }
	myinit();
}

void del(int I, int J) {
	for (int i=J+1; i<sz[I]; i++) A[I][i-1]=A[I][i];
	sz[I]--;
	if (!sz[I]) A[I][0]=(1<<30);
	for (int i=sz[I]-1, j=sz[I]-1; i>=0; i--) {
		while (j&&A[I][j-1]>A[I][i]+L) j--;
		if (A[I][i]+L>=A[I][j]) B[I][i]=A[I][i], C[I][i]=1;
		else B[I][i]=B[I][j], C[I][i]=C[I][j]+1;
	}
}

void ins(int I, int V) {
	int k; for (k=sz[I]-1; k>=0; k--) {
		if (A[I][k]<=V) { A[I][k+1]=V; break; }
		A[I][k+1]=A[I][k];
	}
	if (k<0) A[I][0]=V;
	sz[I]++;
	for (int i=sz[I]-1, j=sz[I]-1; i>=0; i--) {
		while (j&&A[I][j-1]>A[I][i]+L) j--;
		if (A[I][i]+L>=A[I][j]) B[I][i]=A[I][i], C[I][i]=1;
		else B[I][i]=B[I][j], C[I][i]=C[I][j]+1;
	}
}

int update(int I, int Y) {
	Q++;
	if (Q%399==0) myinit();
	for (int i=0; i<=N/400; i++) if (sz[i] && X[I]<A[i+1][0]) {
		del(i, lower_bound(A[i], A[i]+sz[i], X[I])-A[i]);
		break;
	}
	for (int i=0; i<=N/400; i++) if (sz[i] && Y<=A[i+1][0]) {
		ins(i, Y);
		break;
	}
	X[I]=Y;
	int lst=-L-10, ans=0;
	for (int i=0; i<=N/400; i++) if (sz[i]) {
		int ub=upper_bound(A[i], A[i]+sz[i], lst+L)-A[i];
		if (ub>=sz[i]) continue;
		ans+=C[i][ub]; lst=B[i][ub];
	}
	return ans;
}

int n_, l_, m_;
int x_[150010];

int main() {
	scanf("%d %d %d", &n_, &l_, &m_);
	for (int i=0; i<n_; i++) scanf("%d", &x_[i]);
	init(n_, l_, x_);
	while (m_--) {
		int i, y;
		scanf("%d %d", &i, &y);
		printf("%d\n", update(i, y));
	}
	return 0;
}