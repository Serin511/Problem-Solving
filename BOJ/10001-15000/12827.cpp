#include <bits/stdc++.h>
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef long long ll;

const int SZ = 1<<20;

vector<ll> cp;

struct Seg {
	ll sv[SZ], cov[SZ], fc[SZ], lst[SZ], chk[SZ];
	void spread(int i, int s, int e, ll T) {
		ll l=cp[e]-(s?cp[s-1]:0);
		sv[i]+=(T-lst[i]-fc[i])*cov[i]+fc[i]*l;
		if (s!=e) for (auto j:{i*2, i*2+1}) {
			fc[j]+=fc[i];
			if (chk[i]) fc[j]+=T-lst[i]-fc[i];
		}
		lst[i]=T; fc[i]=0;
	}
	void upd(int i, int s, int e, int ts, int te, int v, ll T) {
		spread(i, s, e, T);
		if (te<s||e<ts) return ;
		if (ts<=s&&e<=te) {
			if (!chk[i]) cov[i]=cp[e]-(s?cp[s-1]:0);
			chk[i]+=v;
			if (!chk[i]) cov[i]=(s==e?0:cov[i*2]+cov[i*2+1]);
			return ;
		}
		int md=(s+e)/2;
		upd(i*2, s, md, ts, te, v, T); upd(i*2+1, md+1, e, ts, te, v, T);
		cov[i]=max(chk[i]?cp[e]-cp[s-1]:0, cov[i*2]+cov[i*2+1]);
	}
	ll get(int i, int s, int e, int ts, int te, ll T) {
		spread(i, s, e, T);
		if (te<s||e<ts) return 0;
		if (ts<=s&&e<=te) return sv[i];
		int md=(s+e)/2;
		return get(i*2, s, md, ts, te, T)+get(i*2+1, md+1, e, ts, te, T);
	}
}S;

struct qu {
	ll x1, x2, y; int v, i;
	qu(ll v1, ll v2, ll v3, int v4) : x1(v1), x2(v2), y(v3), v(v4) {}
	qu(ll v1, ll v2, ll v3, int v4, int v5) : x1(v1), x2(v2), y(v3), v(v4), i(v5) {}
	bool operator <(const qu &r)const {
		return y<r.y;
	}
};

int N, M, K; ll A[100010];
vector<qu> P1, P2;

int Find(ll x) { return lower_bound(all(cp), x)-cp.begin(); }

int main() {
	cin>>N;
	cp.eb(0);
	for (int i=1, x1, x2, y1, y2; i<=N; i++)
		cin>>x1>>y1>>x2>>y2, P1.eb(x1, x2, y1, 1), P1.eb(x1, x2, y2, -1), cp.eb(x1), cp.eb(x2);
	cin>>M;
	for (int i=1, x1, x2, y1, y2; i<=M; i++)
		cin>>x1>>y1>>x2>>y2, P2.eb(x1, x2, y1, -1, i), P2.eb(x1, x2, y2, 1, i), cp.eb(x1), cp.eb(x2);
	sort(all(cp)), cp.resize(unique(all(cp))-cp.begin());
	sort(all(P1)), sort(all(P2)); K=cp.size()-1;
	for (int i=0, j=0; i<P2.size(); i++) {
		while (j<P1.size()&&P1[j].y<=P2[i].y) S.upd(1, 0, K, Find(P1[j].x1)+1, Find(P1[j].x2), P1[j].v, P1[j].y), j++;
		A[P2[i].i]+=S.get(1, 0, K, Find(P2[i].x1)+1, Find(P2[i].x2), P2[i].y)*P2[i].v;
	}
	for (int i=1; i<=M; i++) cout<<A[i]<<'\n';
	return 0;
}