#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#define fi first
#define se second
using namespace std;
typedef unsigned long long ull;
typedef array<ull, 50> bs;

int z;

bs operator -(const bs &b1, const bs &b2) {
	bs ret; ull c=0;
	auto f=[](ull &x, ull y) {
		ull t=x;
		return (x=t-y)>t;
	};
	for (int i=0; i<z; i++) {
		ret[i]=b1[i];
		c=f(ret[i], c);
		c+=f(ret[i], b2[i]);
	}
	return ret;
}

bs operator |(const bs &b1, const bs &b2) {
	bs ret;
	for (int i=0; i<z; i++) ret[i]=b1[i]|b2[i];
	return ret;
}

bs operator ^(const bs &b1, const bs &b2) {
	bs ret;
	for (int i=0; i<z; i++) ret[i]=b1[i]^b2[i];
	return ret;
}

bs operator &(const bs &b1, const bs &b2) {
	bs ret;
	for (int i=0; i<z; i++) ret[i]=b1[i]&b2[i];
	return ret;
}

bs shift(const bs &b) {
	bs ret; ull c=0;
	for (int i=0; i<z; i++) ret[i]=c|(b[i]<<1), c=b[i]>>63;
	return ret;
}

pair<int, int> lcs(string s) {
	int n=s.size(); z=n/64+1;
	bs M[26], B, X, Y; pair<int, int> r(0, 0);
	for (int i=0; i<26; i++) for (int j=0; j<z; j++) M[i][j]=0;
	for (int i=0; i<n; i++) M[s[i]-'a'][i>>6]|=(1llu<<(i&63));

	for (int j=n-1; j; j--) {
		if (min(j, n-j)<=r.fi) continue;
		z=j/64+1;
		for (int i=0; i<26; i++) M[i][j>>6]&=(1llu<<(j&63))-1;
		for (int i=0; i<z; i++) B[i]=X[i]=Y[i]=0;
		for (int i=0; i<n; i++) if (s[i]==s[j]) { B[i>>6]|=(1llu<<(i&63)); break;}
		for (int i=j+1; i<n; i++) {
			X=B|M[s[i]-'a'];
			Y=shift(B); Y[0]|=1;
			B=X&(X^(X-Y));
			B[j>>6]&=(1llu<<(j&63))-1;
		}
		int c=0;
		for (int i=0; i<j; i++) if (B[i>>6]&(1llu<<(i&63))) c++;
		r=max(r, make_pair(c, j));
	}
	return r;
}

int D[3010][3010];
inline void lcs2(string &s, string &t) {
	int n=s.size(), m=t.size();
	for (int i=0; i<=n; i++) for (int j=0; j<=m; j++) D[i][j]=0;
	for (int i=0; i<n; i++) for (int j=0; j<m; j++) {
		if (s[i]==t[j]) D[i+1][j+1]=D[i][j]+1;
		D[i+1][j+1]=max({D[i+1][j+1], D[i][j+1], D[i+1][j]});
	}
	string r;
	for (int i=n, j=m; i&&j; ) {
		if (D[i][j]==D[i-1][j]) i--;
		else if (D[i][j]==D[i][j-1]) j--;
		else r.push_back(s[i-1]), i--, j--;
	}
	reverse(r.begin(), r.end()); cout<<r<<r<<'\n';
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int T; string s;
	cin>>T;
	for (int t=1; t<=T; t++) {
		cin>>s;
		auto a=lcs(s);
		cout<<"Case #"<<t<<": "<<a.fi*2<<'\n';
		if (a.fi) {
			string s1(s.begin(), s.begin()+a.se), s2(s.begin()+a.se, s.end());
			lcs2(s1, s2);
		}
	}
	cout.flush();
	return 0;
}