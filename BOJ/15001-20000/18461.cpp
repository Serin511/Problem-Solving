#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 998244353ll;

int D1[80][80], D2[80][80];
int V[80], tp;
ll A, Fc;

ll myp(ll n, ll k) {
	if (!k) return 1;
	ll r=myp(n, k/2);
	return (r*r%MOD)*(k&1?n:1)%MOD;
}
void f(int l) {
	if (!l) {
		if (tp<2||V[0]!=V[1]) return ;
		ll x=1;
		for (int i=tp-1; i>=0; i--) {
			D2[i][V[i]]=0; D1[i][V[i]]=(i<tp-1&&V[i+1]>=V[i])?D1[i+1][V[i]]+1:0;
			x=x*(D1[i][V[i]]+D2[i][V[i]]+1)%MOD;
			for (int j=V[i]-1; j; j--) {
				D2[i][j]=D2[i][j+1]+1; D1[i][j]=(i<tp-1&&V[i+1]>=j)?D1[i+1][j]+1:0;
				x=x*(D1[i][j]+D2[i][j]+1)%MOD;
			}
		}
		x=Fc*myp(x, MOD-2)%MOD;
		A=(A+x*x)%MOD;
		return ;
	}
	for (int i=1; i<=min(l, tp?V[tp-1]:l); i++) {
		V[tp++]=i; f(l-i); --tp;
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin>>N;
	Fc=1; for (int i=1; i<=N; i++) Fc=Fc*i%MOD;
	f(N);
	cout<<A<<'\n';
	return 0;
}