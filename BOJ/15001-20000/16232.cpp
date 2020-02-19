#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

struct node {
	node *l, *r, *p;
	ll val, lz; ll x, lzx;
	node(){}
	node(ll X, ll Val, node *par) {l=r=NULL; p=par; lz=0; lzx=0; x=X; val=Val;}
};

node *root;
const ll INF=(1ll<<60);

inline void spread(node *now) {
	now->val += now->lz;
	now->x += now->lzx;
	if (now->l) {now->l->lz += now->lz; now->l->lzx += now->lzx;}
	if (now->r) {now->r->lz += now->lz; now->r->lzx += now->lzx;}
	now->lz=now->lzx=0;
}

inline void zig(node *p, node *d) {
	if (p->r == d) {
		p->r=d->l; if (d->l) d->l->p=p;
		d->l=p;
	}
	else if (p->l == d) {
		p->l=d->r; if (d->r) d->r->p=p;
		d->r=p;
	}
	d->p=p->p;
	if (p->p) {
		if (p->p->l == p) p->p->l=d;
		else p->p->r=d;
	}
	p->p=d;
}

inline void splay(node *now) {
	spread(now);
	if (!(now->p)) { return; }
	if (!(now->p->p)) { zig(now->p, now); return; }
	node *p=now->p; node *pp=p->p;
	if ((pp->l==p?0:1)!=(p->l==now?0:1)) {
		zig(p, now); zig(pp, now);
	}
	else {
		zig(pp, p); zig(p, now);
	}
	splay(now);
}

inline void ins(node *now, ll X, ll Val) {
	spread(now);
	if (now->x < X) {
		if (!(now->r)) {
			now->r = new node(X, Val, now);
			root=now->r; splay(now->r);
			return ;
		}
		ins(now->r, X, Val);
	}
	else {
		if (!(now->l)) {
			now->l = new node(X, Val, now);
			root=now->l; splay(now->l);
			return ;
		}
		ins(now->l, X, Val);
	}
}

inline node* find_and_splay(node *now, ll X) {
	spread(now);
	if (now->x == X) { splay(now); return now; }
	if (now->x < X) return find_and_splay(now->r, X);
	if (now->x > X) return find_and_splay(now->l, X);
}

inline pll get(node *now, ll X) {
	spread(now);
	pll ret={-INF,-INF};
	if ((now->x) == X) return pll(now->x, now->val);
	else if ((now->x) < X) return now->r?max(pll(now->x, now->val), get(now->r, X)):pll(now->x, now->val);
	else return now->l?get(now->l, X):ret;
}

inline ll ub(node *now, ll X) {
	spread(now);
	ll ret=INF;
	if (now->x <= X) return now->r?ub(now->r, X):ret;
	else {
		ret=now->x;
		return min(ret, now->l?ub(now->l, X):ret);
	}
}

int N;
ll a[200010], b[200010], k[200010];
ll ar[200010], ans[200010];

int main() {
	root=new node(-(1ll<<40), 0, NULL);
	ins(root, (1ll<<40), 0);
	scanf("%d", &N);
	for (int i=1; i<=N; i++) scanf("%lld %lld %lld", &a[i], &b[i], &k[i]);
	for (int i=1; i<=N; i++) ar[i]=ar[i-1]+(ar[i-1]<k[i]?a[i]:b[i]);
	node *nd; ll X, Y; pll pl;
	for (int i=N; i>=1; i--) {
		pl=get(root, ar[i-1]); Y=pl.se;
		root=find_and_splay(root, pl.fi);
		ans[i]=ar[i-1]+Y;

		pl=get(root, k[i]+b[i]); Y=pl.se;
		root=find_and_splay(root, pl.fi);

		pl=get(root, k[i]+a[i]-1);
		root=find_and_splay(root, pl.fi);

		root->r->p=NULL;
		root->r=find_and_splay(root->r, ub(root->r, k[i]+b[i]));
		root->r->l=NULL, root->r->p=root;

		root->x -= a[i], root->val += a[i];
		if (root->l) root->l->lz += a[i], root->l->lzx -= a[i];
		root->r->lz += b[i], root->r->lzx -= b[i];

		ins(root, k[i], Y+b[i]);
	}
	for (int i=1; i<=N; i++) printf("%lld\n", ans[i]);
	return 0;
}
