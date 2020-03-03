#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<int, int> pii;
const int INF = 1e9;

struct Seg {
	vim T; vlm D, S1, S2; int SZ;
	Seg() : T(0), D(0) {}
	void in(int i, int s, int e) {
		if (s==e) { S1[i]=S2[i]=D[s]; return ; }
		int md=(s+e)/2;
		in(i*2, s, md); in(i*2+1, md+1, e);
		S1[i]=min(S1[i*2], S1[i*2+1]);
		S2[i]=max(S2[i*2], S2[i*2+1]);
	}
	void init() {
		SZ=T.size();
		int i=1; while (i<SZ) i*=2;
		i*=2; S1.resize(i+5); S2.resize(i+5);
		if (SZ) in(1, 0, SZ-1);
	}
	int lb(int x) { return lower_bound(all(T), x)-T.begin(); }
	int get(int i, int s, int e, int ts, int te, ll v1, ll v2) {
		if (e<ts||te<s||te<ts||e<s||(S1[i]>=v1&&S2[i]<=v2)) return INF;
		if (s==e) return T[s];
		int md=(s+e)/2, r=get(i*2, s, md, ts, te, v1, v2);
		if (r==INF) return get(i*2+1, md+1, e, ts, te, v1, v2);
		return r;
	}
	int get(int ts, int te, ll v1, ll v2) { return get(1, 0, SZ-1, ts, te, v1, v2); }
};

ll sq(ll x) { return x*x; }

int N, M, K, Q;
set<pii> adj[500005];
vector<pii> V[500005], add; vim tr[500005], e;

ll mysqrt(ll x) {
	ll s=0, e=INF;
	while (s<e) {
		ll md=(s+e+1)/2;
		if (md*md<=x) s=md;
		else e=md-1;
	}
	return s;
}

struct UF {
	vim p; vector<unordered_set<int> > X; int SZ;
	UF(int N) : p(N+1, 0), X(N+1), SZ(N) {}
	inline int get(int x) { return p[x]?(p[x]=get(p[x])):x; }
	inline void Un(int x, int y, int t) {
		x=get(x), y=get(y);
		if (x==y) return ;
		if (X[x].size()<X[y].size()) swap(x, y);
		for (auto &i:X[y]) {
			if (X[x].find(i)!=X[x].end()) {
				e[i]=t;
				X[x].erase(i);
			}
			else X[x].em(i);
		}
		p[y]=x;
	}
};

void solve() {
	cin>>N;
	vector<Seg> St(N+5);
	vector<pii> P; P.eb(0, 0);
	for (int i=1; i<=N; i++) V[i].clear();

	for (int i=0, x, y; i<N; i++) cin>>x>>y, P.eb(x, y);
	cin>>M; vlm lim; vim T(M+5, 1e9); vector<pii> E;
	for (int i=0, u, v, l; i<M; i++) {
		cin>>u>>v>>l;
		lim.eb(mysqrt(sq(l)-sq(P[u].fi-P[v].fi)-sq(P[u].se-P[v].se)));
		adj[u].em(v, i); adj[v].em(u, i); E.eb(u, v);
	}

	set<pii> pq;
	for (int i=1; i<=N; i++) pq.em(adj[i].size(), i);
	while (pq.size()) {
		auto k=*pq.begin(); pq.erase(k);
		for (auto &i:adj[k.se]) {
			pq.erase(pii(adj[i.fi].size(), i.fi));
			adj[i.fi].erase(pii(k.se, i.se));
			pq.em(adj[i.fi].size(), i.fi);
			V[k.se].eb(i);
		}
		adj[k.se].clear();
	}

	vector<pii> Ch; Ch.eb(0,0);
	vim lst(N+5, 0); vlm H(N+5, 0);
	cin>>K;
	for (int i=1, v, h; i<=K; i++) cin>>v>>h, Ch.eb(v, h), St[v].T.eb(i), H[v]+=h, St[v].D.eb(H[v]);
	for (int i=1; i<=N; i++) St[i].init();

	fill(all(H), 0);
	for (int i=1; i<=K; i++) {
		int nw=Ch[i].fi, dh=Ch[i].se;
		for (auto &j:V[nw])
			T[j.se]=min(T[j.se], 
				St[j.fi].get(St[j.fi].lb(lst[nw]), St[j.fi].lb(i)-1, H[nw]-lim[j.se], H[nw]+lim[j.se]));
		H[nw]+=dh; lst[nw]=i;
		for (auto &j:V[nw])
			if (lim[j.se]<abs(H[nw]-H[j.fi])) T[j.se]=min(T[j.se], i);
	}
	for (int i=1; i<=N; i++) for (auto &j:V[i])
		T[j.se]=min(T[j.se], 
			St[j.fi].get(St[j.fi].lb(lst[i]), K, H[i]-lim[j.se], H[i]+lim[j.se]));

	cin>>Q; UF U(N);
	vector<pii> qu(Q); for (auto &i:qu) cin>>i.fi>>i.se;
	e.resize(Q); add.clear(); fill(all(e), K+1);
	for (int i=0; i<M; i++) add.eb(min(T[i], K+1), i);
	sort(all(add)); reverse(all(add));
	for (int i=0; i<Q; i++) U.X[qu[i].fi].em(i), U.X[qu[i].se].em(i);
	for (auto &i:add) U.Un(E[i.se].fi, E[i.se].se, i.fi);
	for (auto &i:e) cout<<(i==K+1?-1:i)<<'\n';
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin>>T;
	while (T--) solve();
	return 0;
}