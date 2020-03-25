#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef long long ll;
typedef vector<int> vim;

struct RMQ {
	vim A; int sz;
	void init(vim &V) {
		int N=V.size()-1;
		for (sz=1; sz<N+1; sz*=2) {}
		A.resize(sz*2); A[0]=1<<30;
		for (int i=1; i<=N; i++) A[i+sz]=V[i];
		for (int i=sz-1; i; i--) A[i]=min(A[i*2], A[i*2+1]);
	}
	int get(int l, int r) {
		l+=sz, r+=sz;
		int a=1<<30;
		while (l<=r) {
			if (l%2) a=min(a, A[l++]);
			if (!(r%2)) a=min(a, A[r--]);
			l/=2; r/=2;
		}
		return a;
	}
}S1, S2;

struct dt {
	int l, r, h;
	dt(int L, int R, int H) : l(L), r(R), h(H) {}
	bool operator <(const dt &d)const {
		return r-l<d.r-d.l;
	}
	ll get(const dt &d) { return (ll)(r-d.l+1)*(h+d.h); }
};

vector<dt> prep(vim V) {
	int N=V.size()-1;
	vector<pair<int, int> > P; vector<dt> R;

	for (int i=1; i<=N; P.eb(V[i], i), i++)
		while (P.size()&&P.back().fi>V[i])
			R.eb((P.size()>1?P[P.size()-2].se:0)+1, i-1, P.back().fi), P.pop_back();
	while (P.size()) R.eb((P.size()>1?P[P.size()-2].se:0)+1, N, P.back().fi), P.pop_back();

	return R;
}

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
		if (i.r<m) lu.eb(i);
		else if (m<i.l) ru.eb(i);
		else lu.eb(i), mu.eb(i);
	}
	for (auto &i:D) {
		if (i.r<m) ld.eb(i);
		else if (m<i.l) rd.eb(i);
		else rd.eb(i), md.eb(i);
	}

	return max({sol(mu, md), dnc(s, m-1, lu, ld), dnc(m+1, e, ru, rd)});
}

int N; ll A;

int main() {
	cin.tie(0)->sync_with_stdio(0);

	cin>>N; vim H(N+1), L(N+1);
	for (int i=1; i<=N; i++) cin>>H[i]>>L[i];

	S1.init(L), S2.init(H);
	vector<dt> U=prep(H), D=prep(L);
	for (auto &i:U) A=max(A, (ll)(i.r-i.l+1)*(i.h+S1.get(i.l, i.r)));
	for (auto &i:D) A=max(A, (ll)(i.r-i.l+1)*(i.h+S2.get(i.l, i.r)));

	sort(all(U)); sort(all(D)); reverse(all(D));
	A=max(A, dnc(1, N, U, D));
	reverse(all(U)); reverse(all(D));
	A=max(A, dnc(1, N, D, U));

	cout<<A<<'\n';
	return 0;
}