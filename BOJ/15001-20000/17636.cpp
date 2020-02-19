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
 
int R, C;
int dty_cnt=1; 
struct dty {
	int l, r, dt, Key;
}st2[(1<<24)];
int new_dty(int k) { st2[dty_cnt].Key=k; return dty_cnt++; }
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

int root;
int n, q;
char s[10]; int I, a, b;
int ar[300010];
set<pair<pii, int> > S;

int main() {
	root=new_dtx();
	scanf("%d %d", &n, &q);
	R=C=n;
	for (int i=1; i<=n; i++) scanf("%1d", &ar[i]);
	for (int i=1; i<=n; i++) {
		if (!ar[i]) continue;
		int j;
		for (j=i; j<=n; j++) if (!ar[j]) break;
		S.insert({make_pair(i, j-1), 0});
		i=j-1;
	}
	set<pair<pii, int> >::iterator it;
	pair<pii, int> pi, pi1, pi2;
	int ans;
	for (int i=1; i<=q; i++) {
		scanf("%s", s);
		if (s[0]=='t') {
			scanf("%d", &I);
			if (ar[I]) {
				it=S.upper_bound({make_pair(I, (1<<30)), (1<<30)});
				it--; pi=(*it); S.erase(it);
				upd1(root, pi.fi.fi, pi.fi.se, i-pi.se, 1, R);
				if (pi.fi.fi<I) S.insert({make_pair(pi.fi.fi, I-1), i});
				if (pi.fi.se>I) S.insert({make_pair(I+1, pi.fi.se), i});
			}
			else {
				if (ar[I-1]) {
					it=S.upper_bound({make_pair(I-1, (1<<30)), (1<<30)});
					it--; pi1=(*it); S.erase(it);
					upd1(root, pi1.fi.fi, pi1.fi.se, i-pi1.se, 1, R);
				}
				else pi1={make_pair(I, I), 0};
				if (ar[I+1]) {
					it=S.upper_bound({make_pair(I+1, (1<<30)), (1<<30)});
					it--; pi2=(*it); S.erase(it);
					upd1(root, pi2.fi.fi, pi2.fi.se, i-pi2.se, 1, R);
				}
				else pi2={make_pair(I, I), 0};
				S.insert({make_pair(pi1.fi.fi, pi2.fi.se), i});
			}
			ar[I]=1-ar[I];
		}
		else {
			scanf("%d %d", &a, &b); b--;
			if (!S.size()) ans=0;
			else {
				it=S.upper_bound({make_pair(a, (1<<30)), (1<<30)});
				if (it==S.begin()) ans=0;
				else {
					it--;
					if ((*it).fi.fi<=a&&(*it).fi.se>=b) ans=i-(*it).se;
					else ans=0;
				}
			}
			ans+=get1(root, 1, b, a, C, 1, R);
			printf("%d\n", ans);
		}
	}
	return 0;
}