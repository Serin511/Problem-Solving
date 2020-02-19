#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define Enc(x, y) (H2[x][y])
#define Dec(x) (H1[x])
#define getcnt(x) ((x+2)*(x+1)/2)
using namespace std;
typedef vector<int> vim;
typedef pair<int, int> pii;

int M, N;
int c[710][710][3][3][3];
int ans[710][710];

int Fen[1410];
void upd(int t, int v) { while (t<=M*2+1) Fen[t]+=v, t+=t&-t; }
int get(int t) { int ret=0; while (t) ret+=Fen[t], t-=t&-t; return ret; }

vector<pii> H1; int H2[1410][1410];
void init() {
	for (int i=0; i<=2*M-1; i++) for (int j=0; j<=2*M-1-i; j++) H1.eb(i, j);
	sort(all(H1), [](pii p1, pii p2){ return p1.fi+p1.se<p2.fi+p2.se; });
	for (int i=0; i<H1.size(); i++) H2[H1[i].fi][H1[i].se]=i;
}

pii sum(pii a, pii b) { return pii(a.fi+b.fi, a.se+b.se); }
pii sub(pii a, pii b) { return pii(a.fi-b.fi, a.se-b.se); }

pii cut1(int x, int v) {
	pii P=Dec(x);
	if (P.fi+P.se<=v) return pii(P.fi, P.se);
	if (P.fi<=v) return pii(P.fi, v-P.fi);
	return pii(v, 0);
}

pii cut3(int x, int v, int m) {
	pii P=Dec(x); int c=m-P.fi-P.se;
	if (P.se+c<=v) return pii(v-P.se-c, P.se);
	if (c<=v) return pii(0, v-c);
	return pii(0, 0);
}

vim dnc(vim &A, int x1, int y1, int x2, int y2) {
	int H=(x2-x1+1), W=(y2-y1+1), sz=A.size();
	if (x1==x2&&y1==y2) {
		vim ret(sz); pii im; int x, y, z, w;
		for (int i=0; i<A.size(); i++) {
			im=Dec(i);
			x=((im.fi>=1)?0:(im.fi+im.se>=1)?1:2);
			y=((im.fi>=2)?0:(im.fi+im.se>=2)?1:2);
			z=((im.fi>=3)?0:(im.fi+im.se>=3)?1:2);
			w=c[x1][y1][x][y][z];
			ans[x1][y1]+=A[i]*w;
			ret[i]=(w==0?Enc(1, 0):w==1?Enc(0, 1):Enc(0, 0));
		}
		return ret;
	}
	else if (x1==x2) {
		vim ret(sz), s1, r1, s2, r2; pii im, im1;

		s1.resize(10);
		for (int i=0; i<A.size(); i++) {
			im=cut1(i, 3);
			s1[Enc(im.fi, im.se)]+=A[i];
		}
		r1=dnc(s1, x1, y1, x1, y1);

		s2.resize(10);
		for (int i=0; i<A.size(); i++) {
			im=cut1(i, 3);
			im=sum(Dec(r1[Enc(im.fi, im.se)]), cut3(i, 2, H+W+1));
			s2[Enc(im.fi, im.se)]+=A[i];
		}
		r2=dnc(s2, x2, y2, x2, y2);

		for (int i=0; i<A.size(); i++) {
			im=cut1(i, 3); im1=sum(Dec(r1[Enc(im.fi, im.se)]), cut3(i, 2, H+W+1));
			im=sum(Dec(r1[Enc(im.fi, im.se)]), Dec(r2[Enc(im1.fi, im1.se)]));
			ret[i]=Enc(im.fi, im.se);
		}
		return ret;
	}
	else if (y1==y2) {
		vim ret(sz), s1, r1, s2, r2; pii im, im1;

		s1.resize(10);
		for (int i=0; i<A.size(); i++) {
			im=cut3(i, 3, H+W+1);
			s1[Enc(im.fi, im.se)]+=A[i];
		}
		r1=dnc(s1, x1, y1, x1, y1);

		s2.resize(10);
		for (int i=0; i<A.size(); i++) {
			im=cut3(i, 3, H+W+1);
			im=sum(Dec(r1[Enc(im.fi, im.se)]), cut1(i, 2));
			s2[Enc(im.fi, im.se)]+=A[i];
		}
		r2=dnc(s2, x2, y2, x2, y2);

		for (int i=0; i<A.size(); i++) {
			im=cut3(i, 3, H+W+1); im1=sum(Dec(r1[Enc(im.fi, im.se)]), cut1(i, 2));
			im=sum(Dec(r1[Enc(im.fi, im.se)]), Dec(r2[Enc(im1.fi, im1.se)]));
			ret[i]=Enc(im.fi, im.se);
		}
		return ret;
	}

	vim s1, r1, s2, r2, s3, r3, s4, r4, ret(A.size());
	pii im; int h, w;
	int mdx=(x1+x2)/2, mdy=(y1+y2)/2;
	

	h=mdx-x1+1, w=mdy-y1+1;
	s1.resize(getcnt(h+w+1));
	for (int i=0; i<A.size(); i++) {
		im=Dec(i);
		im=sub(sub(im, cut1(i, H-h)), cut3(i, W-w, H+W+1));
		s1[Enc(im.fi, im.se)]+=A[i];
	}
	r1=dnc(s1, x1, y1, mdx, mdy);
	
	for (int i=0; i<A.size(); i++) {
		im=Dec(i);
		im=sub(sub(im, cut1(i, H-h)), cut3(i, W-w, H+W+1));
		im=sum(sum(cut1(i, H-h+1), Dec(r1[Enc(im.fi, im.se)])), cut3(i, W-w+1, H+W+1));
		ret[i]=Enc(im.fi, im.se);
	}


	h=x2-mdx, w=mdy-y1+1;
	s2.resize(getcnt(h+w+1));
	for (int i=0; i<A.size(); i++) {
		im=cut1(ret[i], h+w+1);
		s2[Enc(im.fi, im.se)]+=A[i];
	}
	r2=dnc(s2, mdx+1, y1, x2, mdy);
	
	for (int i=0; i<A.size(); i++) {
		im=cut1(ret[i], h+w+1);
		im=sum(sum(cut1(ret[i], 1), Dec(r2[Enc(im.fi, im.se)])), cut3(ret[i], H+W+1-h-w, H+W+1));
		ret[i]=Enc(im.fi, im.se);
	}


	h=mdx-x1+1, w=y2-mdy;
	s3.resize(getcnt(h+w+1));
	for (int i=0; i<A.size(); i++) {
		im=cut3(ret[i], h+w+1, H+W+1);
		s3[Enc(im.fi, im.se)]+=A[i];
	}
	r3=dnc(s3, x1, mdy+1, mdx, y2);

	for (int i=0; i<A.size(); i++) {
		im=cut3(ret[i], h+w+1, H+W+1);
		im=sum(cut1(ret[i], H+W+1-h-w), sum(Dec(r3[Enc(im.fi, im.se)]), cut3(ret[i], 1, H+W+1)));
		ret[i]=Enc(im.fi, im.se);
	}


	h=x2-mdx, w=y2-mdy;
	s4.resize(getcnt(h+w+1));
	for (int i=0; i<A.size(); i++) {
		im=sub(sub(Dec(ret[i]), cut1(ret[i], W-w)), cut3(ret[i], H-h, H+W+1));
		s4[Enc(im.fi, im.se)]+=A[i];
	}
	r4=dnc(s4, mdx+1, mdy+1, x2, y2);

	for (int i=0; i<A.size(); i++) {
		im=sub(sub(Dec(ret[i]), cut1(ret[i], W-w)), cut3(ret[i], H-h, H+W+1));
		im=sum(cut1(ret[i], W-w+1), sum(Dec(r4[Enc(im.fi, im.se)]), cut3(ret[i], H-h+1, H+W+1)));
		ret[i]=Enc(im.fi, im.se);
	}

	for (auto &i:ret) {
		im=sub(sub(Dec(i), cut1(i, 1)), cut3(i, 1, H+W+1));
		i=Enc(im.fi, im.se);
	}

	return ret;
}

int main() {
	scanf("%d %d", &M, &N); init();
	char C;
	for (int i=1; i<M; i++) for (int j=1; j<M; j++) for (int x=0; x<3; x++) for (int y=0; y<3; y++) for (int z=0; z<3; z++) {
		scanf(" %c", &C);
		if (C=='L') c[i][j][x][y][z]=x;
		else if (C=='D') c[i][j][x][y][z]=y;
		else c[i][j][x][y][z]=z;
	}
	//3H(2*M-1) = (2M+1)C2
	vim A(getcnt(M*2-1));
	for (int i=1; i<=N; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		A[Enc(u, v)]++;
		upd(u+1, 1); upd(u+v+1, 1);
	}
	dnc(A, 1, 1, M-1, M-1);
	int t=1;
	for (int i=M-1; i>=0; i--, t++) ans[i][0]=get(t);
	for (int i=1; i<M; i++, t++) ans[0][i]=get(t);

	for (int i=0; i<M; i++) {
		for (int j=0; j<M; j++) printf("%d ", ans[i][j]+1);
		puts("");
	}
	return 0;
}