#include <bits/stdc++.h>
#define fi first
#define se second
#define ryan bear
#define all(V) ((V).begin()), ((V).end())
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;
typedef vector<int> vim;
typedef vector<ll> vlm;

int lis(vector<pii> V) {
	sort(V.begin(), V.end());
	int stk[200010], tp=1;
	stk[0]=-1;
	for (int i=0; i<V.size(); i++) {
		if (stk[tp-1]<V[i].se) {
			stk[tp++]=V[i].se;
			continue;
		}
		int j=lower_bound(stk, stk+tp, V[i].se)-stk;
		stk[j]=V[i].se;
	}
	return tp-1;
}

struct Seg {
	Seg *l, *r;
	int dt;
	Seg() {l=r=NULL; dt=(1<<30);}
	void upd(int i, int xs, int xe, int val) {
		dt=min(dt, val);
		if (xs==xe) return ;
		int md=(xs+xe)/2;
		if (i<=md) {
			if (!l) l=new Seg();
			l->upd(i, xs, md, val);
		}
		else {
			if (!r) r=new Seg();
			r->upd(i, md+1, xe, val);
		}
	}
	int get(int s, int e, int xs, int xe) {
		if (xs>xe) return (1<<30);
		if (s<=xs&&xe<=e) return dt;
		int L, R; L=R=(1<<30);
		int md=(xs+xe)/2;
		if (s<=md) L=(l?l->get(s, e, xs, md):(1<<30));
		if (md+1<=e) R=(r?r->get(s, e, md+1, xe):(1<<30));
		return min(L, R);
	}
};

int M, N;
Seg *tree[200010];

int main() {
	scanf("%d %d", &M, &N);
	if (M==2) {
		vector<pii> ar(N);
		for (int i=0; i<N; i++) scanf("%d", &ar[i].fi);
		for (int i=0; i<N; i++) scanf("%d", &ar[i].se);
		printf("%d\n", lis(ar));
		return 0;
	}
	else {
		vector<pair<int, pii> > ar(N);
		for (int i=0; i<N; i++) scanf("%d", &ar[i].fi);
		for (int i=0; i<N; i++) scanf("%d", &ar[i].se.fi);
		for (int i=0; i<N; i++) scanf("%d", &ar[i].se.se);
		vim cp1, cp2;
		sort(all(ar));
		for (auto pi:ar) { cp1.push_back(pi.se.fi); cp2.push_back(pi.se.se); }
		sort(all(cp1)); sort(all(cp2));
		cp1.erase(unique(all(cp1)), cp1.end()); cp2.erase(unique(all(cp2)), cp2.end());
		for (int i=0; i<N; i++) {
			ar[i].se.fi=lower_bound(all(cp1), ar[i].se.fi)-cp1.begin()+1;
			ar[i].se.se=lower_bound(all(cp2), ar[i].se.se)-cp2.begin()+1;
		}
		int mx=0, s, e;
		for (int i=0; i<=N; i++) tree[i]=new Seg();
		tree[0]->upd(0, 1, N, 0);
		for (int i=0; i<N; i++) {
			if (!mx) {
				mx=1;
				tree[1]->upd(ar[i].se.fi, 1, N, ar[i].se.se);
				continue;
			}
			s=0, e=mx+1;
			while (s+1<e) {
				int md=(s+e)/2;
				if (tree[md]->get(1, ar[i].se.fi, 1, N) <= ar[i].se.se) s=md;
				else e=md;
			}
			mx=max(s+1, mx);
			tree[s+1]->upd(ar[i].se.fi, 1, N, ar[i].se.se);
		}
		printf("%d", mx);
	}
	return 0;
}