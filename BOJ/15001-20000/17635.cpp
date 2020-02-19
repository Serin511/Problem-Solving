#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef vector<int> vim;
typedef pair<int, int> pii;

const int B = 800;

struct line {
	int u, v, r;
	line(int U, int V, int R) : u(U), v(V), r(R) {}
};
typedef shared_ptr<vector<line> > pvii;

struct UF {
	vim par, rnk, sz, cp; vector<pii> cr;
	UF(int n) : par(n+1, 0), rnk(n+1, 0), sz(n+1, 1) {}
	int get(int x) { return par[x]?get(par[x]):x; }
	bool Union(int x, int y) {
		x=get(x), y=get(y);
		if (x==y) return false;
		if (rnk[x]<rnk[y]) swap(x, y);
		cp.eb(y); cr.eb(x, rnk[x]);
		par[y]=x; rnk[x]=max(rnk[x], rnk[y]+1); sz[x]+=sz[y];
		return true;
	}
	void resolve(int x) {
		while (x--)
			sz[par[cp.back()]]-=sz[cp.back()], par[cp.back()]=0, rnk[cr.back().fi]=cr.back().se,
			cp.pop_back(), cr.pop_back();
	}
};

struct qu {
	int st, rs, i;
	qu(int S, int R, int I) : st(S), rs(R), i(I) {}
	bool operator <(const qu &r)const {
		return rs>r.rs;
	}
};

int A[100010];
void solve(int N, vector<line> Fix, vector<pair<qu, pvii> > S) {
	UF U(N); int fr=0;
	sort(all(Fix), [](line &l1, line &l2){ return l1.r>l2.r; }); sort(all(S));
	for (auto &i:S) {
		int c=0;
		while (fr<Fix.size()&&Fix[fr].r>=i.fi.rs) U.Union(Fix[fr].u, Fix[fr].v), fr++;
		for (auto &j:*i.se) c+=U.Union(j.u, j.v);
		A[i.fi.i]=U.sz[U.get(i.fi.st)];
		U.resolve(c);
	}
}

int main() {
	int N, M, Q; scanf("%d %d", &N, &M);
	vector<line> L; L.eb(0, 0, 0);
	set<int> Fix;
	for (int i=1, u, v, r; i<=M; i++)
		scanf("%d %d %d", &u, &v, &r), L.eb(u, v, r);
	for (int i=1; i<=M; i++) Fix.em(i);
	scanf("%d", &Q);
	vim q(Q+1), b(Q+1), r(Q+1);
	for (int s=1; s<=Q; s+=B) {
		int e=min(s+B-1, Q);
		map<int, int> nFix;
		vector<pair<qu, pvii> > S;
		for (int i=s; i<=e; i++) {
			scanf("%d %d %d", &q[i], &b[i], &r[i]);
			if (q[i]==1) Fix.erase(b[i]), nFix[b[i]]=L[b[i]].r;
		}
		for (int i=s; i<=e; i++) {
			if (q[i]==1) nFix[b[i]]=r[i];
			if (q[i]==2) {
				pvii nf(new vector<line>);
				for (auto &j:nFix) if (j.se>=r[i]) nf->eb(L[j.fi].u, L[j.fi].v, j.se);
				S.eb(qu(b[i], r[i], i), nf);
			}
		}
		vector<line> F;
		for (auto &i:Fix) F.eb(L[i]);
		solve(N, F, S);
		for (auto &i:nFix) L[i.fi].r=i.se, Fix.em(i.fi);
	}
	for (int i=1; i<=Q; i++) if (q[i]==2) printf("%d\n", A[i]);
	return 0;
}