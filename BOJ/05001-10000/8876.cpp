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
struct dty {
    dty *l, *r;
    ll dt, L, R; int Key;
    int md;
    dty(int k) {Key=k; dt=0; l=r=NULL;}
    inline void upd(int y, ll val, int ys, int ye) {
        md=(ys+ye)/2;
        if (Key) {
            if (Key==y) {dt=val; return ;}
            if (Key<=md) { l=new dty(Key); l->dt=dt; }
            else { r=new dty(Key); r->dt=dt; }
            Key=0;
        }
        if (y<=md) {
            if (!l) l=new dty(y);
            l->upd(y, val, ys, md);
        }
        else {
            if (!r) r=new dty(y);
            r->upd(y, val, md+1, ye);
        }
        L=(l?l->dt:0);
        R=(r?r->dt:0);
        dt=__gcd(L, R);
    }
    inline ll get(int y1, int y2, int ys, int ye) {
        md=(ys+ye)/2;
        if (Key) return (y1<=Key&&Key<=y2)?dt:0;
        if (y1<=ys&&ye<=y2) return dt;
        L=R=0;
        if (!(md<y1)) L=(l?(l->get(y1, y2, ys, md)):0);
        if (md+1<=y2&&md+1<=ye) R=(r?r->get(y1, y2, md+1, ye):0);
        return __gcd(L, R);
    }
    inline ll get(int y, int ys, int ye) {
        md=(ys+ye)/2;
        if (Key) return (y==Key?dt:0);
        if (y<=md) return l?l->get(y, ys, md):0;
        else return r?r->get(y, md+1, ye):0;
    }
};
 
struct dtx {
    dty *seg;
    dtx *l, *r;
    int md;
    ll L, R;
    dtx() {l=r=NULL; seg=NULL;}
    inline void upd(int x, int y, ll val, int xs, int xe) {
        if (!seg) seg=new dty(y);
        if (xs==xe) {seg->upd(y, val, 1, C); return ;}
        md=(xs+xe)/2;
        if (x<=md) {
            if (!l) l=new dtx();
            l->upd(x, y, val, xs, md);
        }
        else {
            if (!r) r=new dtx();
            r->upd(x, y, val, md+1, xe);
        }
        L=(l?(l->seg->get(y, 1, C)):0);
        R=(r?(r->seg->get(y, 1, C)):0);
        seg->upd(y, __gcd(L, R), 1, C);
    }
    inline ll get(int x1, int y1, int x2, int y2, int xs, int xe) {
        if (!seg) return 0;
        if (x1<=xs&&xe<=x2) return seg->get(y1, y2, 1, C);
        md=(xs+xe)/2;
        L=R=0;
        if (x1<=md) L=(l?(l->get(x1, y1, x2, y2, xs, md)):0);
        if (md+1<=x2&&md+1<=xe) R=(r?(r->get(x1, y1, x2, y2, md+1, xe)):0);
        return __gcd(L, R);
    }
};
 
dtx *root;
 
void init(int r_, int c_) {
    R=r_, C=c_;
    root=new dtx();
}
  
void update(int P, int Q, ll K) {
    root->upd(P+1, Q+1, K, 1, R);
}
  
ll calculate(int P, int Q, int U, int V) {
    return root->get(P+1, Q+1, U+1, V+1, 1, R);
}
 
int main() {
    int r, c, n;
    int q, x1, y1, x2, y2; ll val;
    scanf("%d %d %d", &r, &c, &n);
    init(r, c);
    for (int i=0; i<n; i++) {
        scanf("%d", &q);
        if (q==1) {
            scanf("%d %d %lld", &x1, &y1, &val);
            update(x1, y1, val);
        }
        if (q==2) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            printf("%lld\n", calculate(x1, y1, x2, y2));
        }
    }
}