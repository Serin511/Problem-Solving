#include <bits/stdc++.h>
#define em emplace
using namespace std;
typedef long long ll;

int N;
ll D[200010], G, A;
priority_queue<ll, vector<ll>, greater<ll> > q1, q2;
// to replace / to use

int main() {
	cin>>N;
	for (int i=2; i<=N; i++) cin>>D[i], D[i]+=D[i-1];
	for (int i=1, j; i<=N; i++) {
		cin>>G;
		j=2; while (!q1.empty()&&j) {
			ll X=q1.top(); if (X+G+D[i]>0) break; j--;
			q1.pop(), A+=X+G+D[i], q1.em(-G-D[i]), q2.em(-X-2*D[i]);
		}
		while (j--) q2.em(G-D[i]);
		ll X=q2.top(); q2.pop(); A+=X+D[i]; q1.em(-X-2*D[i]);
	}
	cout<<A<<'\n';
	return 0;
}