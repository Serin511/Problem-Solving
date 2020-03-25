#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef pair<ll, int> pli;

const ll LINF = 1e18;
const ll MX = 3e7;
const pli BS = pli(-LINF, 0);

struct node {
	vlm V[2][2]; int sz;
	node(int SZ=0) { sz=SZ; for (int i=0; i<4; i++) V[(i&2)/2][i&1]=vlm(sz+1, -LINF); }
};

struct dt {
	pli P[2][2];
	dt() { P[0][0]=P[0][1]=P[1][0]=P[1][1]=BS; }
	dt(pli p1, pli p2, pli p3, pli p4)
		{ P[0][0]=p1, P[0][1]=p2, P[1][0]=p3, P[1][1]=p4; }
	pli get() { return max({P[0][0], P[0][1], P[1][0], P[1][1]}); }
};

pli operator +(pli p1, pli p2) { return pli(p1.fi+p2.fi, p1.se+p2.se); }

void merge(node &r, node &n1, node &n2) {
	r=node(n1.sz+n2.sz);
	for (int i=0; i<16; i++) {
		int x=(i&8)/8, y=(i&4)/4, z=(i&2)/2, w=i&1;
		if (n1.sz==1&&(x^y)) continue;
		if (n2.sz==1&&(z^w)) continue;
		vlm &T=r.V[x][w], &R1=n1.V[x][y], &R2=n2.V[z][w];

		int s1=x|y, e1=(n1.sz==1?x:n1.sz-(2-x-y));
		int s2=z|w, e2=(n2.sz==1?z:n2.sz-(2-z-w));

		vlm V, V1, V2;
		V.eb(R1[s1]+R2[s2]);
		for (int j=s1; j<e1; j++) V1.eb(R1[j+1]-R1[j]);
		for (int j=s2; j<e2; j++) V2.eb(R2[j+1]-R2[j]);

		int t=0;
		for (auto &j:V2) {
			while (t<V1.size()&&V1[t]>=j) V.eb(V1[t++]);
			V.eb(j);
		}while (t<V1.size()) V.eb(V1[t++]);

		for (int j=1; j<V.size(); j++) V[j]+=V[j-1];
		for (int j=0; j<V.size(); j++) {
			T[j+s1+s2]=max(T[j+s1+s2], V[j]);
			if (y==1&&z==1)
				T[j+s1+s2-1]=max(T[j+s1+s2-1], V[j]);
		}
	}
}

dt merge(ll v, dt &d1, dt &d2) {
	dt r;
	for (int i=0; i<16; i++) {
		int x=(i&8)/8, y=(i&4)/4, z=(i&2)/2, w=i&1;
		pli im=d1.P[x][y]+d2.P[z][w];
		r.P[x][w]=max(r.P[x][w], im);
		if (y==1&&z==1) r.P[x][w]=max(r.P[x][w], im+pli(-v, -1));
	}
	return r;
}

vector<dt> T[35005];
vlm XX;

struct Seg {
	node st[1<<17]; vector<int> v[1<<17];
	void init(int n, int s, int e, vlm &A) {
		if (s==e) {
			st[n]=node(1);
			st[n].V[0][0][0]=0;
			st[n].V[1][1][1]=A[s];
			return ;
		}
		int m=(s+e)/2;
		init(n*2, s, m, A); init(n*2+1, m+1, e, A);
		merge(st[n], st[n*2], st[n*2+1]);
	}
	void spr(int n, int s, int e, int ts, int te, int x) {
		if (e<ts||te<s) return ;
		if (ts<=s&&e<=te) { v[n].eb(x); return ; }
		int m=(s+e)/2;
		spr(n*2, s, m, ts, te, x); spr(n*2+1, m+1, e, ts, te, x);
	}
	void sol(int n, int s, int e) {
		int md=(s+e)/2;
		if (s!=e) sol(n*2, s, md), sol(n*2+1, md+1, e);
		
		if (s==e) {
			for (auto &i:v[n]) T[i].eb(pli(0, 0), pli(-LINF, 0), pli(-LINF, 0), pli(st[n].V[1][1][1]+XX[i], 1));
			return ;
		}

		sort(all(v[n]), [&](ll v1, ll v2) { return XX[v1]<XX[v2]; });
		vector<pli> im[4];
		for (int i=0; i<4; i++) {
			int x=(i&2)/2, y=i&1, t=x|y;
			for (int j=0; j<v[n].size(); j++) {
				while (t+1<=st[n].sz&&st[n].V[x][y][t]<=st[n].V[x][y][t+1]+XX[v[n][j]]) t++;
				im[i].eb(st[n].V[x][y][t]+t*XX[v[n][j]], t);
			}
		}
		for (int i=0; i<v[n].size(); i++) T[v[n][i]].eb(im[0][i], im[1][i], im[2][i], im[3][i]);
	}
}S;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N, Q; cin>>N>>Q;

	vlm A(N); for (auto &i:A) cin>>i;
	S.init(1, 0, N-1, A);

	vector<int> K;
	for (int i=0, l, r, k; i<Q; i++)
		cin>>l>>r>>k, S.spr(1, 0, N-1, --l, --r, i), K.eb(k);

	vlm s(Q, -MX), e(Q, MX); XX=vlm(Q);
	for (int t=27; t--; ) {
		for (int i=0; i<Q; i++) {
			if (s[i]>e[i]) e[i]=s[i];
			XX[i]=s[i]+(e[i]-s[i])/2;
			T[i].clear();
		}
		S.sol(1, 0, N-1);

		for (int i=0; i<Q; i++) {
			auto v=T[i][0];
			for (int j=1; j<T[i].size(); j++) v=merge(XX[i], v, T[i][j]);
			if (v.get().se<K[i]) s[i]=XX[i]+1;
			else e[i]=XX[i];
		}
	}
	for (int i=0; i<Q; i++) {
		auto v=T[i][0];
		for (int j=1; j<T[i].size(); j++) v=merge(XX[i], v, T[i][j]);
		cout<<v.get().fi-s[i]*K[i]<<'\n';
	}
	return 0;
}