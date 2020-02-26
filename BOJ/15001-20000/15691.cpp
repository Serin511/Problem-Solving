#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef pair<int, ll> pil;

struct dt {
	ll D, S, l, r;
	priority_queue<ll> L;
	priority_queue<ll, vector<ll>, greater<ll> > R;
	dt() : D(0), S(0), l(0), r(0) {}
	void push(ll x) {
		if (L.empty()||x>L.top()+l) R.em(x-r);
		else L.em(x-l);
	}
	void pop() {
		if (!R.empty()) R.pop();
		else if (!L.empty()) L.pop();
	}
	ll top() { return R.empty()?L.top()+l:R.top()+r; }
	int size() { return L.size()+R.size(); }
	void upd(int x) {
		while (R.size()<x) {
			while (!L.empty()&&L.top()+l<=0) L.pop();
			if (L.size()) R.em(L.top()+l-r), L.pop();
			else R.em(-r);
		}
		while (R.size()>x) L.em(R.top()+r-l), R.pop();
	}
}st[250010];

int N; vector<pil> adj[250010];
ll X[250010], Y[250010];

void merge(dt &p, dt &r, ll C) {
	p.D+=r.D; p.S+=C*abs(r.D)+r.S;
	r.l-=C, r.r+=C;
	if (p.size()<r.size()) swap(p.l, r.l), swap(p.r, r.r), swap(p.L, r.L), swap(p.R, r.R);
	while (r.size()) {
		ll i=r.top(); r.pop();
		if (i>0) p.push(i);
	}
}

void dfs(int n, int p) {
	for (auto &i:adj[n]) if (i.fi!=p) dfs(i.fi, n), merge(st[n], st[i.fi], i.se);
	st[n].D+=Y[n]; st[n].upd(max(0, -(int)st[n].D));
}

int main() {
	cin>>N;
	for (int i=1, u, v, c; i<N; i++) cin>>u>>v>>c, adj[u].eb(v, c), adj[v].eb(u, c);
	for (int i=1; i<=N; i++) cin>>X[i]>>Y[i], Y[i]-=X[i];
	dfs(1, 0);
	ll A=st[1].S; for (int i=0; i<-st[1].D; i++) A-=st[1].top(), st[1].pop();
	cout<<A<<'\n';
	return 0;
}