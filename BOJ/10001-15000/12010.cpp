#include <bits/stdc++.h>
#define em emplace
using namespace std;
typedef long long ll;

int N;
ll A, B, X, Y, Z, R;
priority_queue<ll, vector<ll>, greater<ll> > q1, q2;
// to replace / to use

int main() {
	cin>>N>>X>>Y>>Z;
	for (int i=1; i<=N; i++) {
		cin>>A>>B;
		while (A>B) {
			ll W=Y; if (!q1.empty()&&Z*i+q1.top()<W) W=Z*i+q1.top(), q1.pop();
			R+=W; q2.em(-W-Z*i); A--;
		}
		while (A<B) {
			ll W=X; if (!q2.empty()&&Z*i+q2.top()<W) W=Z*i+q2.top(), q2.pop();
			R+=W; q1.em(-W-Z*i); A++;
		}
	}
	cout<<R<<'\n';
	return 0;
}