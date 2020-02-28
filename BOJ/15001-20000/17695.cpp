#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef pair<int, ll> pil;

int N, M, I; vector<pil> Q[200010];
ll mx, A[200010], D[200010];

bool f(ll m, ll n) {
	if (n>m) return false;
	priority_queue<pil> S; ll C=0;
	memset(D, 0, sizeof(D));
	for (int i=1; i<=I; i++) {
		for (auto &j:Q[i]) if (j.fi>I) S.em(j);
		while (A[i]+n-2*C>m) {
			if (!S.size()) return false;
			auto k=S.top(); S.pop();
			ll l=min(k.se, (A[i]+n-m+1)/2-C);
			C+=l, D[k.fi]+=l;
			if (k.se>l) S.em(k.fi, k.se-l);
		}
	}
	for (int i=I+1; i<=N; i++) {
		C-=D[i];
		if (A[i]+n-2*C>m) return false;
	}
	return true;
}

int main() {
	cin>>N>>M;
	for (int i=0, a, b, c; i<M; i++) {
		cin>>a>>b>>c;
		if (a>b) swap(a, b);
		Q[a].eb(b, c);
		A[a]+=c, A[b]-=c;
	}
	for (int i=1; i<=N; i++) {
		A[i]+=A[i-1];
		if (mx<A[i]) mx=A[i], I=i;
	}
	ll s=0, e=mx;
	while (s<e) {
		ll md=(s+e)/2;
		if (f(md, mx-md)||f(md, mx-md+1)) e=md;
		else s=md+1;
	}
	cout<<s<<'\n';
	return 0;
}