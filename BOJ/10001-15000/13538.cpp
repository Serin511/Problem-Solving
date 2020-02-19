#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;

struct node {
	node *l, *r;
	int val;
	node(node *L, node *R) { l=L, r=R; }
}*im;
node* new_node() { return new node(im, im); }
vector<node*> rt;

void upd(node *nd, node *rf, int s, int e, int t) {
	nd->val=rf->val+1;
	if (s==e) return ;
	int md=(s+e)/2;
	if (t<=md) {
		nd->l=new_node(); nd->r=rf->r;
		upd(nd->l, rf->l, s, md, t);
	}else {
		nd->l=rf->l; nd->r=new_node();
		upd(nd->r, rf->r, md+1, e, t);
	}
}

int get1(node *n1, node *n2, int s, int e, int t, int bit) {
	if (s==e) return s;
	int md=(s+e)/2;
	if (t&(1<<bit)) {
		if (n2->l->val-n1->l->val) return get1(n1->l, n2->l, s, md, t, bit-1);
		else return get1(n1->r, n2->r, md+1, e, t, bit-1);
	}else {
		if (n2->r->val-n1->r->val) return get1(n1->r, n2->r, md+1, e, t, bit-1);
		else return get1(n1->l, n2->l, s, md, t, bit-1);
	}
}

int get2(node *nd, int s, int e, int ts, int te) {
	if (te<s||e<ts) return 0;
	if (ts<=s&&e<=te) return nd->val;
	int md=(s+e)/2;
	return get2(nd->l, s, md, ts, te)+get2(nd->r, md+1, e, ts, te);
}

int get_kth(node *n1, node *n2, int s, int e, int k) {
	if (s==e) return s;
	int md=(s+e)/2;
	if (n2->l->val-n1->l->val>=k) return get_kth(n1->l, n2->l, s, md, k);
	else return get_kth(n1->r, n2->r, md+1, e, k-n2->l->val+n1->l->val);
}

int main() {
	im=new node(NULL, NULL); im->l=im->r=im;
	rt.eb(new_node());
	int M; scanf("%d", &M);
	while (M--) {
		int q, l, r, x;
		scanf("%d", &q);
		if (q==1) {
			scanf("%d", &x);
			rt.eb(new_node());
			upd(rt.back(), rt[rt.size()-2], 0, (1<<19)-1, x);
		}
		if (q==2) {
			scanf("%d %d %d", &l, &r, &x);
			printf("%d\n", get1(rt[l-1], rt[r], 0, (1<<19)-1, x, 18));
		}
		if (q==3) {
			scanf("%d", &x);
			while (x--) rt.pop_back();
		}
		if (q==4) {
			scanf("%d %d %d", &l, &r, &x);
			printf("%d\n", get2(rt[r], 0, (1<<19)-1, 0, x)-get2(rt[l-1], 0, (1<<19)-1, 0, x));
		}
		if (q==5) {
			scanf("%d %d %d", &l, &r, &x);
			printf("%d\n", get_kth(rt[l-1], rt[r], 0, (1<<19)-1, x));
		}
	}
	return 0;
}