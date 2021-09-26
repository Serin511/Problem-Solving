#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using i128 = __int128;

const ll MOD = 998244353;

ll mpow(ll n, ll k) {
	ll r=1, p=n%MOD;
	while (k) {
		if (k&1) r=r*p%MOD;
		p=p*p%MOD;
		k/=2;
	}
	return r;
}
ll mpow(ll n, ll k, ll mod) {
	ll r=1, p=n%mod;
	while (k) {
		if (k&1) r=(i128)r*p%mod;
		p=(i128)p*p%mod;
		k/=2;
	}
	return r;
}

namespace miller_rabin {

bool miller_rabin(ll x, ll a) {
	ll s=0, d=x-1;
	while (d%2==0) s++, d/=2;
	ll j=mpow(a, d, x);
	if (j==1) return true;
	int fl=0;
	for (int i=0; i<s; i++) {
		if (j==x-1) return true;
		j=j*j%x;
	}
	return false;
}

bool isprime(ll x) {
	if (x<=1) return false;
	vector<int> pr = {
		2, 7, 61
		//2, 3, 5, 7,
		//11, 13, 17, 19,
		//23, 29, 31, 37
	};
	for (auto &i:pr) {
		if (i==x) return true;
		if (!miller_rabin(x, i)) return false;
	}
	return true;
}
}

int main() {}
