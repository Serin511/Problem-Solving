#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MX = 300005;

int X, Q;
ll N[MX], S[MX], B[MX];

struct node {
	int s, e;
	ll T[6];
	node() { s=e=0; fill(T, T+6, 0); }
}St[1<<20];

node operator +(node n1, node n2) {
	if (!n1.s) return n2;
	if (!n2.s) return n1;
	node r; r.s=n1.s, r.e=n2.e;
	r.T[0]=min(n1.T[0]+N[n1.e]+n2.T[0], n1.T[1]+S[n1.e]+n2.T[2]);
	r.T[1]=min(n1.T[0]+N[n1.e]+n2.T[1], n1.T[1]+S[n1.e]+n2.T[3]);
	r.T[2]=min(n1.T[2]+N[n1.e]+n2.T[0], n1.T[3]+S[n1.e]+n2.T[2]);
	r.T[3]=min(n1.T[2]+N[n1.e]+n2.T[1], n1.T[3]+S[n1.e]+n2.T[3]);
	r.T[4]=min(n1.T[4], n1.T[0]+n1.T[3]+N[n1.e]+S[n1.e]+n2.T[4]);
	r.T[5]=min(n2.T[5], n2.T[0]+n2.T[3]+N[n1.e]+S[n1.e]+n1.T[5]);
	return r;
}

void upd(int i, int s, int e, int ts, int te) {
	if (e<ts||te<s) return ;
	if (s==e) { St[i].s=St[i].e=s, St[i].T[0]=St[i].T[3]=0, St[i].T[1]=St[i].T[2]=St[i].T[4]=St[i].T[5]=B[s]; return ; }
	int md=(s+e)/2;
	upd(i*2, s, md, ts, te); upd(i*2+1, md+1, e, ts, te);
	St[i]=St[i*2]+St[i*2+1];
}

node get(int i, int s, int e, int ts, int te) {
	if (e<ts||te<s) return node();
	if (ts<=s&&e<=te) return St[i];
	int md=(s+e)/2;
	return get(i*2, s, md, ts, te)+get(i*2+1, md+1, e, ts, te);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin>>X;
	for (int i=1; i<X; i++) cin>>N[i];
	for (int i=1; i<X; i++) cin>>S[i];
	for (int i=1; i<=X; i++) cin>>B[i];
	upd(1, 1, X, 1, X);
	cin>>Q;
	while (Q--) {
		int q, x, y;
		cin>>q;
		if (q==1) {
			char c1, c2;
			cin>>c1>>x>>c2>>y;
			if (x>y) swap(x, y), swap(c1, c2);
			auto l=get(1, 1, X, 1, x), r=get(1, 1, X, y, X);
			if (x==y) cout<<(c1==c2?0:min(l.T[5], r.T[4]))<<'\n';
			else {
				l.s=l.e=x; l.T[0]=l.T[3]=0; l.T[1]=l.T[2]=l.T[4]=l.T[5];
				r.s=r.e=y; r.T[0]=r.T[3]=0; r.T[1]=r.T[2]=r.T[5]=r.T[4];
				if (y==x+1) l=l+r;
				else l=l+get(1, 1, X, x+1, y-1)+r;
				c1=(c1=='N'?0:1); c2=(c2=='N'?0:1);
				cout<<l.T[c1*2+c2]<<'\n';
			}
		}
		else cin>>x>>y;
		if (q==2) N[x]=y, upd(1, 1, X, x, x+1);
		if (q==3) S[x]=y, upd(1, 1, X, x, x+1);
		if (q==4) B[x]=y, upd(1, 1, X, x, x);
	}
	return 0;
}