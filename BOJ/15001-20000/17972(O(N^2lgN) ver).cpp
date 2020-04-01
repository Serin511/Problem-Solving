#include <bits/stdc++.h>
#define fi first
#define se second
#define all(V) (V).begin(), (V).end()
using namespace std;

const int MX = 2005;

int N, A[MX];
pair<int, int> S[MX];

struct ST {
	int st[4100], lz[4100];
	int l, r;
	void init() { fill(st, st+4100, -(1e9)); }
	void spr(int i) {
		st[i]+=lz[i];
		if (i<(1<<11)) for (int j:{i*2, i*2+1}) lz[j]+=lz[i];
		lz[i]=0;
	}
	void Set(int i, int s, int e) {
		if (lz[i]) spr(i);
		st[i]=max(st[i], r);
		if (s==e) return ;
		int m=(s+e)/2;
		if (l<=m) Set(i*2, s, m);
		else Set(i*2+1, m+1, e);
	}
	void Set(int t, int v) { l=t, r=v; Set(1, 0, N); }
	void upd(int i, int s, int e) {
		if (lz[i]) spr(i);
		if (e<l||r<s) return ;
		if (l<=s&&e<=r) { lz[i]++; spr(i); return ; }
		int m=(s+e)/2;
		upd(i*2, s, m); upd(i*2+1, m+1, e);
		st[i]=max(st[i*2], st[i*2+1]);
	}
	void upd(int L, int R) { l=L, r=R; upd(1, 0, N); }
	int get(int i, int s, int e) {
		if (lz[i]) spr(i);
		if (e<l||r<s) return -(1e9);
		if (l<=s&&e<=r) return st[i];
		int m=(s+e)/2;
		return max(get(i*2, s, m), get(i*2+1, m+1, e));
	}
	int get(int L, int R) { l=L, r=R; return get(1, 0, N); }
}Seg[MX];

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>N; vector<int> cp;
	for (int i=1; i<=N; i++) cin>>S[i].fi>>S[i].se, cp.emplace_back(S[i].fi);
	sort(all(cp)); cp.resize(unique(all(cp))-cp.begin());
	for (int i=1; i<=N; i++)
		S[i].fi=lower_bound(all(cp), S[i].fi)-cp.begin()+1,
		S[i].se=upper_bound(all(cp), S[i].se)-cp.begin();
	sort(S+1, S+1+N);
	for (int i=0; i<=N; i++) Seg[i].init(); Seg[0].Set(0, 0);
	for (int i=1; i<=N; i++) for (int j=i-1; j>=0; j--) {
		Seg[j+1].upd(S[i].se+1, N);
		Seg[j+1].Set(S[i].se, Seg[j+1].get(S[i].fi, S[i].se)+1);
		Seg[j+1].Set(S[i].se, Seg[j].get(0, S[i].fi-1)+1);
	}
	for (int i=1; i<=N; i++) {
		int mx=Seg[i].get(0, N);
		for (int j=1; j<=mx; j++) A[j]=max(A[j], i);
	}
	for (int i=N; i>=1; i--) cout<<min(A[i], i)<<' ';
	return 0;
}