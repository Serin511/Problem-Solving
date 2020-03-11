#include <bits/stdc++.h>
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef long long ll;
typedef vector<int> vim;
typedef pair<int, int> pii;

const int MX = 100005;

int N, M, Q, A[MX], L[MX];
vim cp;

struct node {
	int l, r, v;
	node() : l(0), r(0), v(0) {}
	node(int L, int R, int V) : l(L), r(R), v(V) {}
}st[1<<25]; int nd_tp=1;

namespace pst {
	int upd(int rf, int s, int e, int t, int v) {
		if (!t) return rf;
		int nd=++nd_tp; st[nd]=node(st[rf].l, st[rf].r, st[rf].v+v);
		if (s==e) return nd;
		int md=(s+e)/2;
		if (t<=md) st[nd].l=upd(st[rf].l, s, md, t, v);
		else st[nd].r=upd(st[rf].r, md+1, e, t, v);
		return nd;
	}
	int get(int i, int s, int e, int t) {
		if (!i) return 0;
		if (s==e) return st[i].v;
		int md=(s+e)/2;
		if (t<=md) return get(st[i].l, s, md, t)+st[st[i].r].v;
		else return get(st[i].r, md+1, e, t);
	}
}

struct Seg {
	map<int, int> nd[1<<18];
	Seg() { for (int i=1; i<(1<<18); i++) nd[i][0]=1; }
	void upd(int i, int s, int e, int t, int l, int r) {
		nd[i][r]=pst::upd(pst::upd(prev(nd[i].end())->second, 1, N, l, -1), 1, N, r, 1);
		if (s==e) return ;
		int md=(s+e)/2;
		if (t<=md) upd(i*2, s, md, t, l, r);
		else upd(i*2+1, md+1, e, t, l, r);
	}
	int get(int i, int ts, int te) { return pst::get(prev(nd[i].lower_bound(te+1))->second, 1, N, ts); }
	int get(int i, int s, int e, int ts, int te, int v) {
		if (s==e) {
			if (get(i, ts, te)<v) return -1;
			return cp[s-1];
		}
		int md=(s+e)/2, r=get(i*2, ts, te);
		if (r>=v) return get(i*2, s, md, ts, te, v);
		else return get(i*2+1, md+1, e, ts, te, v-r);
	}
}S;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N;
	for (int i=1; i<=N; i++) cin>>A[i], cp.eb(A[i]);
	sort(all(cp)), cp.resize(unique(all(cp))-cp.begin()), M=cp.size();
	for (int i=1; i<=N; i++) A[i]=lower_bound(all(cp), A[i])-cp.begin()+1;
	for (int i=1; i<=N; i++) S.upd(1, 1, M, A[i], L[A[i]], i), L[A[i]]=i;
	ll A=0;
	cin>>Q; while (Q--) {
		int a, b, c, d, k;
		cin>>a>>b>>c>>d>>k;
		int l=(a*max(A, 0ll)+b)%N+1, r=(c*max(A, 0ll)+d)%N+1;
		if (l>r) swap(l, r);
		cout<<(A=S.get(1, 1, M, l, r, k))<<'\n';
	}
	return 0;
}