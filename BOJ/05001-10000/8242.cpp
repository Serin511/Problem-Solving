#include <bits/stdc++.h>
using namespace std;

int N, M;
int T[100010], J[100010], I[100010];
int mx[100010], mn[100010], A[100010];
int s[100010], e[100010];

bool ch(int X) {
	for (int i=1; i<=N; i++) mx[i]=0, mn[i]=1e9;
	for (int i=1; i<=M; i++) A[i]=s[i]=e[i]=0;
	for (int i=1; i<=X; i++) {
		if (A[T[i]]&&A[T[i]]!=I[i]+1) return 0;
		A[T[i]]=I[i]+1;
		mx[J[i]]=max(mx[J[i]], T[i]);
		mn[J[i]]=min(mn[J[i]], T[i]);
	}
	int fr=0, nfr=0, con=0, en=0, pull=0;
	for (int i=1; i<=N; i++) {
		if (mx[i]) nfr++, s[mn[i]]++, e[mx[i]]++;
		else fr++;
	}
	for (int i=1; i<=M; i++) {
		if (!A[i]) continue;
		con+=s[i]; pull-=s[i];
		if (pull<0) nfr+=pull, pull=0;
		if (A[i]>pull+con+en) nfr-=A[i]-con-en-pull, pull=A[i]-con-en;
		if (A[i]<pull+con+en) {
			if (A[i]<con) return 0;
			en=A[i]-con-pull;
			if (en<0) {
				nfr+=con+pull-A[i], fr-=con+pull-A[i];
				pull=A[i]-con, en=0;
			}
		}
		con-=e[i], en+=e[i];
	}
	return (fr>=0&&nfr+fr>=0);
}

void sol() {
	cin>>N>>M;
	for (int i=1; i<=M; i++) cin>>T[i]>>J[i]>>I[i];
	int s=1, e=M;
	while (s<e) {
		int md=(s+e+1)/2;
		if (ch(md)) s=md;
		else e=md-1;
	}
	cout<<s<<'\n';
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int Z; cin>>Z;
	while (Z--) sol();
	return 0;
}