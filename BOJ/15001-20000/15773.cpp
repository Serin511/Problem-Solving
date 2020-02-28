#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

int N; pll B[250010]; ll S;
priority_queue<ll> pq;

int main() {
	cin>>N;
	for (int i=1; i<=N; i++) cin>>B[i].fi>>B[i].se;
	sort(B+1, B+N+1, [](pll &p1, pll &p2){ return p1.fi+p1.se<p2.fi+p2.se; });
	for (int i=1; i<=N; i++) {
		if (S<=B[i].fi) pq.em(B[i].se), S+=B[i].se;
		else if (pq.size()&&pq.top()>B[i].se&&S-pq.top()<=B[i].fi) S+=B[i].se-pq.top(), pq.pop(), pq.em(B[i].se);
	}
	cout<<pq.size()<<'\n';
	return 0;
}