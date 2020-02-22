#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef array<ull, 40> bs;

bs operator -(const bs &b1, const bs &b2) {
	bs ret; ull c=0;
	auto f=[](ull &x, ull y) {
		ull t=x;
		return (x=t-y)>t;
	};
	for (int i=0; i<40; i++) {
		ret[i]=b1[i];
		c=f(ret[i], c);
		c+=f(ret[i], b2[i]);
	}
	return ret;
}

bs operator |(const bs &b1, const bs &b2) {
	bs ret;
	for (int i=0; i<40; i++) ret[i]=b1[i]|b2[i];
	return ret;
}

bs operator ^(const bs &b1, const bs &b2) {
	bs ret;
	for (int i=0; i<40; i++) ret[i]=b1[i]^b2[i];
	return ret;
}

bs operator &(const bs &b1, const bs &b2) {
	bs ret;
	for (int i=0; i<40; i++) ret[i]=b1[i]&b2[i];
	return ret;
}

bs shift(const bs &b) {
	bs ret; ull c=0;
	for (int i=0; i<40; i++) ret[i]=c|(b[i]<<1), c=b[i]>>63;
	return ret;
}

int lcs(char *s, char *t) {
	int n=strlen(s), m=strlen(t);
	bs M[256], B, X, Y;
	for (int i=0; i<256; i++) for (int j=0; j<40; j++) M[i][j]=0;
	for (int i=0; i<40; i++) B[i]=X[i]=Y[i]=0;
	for (int i=0; i<m; i++) M[t[i]][i>>6]|=(1llu<<(i&63));
	for (int i=0; i<m; i++) if (s[0]==t[i]) { B[i>>6]|=(1llu<<(i&63)); break;}
	for (int i=1; i<n; i++) {
		X=B|M[s[i]];
		Y=shift(B); Y[0]|=1;
		B=X&(X^(X-Y));
		B[m>>6]&=(1llu<<(m&63))-1;
	}
	int c=0;
	for (int i=0; i<m; i++) if (B[i>>6]&(1llu<<(i&63))) c++;
	return c;
}

int main() {
	char s[1510], t[1510];
	while (scanf("%s %s", s, t)==2) {
		int n=strlen(s), a=0;
		for (int j=0; j<2; j++) {
			for (int i=1; i<=n; i++) {
				a=max(a, lcs(s, t));
				rotate(s, s+1, s+n);
			}
			reverse(s, s+n);
		}
		printf("%d\n", a*2);
	}
	return 0;
}