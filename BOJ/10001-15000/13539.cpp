#include <bits/stdc++.h>
using namespace std;

struct node {
	node *l, *r, *p; int num;
	node(int N) : l(NULL), r(NULL), p(NULL), num(N) {}
}*nd[100010];

bool isRoot(node *x) { return (!(x->p) || (x->p->l!=x&&x->p->r!=x)); }

void zig(node *p, node *d) {
	if (p->r == d) { p->r=d->l; if (d->l) d->l->p=p; d->l=p; }
	else if (p->l == d) { p->l=d->r; if (d->r) d->r->p=p; d->r=p; }
	d->p=p->p;
	if (!isRoot(p)) {
		if (p->p->l == p) p->p->l=d;
		else p->p->r=d;
	}
	p->p=d;
}

void splay(node *x) {
	if (isRoot(x)) { return; }
	if (isRoot(x->p)) { zig(x->p, x); return; }
	node *p=x->p; node *pp=p->p;
	if ((pp->l==p)^(p->l==x)) { zig(p, x); zig(pp, x); }
	else { zig(pp, p); zig(p, x); }
	splay(x);
}

node* access(node *x) {
	splay(x);
	x->r=NULL;
	node *ret=x;
	while (x->p) {
		node *y=x->p; ret=y;
		splay(y); y->r=x; splay(x); 
	}
	return ret;
}

void link(node *x, node *y) {
	access(x), access(y);
	x->l=y, y->p=x;
}

void cut(node *x) {
	access(x);
	if (x->l) x->l->p=NULL, x->l=NULL;
}

node* lca(node *x, node *y) {
	access(x); return access(y);
}

int N, Q;

int main() {
	scanf("%d %d", &N, &Q);
	for (int i=1; i<=N; i++) nd[i]=new node(i);
	while (Q--) {
		int q, u, v;
		scanf("%d", &q);
		if (q==1) scanf("%d %d", &u, &v), link(nd[u], nd[v]);
		if (q==2) scanf("%d", &u), cut(nd[u]);
		if (q==3) scanf("%d %d", &u, &v), printf("%d\n", lca(nd[u], nd[v])->num);
	}
	return 0;
}