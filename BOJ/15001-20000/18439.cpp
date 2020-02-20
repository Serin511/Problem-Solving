#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef array<ull, 1000> bs;

bs M[26], B, X, Y;
char s[50005], t[50005];

bs operator -(const bs &b1, const bs &b2) {
	bs ret; ull c=0;
	auto f=[](ull &x, ull y) {
		ull t=x;
		return (x=t-y)>t;
	};
	for (int i=0; i<1000; i++) {
		ret[i]=b1[i];
		c=f(ret[i], c);
		c+=f(ret[i], b2[i]);
	}
	return ret;
}

bs operator |(const bs &b1, const bs &b2) {
	bs ret;
	for (int i=0; i<1000; i++) ret[i]=b1[i]|b2[i];
	return ret;
}

bs operator ^(const bs &b1, const bs &b2) {
	bs ret;
	for (int i=0; i<1000; i++) ret[i]=b1[i]^b2[i];
	return ret;
}

bs operator &(const bs &b1, const bs &b2) {
	bs ret;
	for (int i=0; i<1000; i++) ret[i]=b1[i]&b2[i];
	return ret;
}

bs shift(const bs &b) {
	bs ret; ull c=0;
	for (int i=0; i<1000; i++) ret[i]=c|(b[i]<<1), c=b[i]>>63;
	return ret;
}

int main() {
	scanf("%s %s", s, t);
	int n=strlen(s), m=(strlen(t));
	for (int i=0; i<m; i++) M[t[i]-'A'][i>>6]|=(1llu<<(i&63));
	for (int i=0; i<m; i++) if (s[0]==t[i]) { B[i>>6]|=(1llu<<(i&63)); break;}
	for (int i=1; i<n; i++) {
		X=B|M[s[i]-'A'];
		Y=shift(B); Y[0]|=1;
		B=X&(X^(X-Y));
		B[m>>6]&=(1llu<<(m&63))-1;
	}
	int c=0;
	for (int i=0; i<m; i++) if (B[i>>6]&(1llu<<(i&63))) c++;
	printf("%d\n", c);
	return 0;
}