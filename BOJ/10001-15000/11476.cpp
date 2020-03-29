#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MX = 2005;
const double TAU = 2*M_PI;

struct angle {
	int t; double a1, a2;
	angle(int x=0) : t(x) {}
	angle(double d1, double d2) : t(0), a1(d1), a2(d2) {}
};

angle operator &(angle a1, angle a2) {
	if (a1.t<0||a2.t<0) return angle(-1);
	if (a1.t>0) return a2;
	if (a2.t>0) return a1; 
	if (a1.a1>a2.a1) swap(a1, a2);
	if (a2.a2<=a1.a2) return a2;
	if (a1.a2<a2.a1) {
		a1.a1+=TAU; a1.a2+=TAU;
		if (a1.a2<a2.a1||a2.a2<a1.a1) return angle(-1);
		return angle(max(a1.a1, a2.a1), min(a1.a2, a2.a2));
	}
	return angle(a2.a1, a1.a2);
}

ll dist(pii p1, pii p2) { return 1ll*(p2.fi-p1.fi)*(p2.fi-p1.fi)+1ll*(p2.se-p1.se)*(p2.se-p1.se); }

int N, M, C[MX][MX], D[MX];
pii P[MX];
angle A[MX][MX];

angle segm(pii p1, pii p2) {
	if (dist(p1, p2)<=1ll*M*M) return angle(1);
	double a=atan2(p2.se-p1.se, p2.fi-p1.fi);
	if (a<0) a+=TAU;
	double d=asin(M/sqrt(dist(p1, p2)));
	if (a<d) return angle(a-d+TAU, a+d+TAU);
	return angle(a-d, a+d);
}

bool chk(angle a, pii p) {
	if (a.t>0) return true;
	if (a.t<0) return false;
	double x=atan2(p.se, p.fi);
	if (x<0) x+=TAU;
	return (a.a1<=x&&x<=a.a2)||(a.a1<=x+TAU&&x+TAU<=a.a2);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N>>M;
	for (int i=1; i<=N; i++) cin>>P[i].fi>>P[i].se;
	for (int i=1; i<=N; i++) {
		A[i][i]=angle(1);
		for (int j=i+1; j<=N; j++) A[i][j]=A[i][j-1]&segm(P[i], P[j]);
		for (int j=i-1; j>=1; j--) A[i][j]=A[i][j+1]&segm(P[i], P[j]);
	}
	for (int i=1; i<=N; i++) for (int j=i+1; j<=N; j++)
		if (chk(A[i][j], pii(P[j].fi-P[i].fi, P[j].se-P[i].se))
			&&chk(A[j][i], pii(P[i].fi-P[j].fi, P[i].se-P[j].se))) C[i][j]=1;
	D[1]=1;
	for (int i=2; i<=N; i++) {
		D[i]=1e9;
		for (int j=i-1; j>=1; j--) if (C[j][i]) D[i]=min(D[i], D[j]+1);
	}
	cout<<D[N]<<'\n';
	return 0;
}