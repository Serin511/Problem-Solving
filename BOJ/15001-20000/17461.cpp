#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef long long ll;
typedef vector<int> vim;
typedef pair<int, int> pii;

struct dt {
	int l, r, h;
	dt(int L, int R, int H) : l(L), r(R), h(H) {}
	bool operator <(const dt &d)const {
		return r-l<d.r-d.l;
	}
	ll get(const dt &d) { return (ll)(r-d.l+1)*(h+d.h); }
};

struct Seg {
	vim cp, st; int sz;
	void init(vector<dt> &V) {
		for (auto &i:V) cp.eb(i.r);
		sort(all(cp)); cp.resize(unique(all(cp))-cp.begin());
		for (sz=1; sz<cp.size(); sz*=2) {}
		st.resize(sz*2);
	}
	void upd(int i, int s, int e, int t, int v) {
		if (s==e) { st[i]=max(st[i], v); return ; }
		int md=(s+e)/2;
		if (t<=md) upd(i*2, s, md, t, v);
		else upd(i*2+1, md+1, e, t, v);
		st[i]=max(st[i*2], st[i*2+1]);
	}
	void upd(dt &d) {
		int b=lower_bound(all(cp), d.r)-cp.begin();
		upd(1, 0, cp.size()-1, b, d.h);
	}
	int get(int i, int s, int e, int t) {
		if (t>e) return 0;
		if (s==e) return st[i];
		int md=(s+e)/2;
		if (t<=md) return max(get(i*2, s, md, t), st[i*2+1]);
		else return get(i*2+1, md+1, e, t);
	}
	int get(int t) {
		int b=lower_bound(all(cp), t)-cp.begin();
		return get(1, 0, cp.size()-1, b);
	}
};

struct solver {
	vim cp;

	ll sol(vector<dt> U, vector<dt> D) {
		auto cross = [&](int x, int y) {
			int s=0, e=U.size();
			while (s<e) {
				int md=(s+e)/2;
				if (D[x].get(U[md])<D[y].get(U[md])) e=md;
				else s=md+1;
			}
			return s;
		};

		vim s, e;
		vector<dt> dd;
		for (int i=0, x=U.size()-1, y=U.size()-1; i<D.size(); i++) {
			while (x>=0&&D[i].r<=U[x].r) x--;
			while (y>=0&&D[i].l>U[y].l) y--;
			if (x+1<=y) s.eb(x+1), e.eb(y), dd.eb(D[i]);
		}swap(dd, D);

		int N=U.size(), M=D.size();
		if (!N||!M) return 0;

		ll A=0;
		for (int f=0; f<M; f++) {
			int r=f; while (r<M&&s[f]<=e[r]) r++; r--;
			
			int b=e[f]; vim L;
			for (int i=f; i<=r; i++) {
				while (L.size()>1&&cross(L[L.size()-2], L.back())>=cross(L.back(), i)) L.pop_back();
				L.eb(i);
				for (; b>=(i==r?s[f]:e[i+1]+1); b--) {
					while (L.size()>1&&cross(L[L.size()-2], L.back())>b) L.pop_back();
					A=max(A, D[L.back()].get(U[b]));
				}
			}

			b=s[r]; vim R;
			for (int i=r; i>f; i--) {
				while (R.size()>1&&cross(R.back(), R[R.size()-2])<=cross(i, R.back())) R.pop_back();
				R.eb(i);
				for (; b<s[i-1]; b++) {
					while (R.size()>1&&cross(R.back(), R[R.size()-2])<b) R.pop_back();
					A=max(A, D[R.back()].get(U[b]));
				}
			}
			
			f=r;
		}

		return A;
	}

	ll dnc(int s, int e, vector<dt> U, vector<dt> D) {
		if (s>e||!U.size()||!D.size()) return 0;
		int m=(s+e)/2;
		vector<dt> lu, ld, ru, rd, mu, md;

		for (auto &i:U) {
			if (i.r<cp[m]) lu.eb(i);
			else if (cp[m]<i.l) ru.eb(i);
			else lu.eb(i), mu.eb(i);
		}
		for (auto &i:D) {
			if (i.r<cp[m]) ld.eb(i);
			else if (cp[m]<i.l) rd.eb(i);
			else rd.eb(i), md.eb(i);
		}

		return max({sol(mu, md), dnc(s, m-1, lu, ld), dnc(m+1, e, ru, rd)});
	}
};

int W; vim cp;

ll cal(vector<pii> &P, int hi) {
	ll A=0;
	vector<pii> st; st.eb(0, 0);
	for (auto &i:P) {
		A=max(A, (ll)(i.fi-st.back().fi)*hi);
		while (st.size()&&st.back().se>=i.se)
			A=max(A, (ll)(i.fi-(st.size()>1?st[st.size()-2].fi:0))*st.back().se),
			st.pop_back();
		st.eb(i);
	}
	A=max(A, (ll)(W-st.back().fi)*hi);
	while (st.size())
		A=max(A, (ll)(W-(st.size()>1?st[st.size()-2].fi:0))*st.back().se), st.pop_back();
	return A;
}

vector<dt> prec(vector<pii> &P, int hi) {
	vector<dt> r;
	vector<pair<int, int> > st; st.eb(0, 0);
	for (auto &i:P) {
		r.eb(st.back().fi, i.fi-1, hi);
		while (st.size()&&st.back().se>=i.se) {
			if (st.back().se) r.eb(st[st.size()-2].fi, i.fi-1, st.back().se);
			st.pop_back();
		}
		st.eb(i);
	}
	r.eb(st.back().fi, W-1, hi);
	while (st.size()) {
		if (st.back().se) r.eb(st[st.size()-2].fi, W-1, st.back().se);
		st.pop_back();
	}
	return r;
}

ll f(int s, int e, int lo, int hi, vector<pii> P) {
	if (!P.size()||s>e) return (ll)W*(hi-lo);

	ll A=0; int md=(s+e)/2, mh=cp[md];
	vector<dt> U, D;
	vector<pii> up, dp, UP, DP;

	for (auto &i:P) {
		if (i.fi>mh) UP.eb(i), up.eb(i.se, i.fi-mh);
		if (i.fi<mh) DP.eb(i), dp.eb(i.se, mh-i.fi);
	}
	A=max({A, cal(up, hi-mh), cal(dp, mh-lo)});
	up.clear(); dp.clear();
	
	for (auto &i:P) {
		if (i.fi>=mh) up.eb(i.se, i.fi-mh);
		if (i.fi<=mh) dp.eb(i.se, mh-i.fi);
	}
	U=prec(up, hi-mh); D=prec(dp, mh-lo);

	Seg S1, S2; S1.init(D); S2.init(U);
	sort(all(U), [](dt &d1, dt &d2){ return d1.l<d2.l; });
	sort(all(D), [](dt &d1, dt &d2){ return d1.l<d2.l; });
	int tp=0; for (auto &i:U) {
		while (tp<D.size()&&D[tp].l<=i.l) S1.upd(D[tp]), tp++;
		A=max(A, (ll)(i.r-i.l+1)*(i.h+S1.get(i.r)));
	}
	tp=0; for (auto &i:D) {
		while (tp<U.size()&&U[tp].l<=i.l) S2.upd(U[tp]), tp++;
		A=max(A, (ll)(i.r-i.l+1)*(i.h+S2.get(i.r)));
	}

	solver sol;
	for (auto &i:U) sol.cp.eb(i.l);
	for (auto &i:D) sol.cp.eb(i.l);
	sort(all(sol.cp)); sol.cp.resize(unique(all(sol.cp))-sol.cp.begin());

	sort(all(U)); sort(all(D)); reverse(all(D));
	A=max(A, sol.dnc(0, sol.cp.size()-1, U, D));
	reverse(all(U)); reverse(all(D));
	A=max(A, sol.dnc(0, sol.cp.size()-1, D, U));

	return max({A, f(s, md-1, lo, mh, DP), f(md+1, e, mh, hi, UP)});
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int H, N;
	cin>>H>>W>>N;
	vector<pii> im(N), P;
	for (auto &i:im) {
		cin>>i.fi>>i.se;
		if (i.fi!=0&&i.fi!=H&&i.se!=0&&i.se!=W) P.eb(i), cp.eb(i.fi);
	}cp.eb(0); cp.eb(H);
	sort(all(P), [](pii &p1, pii &p2){ return p1.se<p2.se; });
	sort(all(cp)); cp.resize(unique(all(cp))-cp.begin());
	cout<<f(0, cp.size()-1, 0, H, P)<<'\n';
	return 0;
}