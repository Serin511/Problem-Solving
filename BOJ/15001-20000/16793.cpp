#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef vector<int> vim;
typedef pair<int, int> pii;
typedef shared_ptr<vector<pii> > pvii;

const int B = 300;
int N, D, Q;

struct UF {
	vim par, ch; bool im;
	UF(int n, bool i) : par(n, -1), im(i) {}
	int get(int x) { return par[x]!=-1?(par[x]=get(par[x])):x; }
	bool Union(int x, int y) {
		x=get(x), y=get(y);
		if (x==y) return false;
		if (im) ch.eb(y);
		par[y]=x;
		return true;
	}
	void resolve() { for (auto &i:ch) par[i]=-1; ch.clear(); }
};

vector<pii> solve(int N, vector<pii> Fix, vector<pair<pii, pvii> > S) {
	UF U1(N, false), U2(N, true); vector<pii> R;
	sort(all(Fix), [](pii &p1, pii &p2){ return p1.se<p2.se; });
	sort(all(S), [](pair<pii, pvii> &p1, pair<pii, pvii> &p2){ return p1.fi.fi<p2.fi.fi; });
	int tp=0, cnt=0;
	for (auto &i:S) {
		for (; tp<Fix.size()&&Fix[tp].se<=i.fi.fi; tp++) cnt+=U1.Union(Fix[tp].fi, Fix[tp].se);
		int im=cnt;
		for (auto &j:*i.se) if (j.se<=i.fi.fi) im+=U2.Union(U1.get(j.fi), U1.get(j.se));
		R.eb(i.fi.se, i.fi.fi+1-im);
		U2.resolve();
	}
	return R;
}

int main() {
	scanf("%d %d %d", &N, &D, &Q);
	vim T(D), X(D), Y(D), W(Q), P(Q);
	for (int i=0; i<D; i++) scanf("%d %d %d", &T[i], &X[i], &Y[i]);
	for (int i=0; i<Q; i++) scanf("%d %d", &W[i], &P[i]);
	vim A(Q, 0); set<pii> Fix;
	vector<pair<pii, int> > qu;
	for (int i=0; i<Q; i++) qu.eb(pii(W[i], P[i]), i); sort(all(qu));
	for (int i=0; i<D; i++) if (X[i]>Y[i]) swap(X[i], Y[i]);
	for (int s=0, tp=0; s<D; s+=B) {
		int e=min(D, s+B);
		set<pii> nFix;
		for (int i=s; i<e; i++) if (Fix.find(pii(X[i], Y[i]))!=Fix.end())
			Fix.erase(pii(X[i], Y[i])), nFix.em(X[i], Y[i]);
		vector<pair<pii, pvii> > S1, S2;
		for (int i=s; i<e; i++) {
			if (T[i]==0) nFix.em(X[i], Y[i]);
			if (T[i]==1) nFix.erase(pii(X[i], Y[i]));
			pvii nf1(new vector<pii>), nf2(new vector<pii>);
			for (auto &j:nFix) nf1->eb(j), nf2->eb(N-1-j.se, N-1-j.fi);
			for (; tp<Q&&qu[tp].fi.fi==i; tp++)
				S1.eb(pii(qu[tp].fi.se, qu[tp].se), nf1), S2.eb(pii(N-2-qu[tp].fi.se, qu[tp].se), nf2);
		}
		vector<pii> F1, F2;
		for (auto &i:Fix) F1.eb(i), F2.eb(N-1-i.se, N-1-i.fi);
		vector<pii> r1 = solve(N, F1, S1);
		vector<pii> r2 = solve(N, F2, S2);
		for (auto &i:r1) A[i.fi]+=i.se;
		for (auto &i:r2) A[i.fi]+=i.se;
		for (int i=s; i<e; i++) {
			if (T[i]==0) Fix.em(X[i], Y[i]);
			if (T[i]==1) Fix.erase(pii(X[i], Y[i]));
		}
	}
	for (auto &i:A) printf("%d\n", i);
	return 0;
}
