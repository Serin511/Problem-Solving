#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).resize(unique(all(V))-(V).begin())
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
const ll INF = (1ll<<60);
const int MAX = 1e9;

/*
disjoint set for fast coding
struct djs {
	vector<int> p;
	djs(int n) : p(n+1) {}
	int gp(int u) { return p[u]?(p[u]=gp(p[u])):u; }
	bool un(int u, int v) {
		u=gp(u), v=gp(v);
		if (u!=v) p[v]=u;
		return u!=v;
	}
};
*/

/*
fft

using bs = complex<long double>;

void fft(vector<bs> &a, bool inv) {
    int n=a.size();
    for (int i=1, j=0; i<n; i++){
        int b=n/2;
        for (; j>=b; b/=2) j-=b;
        j+=b;
		if (i<j) swap(a[i], a[j]);
    }
	for (int l=2; l<=n; l*=2) {
		double t=2*M_PI/l*(inv?-1:1);
		bs wl(cos(t), sin(t));
		for (int i=0; i<n; i+=l) {
			bs w(1);
			for (int j=0; j<l/2; j++) {
				bs u=a[i+j], v=a[i+j+l/2]*w;
				a[i+j]=u+v;
				a[i+j+l/2]=u-v;
				w*=wl;
			}
		}
	}
	if (inv) for (auto &i:a) i/=n;
}

vector<ll> mul(const vector<ll> &a, const vector<ll> &b) {
	vector<bs> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n=1;
	while (n<a.size()+b.size()) n*=2;
	fa.resize(n); fft(fa, 0);
	fb.resize(n); fft(fb, 0);
	vector<bs> fr(n);
	for (int i=0; i<n; i++) fr[i]=fa[i]*fb[i];
	fft(fr, 1);
	vector<ll> r;
	for (auto &i:fr) r.emplace_back((ll)(i.real()+(i.real()>0?0.5:-0.5)));
	return r;
}
*/

/*
ntt
primes: 998244353, 2281701377, 2483027969, 104857601, 1092616193

ll pw(ll n, ll k, ll m) {
	ll r=1;
	while (k) {
		if (k&1) r=r*n%m;
		k/=2;
		n=n*n%m;
	}
	return r;
}

void ntt(vector<ll> &a, bool inv, ll p) {
    int n=a.size();
    for (int i=1, j=0; i<n; i++){
        int b=n/2;
        for (; j>=b; b/=2) j-=b;
        j+=b;
		if (i<j) swap(a[i], a[j]);
	}
	ll t=pw(3, (p-1)/n, p);
	if (inv) t=pw(t, p-2, p);
	vector<ll> r(n/2);
	r[0]=1;
	for (int i=1; i<n/2; i++) r[i]=r[i-1]*t%p;
	for (int l=2; l<=n; l*=2) {
		int st=n/l;
		for (int i=0; i<n; i+=l) for (int j=0; j<l/2; j++) {
			ll u=a[i+j], v=a[i+j+l/2]*r[st*j]%p;
			a[i+j]=(u+v)%p;
			a[i+j+l/2]=(u-v+p)%p;
		}
	}
	t=pw(n, p-2, p);
	if (inv) for (auto &i:a) i=i*t%p;
}

vector<ll> mul(const vector<ll> &a, const vector<ll> &b, ll p) {
	vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n=1;
	while (n<max(a.size(), b.size())) n*=2;
	fa.resize(n); ntt(fa, 0, p);
	fb.resize(n); ntt(fb, 0, p);
	vector<ll> fr(n);
	for (int i=0; i<n; i++) fr[i]=fa[i]*fb[i]%p;
	ntt(fr, 1, p);
	return fr;
}

*/


/*
cout round
fixed<<setprecision(4)
*/

/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set

*/

/*
fastio
cin.tie(0)->sync_with_stdio(0);
*/

/*
random
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
*/

/*Pragma
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,sse4,abm,avx,avx2")
*/

/*Debug
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _FORTIFY_SOURCE 2
*/

namespace My_Seg {
template <typename T> struct Seg {
	function<T(T, T)> mg;
	vector<T> st;
	int N;
	Seg(int N, T gen = T(), function<T(T, T)> fmg = [&](T t1, T t2) { return t1+t2; })
		: st(1<<(33-__builtin_clz(N)), gen), mg(fmg) { this->N=N; }
	void init(int i, int s, int e, T *V) {
		if (s==e) { st[i]=V[s]; return ; }
		int m=(s+e)/2;
		init(i*2, s, m, V); init(i*2+1, m+1, e, V);
		st[i]=mg(st[i*2], st[i*2+1]);
	}
	void init(T *V) { init(1, 1, N, V); }
	void upd(int i, int s, int e, int t, T v) {
		if (s==e) { st[i]=mg(st[i], v); return ; }
		int m=(s+e)/2;
		if (t<=m) upd(i*2, s, m, t, v);
		else upd(i*2+1, m+1, e, t, v);
	}
	void upd(int t, T v) { upd(1, 1, N, t, v); }
	T get(int i, int s, int e, int l, int r) {
		if (e<l||r<s) return T();
		if (l<=s&&e<=r) return st[i];
		int m=(s+e)/2;
		return mg(get(i*2, s, m, l, r), get(i*2+1, m+1, e, l, r));
	}
	T get(int l, int r) { return get(1, 1, N, l, r); }
};
}

namespace Centroid_Decomposition {

vector<pil> adj[MX], dp[MX];

void cent() {
	vector<int> c1(N+1), c2(N+1), sz(N+1); int t=1;

	function<void(int, int, int)> d1 = [&](int n, int p, int lv) {
		sz[n]=1; c1[n]=lv;
		for (auto &i:adj[n]) if (i.fi!=p && !c2[i.fi]) d1(i.fi, n, lv), sz[n]+=sz[i.fi];
	};

	function<int(int, int, int)> d2 = [&](int n, int p, int s) {
		for (auto &i:adj[n]) if (i.fi!=p && !c2[i.fi] && sz[i.fi]>s) return d2(i.fi, n, s);
		return n;
	};

	function<void(int, int, int, ll)> d3 = [&](int n, int p, int c, ll d) {
		dp[n].eb(c, d);
		for (auto &i:adj[n]) if (i.fi!=p && !c2[i.fi]) d3(i.fi, n, c, d+i.se);
		return 0;
	};

	int cnt=0;
	while (cnt<N&&t++) for (int i=1; i<=N; i++) if (!c2[i] && c1[i]!=t) {
		d1(i, 0, t);
		int c=d2(i, 0, sz[i]/2);
		d3(c, 0, c, 0);
		c2[c]=1; cnt++;
	}
}

}

namespace fastio {
inline void fi(int &number) { 
    bool negative = false; 
    register int c; 
    number = 0; 
    c = getchar(); 
    if (c=='-') { 
        negative = true;
        c = getchar(); 
    }
    for (; (c>47 && c<58); c=getchar()) 
        number = number *10 + c - 48; 
    if (negative) 
        number *= -1; 
}
}

namespace Dynamic_Max_Seg {
	struct node {
		int val, ind;
		node *l, *r;
		node (int val, int ind, node *l, node *r) :val(val), ind(ind), l(l), r(r) {}
	} *Tree[200010];

	node *make_tree(node *now, int fr, int re, int y, int val) {
		if (!(fr<=y&&y<re)) return now;
		node *ret=new node(0, 0, NULL, NULL);
		if (fr+1==re) {
			ret->val=max(now->val,val);
			return ret;
		}
		int md=(fr+re)/2;
		ret->l=make_tree(now->l, fr, md, y, val, ind);
		ret->r=make_tree(now->r, md, re, y, val, ind);
		ret->val=max((ret->l?ret->l->val:0),(ret->r?ret->r->val:0));
		return ret;
	}

	int mx_rng(node *now, int fr, int re, int s, int e) {
		if (s<=fr&&re<=e) return now->val;
		else if (re<=s||e<=fr) return 0;
		int md=(fr+re)/2;
		return max(mx_rng(now->l, fr, md, s, e), mx_rng(now->r, md, re, s, e));
	}
}

namespace LiChao_Tree { //Min-CHT
struct line {
	ll a, b;
	ll get(ll x) { return a*x+b; }
	line() { a=0, b=INF; }
	line(ll A, ll B) { a=A, b=B; }
};

struct LiChao {
	vector<int> l, r;
	vector<line> L;
	LiChao() : l(2), r(2), L(2) {}
	int new_line() {
		l.emplace_back(0); r.emplace_back(0); L.emplace_back(line());
		return l.size()-1;
	}
	void upd(int n, line v, ll s, ll e) {
		ll md=(s+e)/2;
		line lo=L[n], hi=v;
		if (lo.get(s)<hi.get(s)) swap(lo, hi);
		if (lo.get(e)>=hi.get(e)) { L[n]=hi; return ; }

		if (lo.get(md)<=hi.get(md)) {
			L[n]=lo;
			if (!l[n]) { l[n]=new_line(); }
			upd(l[n], hi, s, md);
		}
		else {
			L[n]=hi;
			if (!r[n]) { r[n]=new_line(); }
			upd(r[n], lo, md+1, e);
		}
	}
	ll get(int n, ll x, ll s, ll e) {
		if (!n) return INF;
		ll md=(s+e)/2;
		if (x<=md) return min(L[n].get(x), get(l[n], x, s, md));
		else return min(L[n].get(x), get(r[n], x, md+1, e));
	}
	void add(ll a, ll b) { upd(1, line(a, b), 0, 1e18); }
	ll get(ll x) { return get(1, x, 0, 1e18); }
};
}

namespace PLCT { //Min-CHT
struct line {
	ll a, b;
	ll get(ll x) { return a*x+b; }
	line() {}
	line(ll A, ll B) { a=A, b=B; }
};

struct node {
	int l, r;
	line L;
	node() { L=line(0, INF); }
}st[(1<<23)]; int nd_tp=1;
int new_node() { return nd_tp++; }

void upd(int now, int ref, line v, ll s, ll e) {
	st[now].l = st[ref].l;
	st[now].r = st[ref].r;
	ll md=(s+e)/2;
	line lo=st[ref].L, hi=v;
	if (lo.get(s)<hi.get(s)) swap(lo, hi);
	if (lo.get(e)>=hi.get(e)) { st[now].L=hi; return ; }

	if (lo.get(md)<hi.get(md)) {
		st[now].L = lo;
		st[now].l = new_node();
		upd(st[now].l, st[ref].l, hi, s, md);
	}
	else {
		st[now].L = hi;
		st[now].r = new_node();
		upd(st[now].r, st[ref].r, lo, md+1, e);
	}
}

ll get(int now, ll x, ll s, ll e) {
	if (!now) return INF;
	ll md=(s+e)/2;
	if (x<=md) return min(st[now].L.get(x), get(st[now].l, x, s, md));
	else return min(st[now].L.get(x), get(st[now].r, x, md+1, e));
}
}


namespace Dynamic_2D_Seg {
struct dty {
	int l, r, dt, Key;
}st2[(1<<24)];
int dty_cnt=1; int new_dty(int k) { st2[dty_cnt].Key=k; return dty_cnt++; }
inline void upd2(int now, int y, int val, int ys, int ye) {
	int md=(ys+ye)/2;
	if (st2[now].Key) {
		if (st2[now].Key==y) { st2[now].dt+=val; return ;}
		if (st2[now].Key<=md) { st2[now].l=new_dty(st2[now].Key); st2[st2[now].l].dt=st2[now].dt; }
		else { st2[now].r=new_dty(st2[now].Key); st2[st2[now].r].dt=st2[now].dt; }
		st2[now].Key=0;
	}
	if (y<=md) {
		if (!st2[now].l) st2[now].l=new_dty(y);
		upd2(st2[now].l, y, val, ys, md);
	}
	else {
		if (!st2[now].r) st2[now].r=new_dty(y);
		upd2(st2[now].r, y, val, md+1, ye);
	}
	int L, R;
	L=(st2[now].l?st2[st2[now].l].dt:0);
	R=(st2[now].r?st2[st2[now].r].dt:0);
	st2[now].dt=L+R;
}
inline int get2(int now, int y1, int y2, int ys, int ye) {
	int md=(ys+ye)/2;
	if (st2[now].Key) return (y1<=st2[now].Key&&st2[now].Key<=y2)?st2[now].dt:0;
	if (y1<=ys&&ye<=y2) return st2[now].dt;
	int L, R; L=R=0;
	if (!(md<y1)) L=(st2[now].l?(get2(st2[now].l, y1, y2, ys, md)):0);
	if (md+1<=y2&&md+1<=ye) R=(st2[now].r?get2(st2[now].r, y1, y2, md+1, ye):0);
	return L+R;
}

struct dtx {
	int seg, l, r;
}st1[(1<<19)];
int dtx_cnt=1; int new_dtx() { return dtx_cnt++; }

inline void upd1(int now, int x, int y, int val, int xs, int xe) {
	if (!st1[now].seg) st1[now].seg=new_dty(y);
	if (xs==xe) { upd2(st1[now].seg, y, val, 1, C); return ; }
	int md=(xs+xe)/2;
	if (x<=md) {
		if (!st1[now].l) st1[now].l=new_dtx();
		upd1(st1[now].l, x, y, val, xs, md);
	}
	else {
		if (!st1[now].r) st1[now].r=new_dtx();
		upd1(st1[now].r, x, y, val, md+1, xe);
	}
	upd2(st1[now].seg, y, val, 1, C);
}
inline int get1(int now, int x1, int y1, int x2, int y2, int xs, int xe) {
	if (!st1[now].seg) return 0;
	if (x1<=xs&&xe<=x2) return get2(st1[now].seg, y1, y2, 1, C);
	int md=(xs+xe)/2, L, R; L=R=0;
	if (x1<=md) L=(st1[now].l?get1(st1[now].l, x1, y1, x2, y2, xs, md):0);
	if (md+1<=x2&&md+1<=xe) R=(st1[now].r?get1(st1[now].r, x1, y1, x2, y2, md+1, xe):0);
	return L+R;
}
}

namespace berlekamp {

const int mod = 998244353;
using ll = long long;
//berlekamp-massey code from https://gist.github.com/koosaga/d4afc4434dbaa348d5bef0d60ac36aa4
ll ipow(ll x, ll p){
	ll ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}
vector<int> berlekamp_massey(vector<int> x){
	vector<int> ls, cur;
	int lf, ld;
	for(int i=0; i<x.size(); i++){
		ll t = 0;
		for(int j=0; j<cur.size(); j++){
			t = (t + 1ll * x[i-j-1] * cur[j]) % mod;
		}
		if((t - x[i]) % mod == 0) continue;
		if(cur.empty()){
			cur.resize(i+1);
			lf = i;
			ld = (t - x[i]) % mod;
			continue;
		}
		ll k = -(x[i] - t) * ipow(ld, mod - 2) % mod;
		vector<int> c(i-lf-1);
		c.push_back(k);
		for(auto &j : ls) c.push_back(-j * k % mod);
		if(c.size() < cur.size()) c.resize(cur.size());
		for(int j=0; j<cur.size(); j++){
			c[j] = (c[j] + cur[j]) % mod;
		}
		if(i-lf+(int)ls.size()>=(int)cur.size()){
			tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
		}
		cur = c;
	}
	for(auto &i : cur) i = (i % mod + mod) % mod;
	return cur;
}
int get_nth(vector<int> rec, vector<int> dp, ll n){
	int m = rec.size();
	vector<int> s(m), t(m);
	s[0] = 1;
	if(m != 1) t[1] = 1;
	else t[0] = rec[0];
	auto mul = [&rec](vector<int> v, vector<int> w){
		int m = v.size();
		vector<int> t(2 * m);
		for(int j=0; j<m; j++){
			for(int k=0; k<m; k++){
				t[j+k] += 1ll * v[j] * w[k] % mod;
				if(t[j+k] >= mod) t[j+k] -= mod;
			}
		}
		for(int j=2*m-1; j>=m; j--){
			for(int k=1; k<=m; k++){
				t[j-k] += 1ll * t[j] * rec[k-1] % mod;
				if(t[j-k] >= mod) t[j-k] -= mod;
			}
		}
		t.resize(m);
		return t;
	};
	while(n){
		if(n & 1) s = mul(s, t);
		t = mul(t, t);
		n >>= 1;
	}
	ll ret = 0;
	for(int i=0; i<m; i++) ret += 1ll * s[i] * dp[i] % mod;
	return ret % mod;
}
}
