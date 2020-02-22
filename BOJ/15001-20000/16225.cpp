#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int N; ll B;
vector<pii> A;
priority_queue<int> S;

int main() {
	cin>>N; A.resize(N);
	for (auto &i:A) cin>>i.fi;
	for (auto &i:A) cin>>i.se;
	sort(A.begin(), A.end(), [](pii &p1, pii &p2){ return p1.se<p2.se; }); S.em(A[0].fi);
	for (int i=1; i<N; i+=2) {
		B+=S.top(); S.pop();
		S.em(A[i].fi), S.em(A[i+1].fi);
	}
	cout<<B;
	return 0;
}