#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;

struct line {
	ll a, b, c; int cnt;
	ll get(ll x, ll y) { return a*x+b*y+c; }
	line() {}
	line(ll A, ll B, ll C, int i) { a=A, b=B, c=C, cnt=i; }
};

int N, K;
ll V[50010], D[50010]; int C[50010];

int cross(line &v1, line &v2) {
	int s=0, e=N, md;
	while (s+1<e) {
		md=(s+e)/2;
		if (v1.get(md, V[md])<v2.get(md, V[md])) s=md;
		else e=md;
	}
	return s;
}

struct Monotone {
	line L[50010]; int s, e;
	void init() { s=e=0; }
	void ins(line v) {
		while (s+1<e && cross(L[e-2], L[e-1])>cross(L[e-1], v)) e--;
		L[e++]=v;
	}
	pair<ll, int> get(ll x, ll y) {
		while (s+1<e && L[s].get(x, y)>=L[s+1].get(x, y)) s++;
		return {L[s].get(x, y), L[s].cnt};
	}
}st;

void solve(ll Cost) {
	st.init(); st.ins(line(0, 0, Cost, 0));
	for (int i=1; i<=N; i++) {
		auto im=st.get(i, V[i]);
		D[i]=im.fi+V[i]*i; C[i]=im.se+1;
		st.ins(line(-V[i], -i, D[i]+V[i]*i+Cost, C[i]));
	}
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i=1; i<=N; i++) { scanf("%lld", &V[i]); V[i]+=V[i-1]; }
	ll s=0, e=(1e15);
	while (s<e) {
		ll md=(s+e)/2; solve(md);
		if (C[N]>K) s=md+1;
		else e=md;
	}
	solve(s);
	printf("%lld\n", D[N]-s*K);
	return 0;
}