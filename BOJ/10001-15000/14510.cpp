#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;
typedef long long ll;

int N, M, K, W, S[200005], pr[200005];
vector<tuple<ll, int, int> > E1, E2;

int gp(int x) { return pr[x]?(pr[x]=gp(pr[x])):x; }
bool Un(int x, int y) {
	x=gp(x), y=gp(y);
	if (x!=y) pr[y]=x;
	return x!=y;
}

pair<ll, int> f(ll C) {
	fill(pr, pr+N+1, 0);
	int t=0; pair<ll, int> r(0, 0);
	for (auto &i:E1) {
		for (; t<E2.size()&&get<0>(E2[t])<=get<0>(i)+C; t++)
			if (Un(get<1>(E2[t]), get<2>(E2[t]))) r.first+=get<0>(E2[t]);
		if (Un(get<1>(i), get<2>(i))) r.first+=get<0>(i)+C, r.second++;
	}
	return r;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin>>N>>M>>K>>W;
	for (int i=1, s; i<=K; i++) cin>>s, S[s]=1;
	for (int i=1, u, v, c; i<=M; i++) cin>>u>>v>>c, (S[u]+S[v]==1?E1:E2).eb(c, u, v);
	sort(E1.begin(), E1.end()); sort(E2.begin(), E2.end());
	E1.eb(1e18, 1, 1);
	ll s=-(1e12), e=(1e12);
	if (f(s).second<W||f(e).second>W) { cout<<"-1\n"; return 0; }
	for (int i=2; i<=N; i++) if (Un(1, i)) { cout<<"-1\n"; return 0; }
	while (s<e) {
		ll md=s+(e-s)/2;
		if (f(md).second>W) s=md+1;
		else e=md;
	}
	cout<<(f(s).first-s*W)<<'\n';
	return 0;
}